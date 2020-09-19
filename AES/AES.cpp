#include "AES.h"

using namespace AES;

std::string AES::plaintextToHexString(std::string plaintext)
{
	std::stringstream stream;
	for(auto ch : plaintext)
	{
		unsigned long num = ch;
		if(num < 16) stream << 0;
		stream << std::hex << num;
	}
	std::string res(stream.str());
	return res;
}

std::string AES::hexStringToPlaintext(std::string s)
{
	std::string plain = "";
	for(int i = 0; i < s.size(); i+=2)
	{
		char temp = stoul(s.substr(i, 2), 0, 16);
		plain += temp;
	}
	return plain;
}


std::vector<std::vector<std::bitset<8>>> AES::generateGridFromHexString(std::string s)
{
	std::vector<std::vector<std::bitset<8>>> grid(4, std::vector<std::bitset<8>>(4));

	int index = 0;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			grid.at(j).at(i) = std::bitset<8>(stoi(s.substr(index, 2), 0, 16));
			index += 2;
		}
	}
	return grid;
}

std::string AES::decrypt128BitMessage(std::string cipherText, std::string keyString)
{
	auto key = generateGridFromHexString(keyString);

	auto grid = generateGridFromHexString(cipherText);

	auto expandedKey = generateExpandedKey(key);
	//printExpandedKey(expandedKey);
	//Initial Round:
	addRoundKey(grid, expandedKey.at(expandedKey.size() - 1));

	//Rounds 1-10
	for(int i = expandedKey.size() - 2; i > 0; i--)
	{
		invShiftGrid(grid);
		invSubstitute(grid);
		addRoundKey(grid, expandedKey.at(i));
		invMixColumns(grid);
	}

	invShiftGrid(grid);
	invSubstitute(grid);
	addRoundKey(grid, expandedKey.at(0));
	//printGrid(grid);
	return gridToHexString(grid);
}



std::string AES::encrypt128BitMessage(std::string plaintext, std::string keyString)
{
	auto key = generateGridFromHexString(keyString);

	auto grid = generateGridFromHexString(plaintext);

	auto expandedKey = generateExpandedKey(key);
	//std::cout << "ExpandedKey: \n";
	//printExpandedKey(expandedKey);
	//Initial Round: Add round key
	addRoundKey(grid, expandedKey.at(0));

	//Rounds 1 - 10:
	for(int i = 1; i < ROUNDS; i++)
	{
		substitute(grid);
		shiftGrid(grid);
		mixColumns(grid);
		addRoundKey(grid, expandedKey.at(i));
	}
	//Final Round:
	substitute(grid);
	shiftGrid(grid);
	addRoundKey(grid, expandedKey.at(ROUNDS));

	return gridToHexString(grid);
}

std::string AES::gridToHexString(std::vector<std::vector<std::bitset<8>>> grid)
{
	std::stringstream stream;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			unsigned long num = grid.at(j).at(i).to_ulong();
			if(num < 16) stream << 0;
			stream << std::hex << num;
		}
	}
	std::string res(stream.str());
	return res;
}




/*KEY STUFF*/
std::vector<std::vector<std::bitset<8>>> AES::generateKey()
{
	std::vector<std::vector<std::bitset<8>>> grid(4, std::vector<std::bitset<8>>(4));

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			grid.at(i).at(j) = std::bitset<8>(rand() % 256);
			//grid.at(i).at(j) = std::bitset<8>(0xFF);

		}
	}
	return grid;
}

std::vector<std::vector<std::vector<std::bitset<8>>>> AES::generateExpandedKey(std::vector<std::vector<std::bitset<8>>>& key)
{
	std::vector<std::vector<std::vector<std::bitset<8>>>> expandedKey;//ROUNDS - 1, std::vector<std::vector<std::bitset<8>>>(N, std::vector<std::bitset<8>>(N)));

	//Add the key to the first row of expanded key:
	expandedKey.push_back(key);
	for(int i = 1; i <= ROUNDS; i++)
	{
		expandedKey.push_back(generateRoundKey(expandedKey.back(), i));
	}
	
	return expandedKey;
}

std::vector<std::vector<std::bitset<8>>> AES::generateRoundKey(std::vector<std::vector<std::bitset<8>>>& prevKey, int roundNumber)
{
	std::vector<std::vector<std::bitset<8>>> roundKey(4, std::vector<std::bitset<8>>(4));
	//Create and fill G with rightmost col from prevKey
	std::vector<std::bitset<8>> G;
	for(int i = 0; i < N; i++)
	{
		G.push_back(prevKey.at(i).at(N-1));
	}

	//for(auto& byte : G) std::cout << std::hex << byte.to_ulong();
	//std::cout << "\n";
	//shift rotate G, on to the left
	std::rotate(G.begin(), G.begin()+1, G.end());

	//Push G through S_Box
	for(auto& byte : G)
	{
		byte = sBox(byte);
	}

	//XOr first byte of G with roundnumber
	G.at(0) ^= std::bitset<8>(RCON_BOX.at(roundNumber));

	//First word of roundKey is first word of prevKey XORed with G
	for(int i = 0; i < N; i++)
	{
		roundKey.at(i).at(0) = prevKey.at(i).at(0) ^ G.at(i);
	}
	for(int j = 1; j < N; j++)
	{
		for(int i = 0; i < N; i++)
		{
			roundKey.at(i).at(j) = prevKey.at(i).at(j) ^ roundKey.at(i).at(j-1);
		}	
	}
	return roundKey;
}

void AES::printExpandedKey(std::vector<std::vector<std::vector<std::bitset<8>>>>& key)
{
	for(const auto& grid : key)
	{
		printGrid(grid);
	}
}


/*NORMAL STUFF*/
void AES::addRoundKey(std::vector<std::vector<std::bitset<8>>>& grid, std::vector<std::vector<std::bitset<8>>>& key)
{
	for(int row = 0; row < N; row++)
	{
		for(int col = 0; col < N; col++)
		{
			grid.at(row).at(col) ^= key.at(row).at(col);
		}
	}
}

void AES::mixColumns(std::vector<std::vector<std::bitset<8>>>& grid)
{
	std::vector<std::vector<std::bitset<8>>> newGrid(4, std::vector<std::bitset<8>>(4));

	for(int row = 0; row < N; row++)
	{
		for(int col = 0; col < N; col++)
		{
			std::vector<std::bitset<8>> c;

			for(int tempRow = 0; tempRow < N; tempRow++)
			{
				c.push_back(ffMultiply(grid.at(tempRow).at(col), MIX_COL_MATRIX.at(row).at(tempRow)));
			}
			std::bitset<8> final;
			for(auto i : c) final ^= i;
			newGrid.at(row).at(col) = final;

		}
	}
	grid = newGrid;
}

std::bitset<8> AES::L(std::bitset<8> byte)
{
	std::bitset<8> divider(0x0F);
	unsigned col = std::bitset<4>((byte & divider).to_ulong()).to_ulong();
	unsigned row = std::bitset<4>(((byte >> 4) & divider).to_ulong()).to_ulong();

	return std::bitset<8>(L_TABLE.at(row).at(col));	
}


std::bitset<8> AES::E(std::bitset<8> byte)
{
	std::bitset<8> divider(0x0F);
	unsigned col = std::bitset<4>((byte & divider).to_ulong()).to_ulong();
	unsigned row = std::bitset<4>(((byte >> 4) & divider).to_ulong()).to_ulong();

	return std::bitset<8>(E_TABLE.at(row).at(col));	
}


void AES::invMixColumns(std::vector<std::vector<std::bitset<8>>>& grid)
{
	std::vector<std::vector<std::bitset<8>>> newGrid(4, std::vector<std::bitset<8>>(4));

	for(int row = 0; row < N; row++)
	{
		for(int col = 0; col < N; col++)
		{
			std::vector<std::bitset<8>> c;

			for(int tempRow = 0; tempRow < N; tempRow++)
			{
				auto b1 = grid.at(tempRow).at(col);
				auto b2 = INV_MIX_COL_MATRIX.at(row).at(tempRow);
				if(b1.none()) 
				{
					c.push_back(b1);
					continue;
				}
				unsigned long t1 = L(b1).to_ulong();
				unsigned long t2 = L(b2).to_ulong();
				unsigned long t3 = t1 + t2;
				if(t3 > 0xFF) t3 -= 0xFF;

				c.push_back(E(std::bitset<8>(t3)));
				//c.push_back(E(L(grid.at(tempRow).at(col)) ^ L(INV_MIX_COL_MATRIX.at(row).at(tempRow))));
			}
			std::bitset<8> final;
			for(auto i : c) final ^= i;
			newGrid.at(row).at(col) = final;

		}
	}
	grid = newGrid;
}



std::bitset<8> AES::ffMultiply(std::bitset<8> a, std::bitset<8> b)
{
	//std::cout << "Multi " << std::hex << a.to_ulong() << ", with " << std::hex << b.to_ulong() << "\n";
	if(b.to_ulong() == 0x01)
	{
		return a;
	} 
 	std::bitset<8> magicByte(std::string("00011011"));

	std::bitset<8> c = a << 1;
	if(a[a.size() - 1])
	{
		c ^= magicByte;
	}

	if(b.to_ulong() == 0x03)
	{
		c ^= a;
	}
	return c;
}



std::bitset<8> AES::sBox(std::bitset<8> byte)
{
	std::bitset<8> divider(0x0F);
	unsigned col = std::bitset<4>((byte & divider).to_ulong()).to_ulong();
	unsigned row = std::bitset<4>(((byte >> 4) & divider).to_ulong()).to_ulong();

	return std::bitset<8>(S_BOX.at(row).at(col));
}

std::bitset<8> AES::invSBox(std::bitset<8> byte)
{
	std::bitset<8> divider(0x0F);
	unsigned col = std::bitset<4>((byte & divider).to_ulong()).to_ulong();
	unsigned row = std::bitset<4>(((byte >> 4) & divider).to_ulong()).to_ulong();

	return std::bitset<8>(INV_S_BOX.at(row).at(col));
}

void AES::printGrid(const std::vector<std::vector<std::bitset<8>>>& grid)
{
	for(auto v : grid)
	{
		std::cout << "\t";
		for(auto b : v)
		{
			std::cout << std::hex << b.to_ulong() << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

void AES::shiftGrid(std::vector<std::vector<std::bitset<8>>>& grid)
{
	for(int i = 1; i < N; i++)
	{
		std::rotate(grid.at(i).begin(), grid.at(i).begin()+i, grid.at(i).end());

	}
}

void AES::invShiftGrid(std::vector<std::vector<std::bitset<8>>>& grid)
{
	for(int i = 1; i < N; i++)
	{
		std::rotate(grid.at(i).begin(), grid.at(i).end()-i, grid.at(i).end());
	}
}


void AES::substitute(std::vector<std::vector<std::bitset<8>>>& grid)
{
	for(auto& vector : grid)
	{
		for(auto& byte : vector)
		{
			byte = sBox(byte);
		}
	}
}

void AES::invSubstitute(std::vector<std::vector<std::bitset<8>>>& grid)
{
	for(auto& vector : grid)
	{
		for(auto& byte : vector)
		{
			byte = invSBox(byte);

		}
	}
}

std::vector<std::vector<std::bitset<8>>> AES::generateGridFromPlainText(std::string message)
{
	std::vector<std::vector<std::bitset<8>>> grid(4, std::vector<std::bitset<8>>(4));

	int index = 0;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			grid.at(j).at(i) = std::bitset<8>(message.at(index));
			index++;
		}
	}
	return grid;
}


/*
	Test vectors collected from: https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf
	PAGE 24
*/
void AES::runTests()
{

	std::cout << "Running tests:\n";

//TEST1
	std::string plaintext = 	"6bc1bee22e409f96e93d7e117393172a";
	std::string key = 			"2b7e151628aed2a6abf7158809cf4f3c";
	std::string cipherText = 	"3ad77bb40d7a3660a89ecaf32466ef97";

	std::string encrypted = encrypt128BitMessage(plaintext, key);
	std::cout << "\tTest 1: \n";
	std::cout << "\t\tEncryption: ";
	if(cipherText.compare(encrypted) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

	std::string decrypted = decrypt128BitMessage(encrypted, key);
	std::cout << "\t\tDecryption: ";
	if(decrypted.compare(plaintext) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}


//TEST2
	plaintext = 	"ae2d8a571e03ac9c9eb76fac45af8e51";
	key = 			"2b7e151628aed2a6abf7158809cf4f3c";
	cipherText = 	"f5d3d58503b9699de785895a96fdbaaf";

	encrypted = encrypt128BitMessage(plaintext, key);

	std::cout << "\tTest 2: \n";
	std::cout << "\t\tEncryption: ";
	if(cipherText.compare(encrypted) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

	decrypted = decrypt128BitMessage(encrypted, key);

	std::cout << "\t\tDecryption: ";
	if(decrypted.compare(plaintext) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

//TEST3
	plaintext = 	"30c81c46a35ce411e5fbc1191a0a52ef";
	key =		 	"2b7e151628aed2a6abf7158809cf4f3c";
	cipherText = 	"43b1cd7f598ece23881b00e3ed030688";

	encrypted = encrypt128BitMessage(plaintext, key);

	std::cout << "\tTest 3: \n";
	std::cout << "\t\tEncryption: ";

	if(cipherText.compare(encrypted) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

	decrypted = decrypt128BitMessage(encrypted, key);

	std::cout << "\t\tDecryption: ";
	if(decrypted.compare(plaintext) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}


//TEST4
	plaintext = 	"f69f2445df4f9b17ad2b417be66c3710";
	key =		 	"2b7e151628aed2a6abf7158809cf4f3c";
	cipherText = 	"7b0c785e27e8ad3f8223207104725dd4";

	encrypted = encrypt128BitMessage(plaintext, key);

	std::cout << "\tTest 4: \n";
	std::cout << "\t\tEncryption: ";

	if(cipherText.compare(encrypted) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

	decrypted = decrypt128BitMessage(encrypted, key);

	std::cout << "\t\tDecryption: ";
	if(decrypted.compare(plaintext) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

}