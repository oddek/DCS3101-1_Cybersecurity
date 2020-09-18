#include <bitset>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

int N = 4;
int ROUNDS = 10;

std::vector<int> RCON_BOX = 
{
	{0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36} 
};

std::vector<std::vector<int>> S_BOX = 
{
 	{0x63 ,0x7c ,0x77 ,0x7b ,0xf2 ,0x6b ,0x6f ,0xc5 ,0x30 ,0x01 ,0x67 ,0x2b ,0xfe ,0xd7 ,0xab ,0x76},
 	{0xca ,0x82 ,0xc9 ,0x7d ,0xfa ,0x59 ,0x47 ,0xf0 ,0xad ,0xd4 ,0xa2 ,0xaf ,0x9c ,0xa4 ,0x72 ,0xc0},
 	{0xb7 ,0xfd ,0x93 ,0x26 ,0x36 ,0x3f ,0xf7 ,0xcc ,0x34 ,0xa5 ,0xe5 ,0xf1 ,0x71 ,0xd8 ,0x31 ,0x15},
 	{0x04 ,0xc7 ,0x23 ,0xc3 ,0x18 ,0x96 ,0x05 ,0x9a ,0x07 ,0x12 ,0x80 ,0xe2 ,0xeb ,0x27 ,0xb2 ,0x75},
 	{0x09 ,0x83 ,0x2c ,0x1a ,0x1b ,0x6e ,0x5a ,0xa0 ,0x52 ,0x3b ,0xd6 ,0xb3 ,0x29 ,0xe3 ,0x2f ,0x84},
 	{0x53 ,0xd1 ,0x00 ,0xed ,0x20 ,0xfc ,0xb1 ,0x5b ,0x6a ,0xcb ,0xbe ,0x39 ,0x4a ,0x4c ,0x58 ,0xcf},
 	{0xd0 ,0xef ,0xaa ,0xfb ,0x43 ,0x4d ,0x33 ,0x85 ,0x45 ,0xf9 ,0x02 ,0x7f ,0x50 ,0x3c ,0x9f ,0xa8},
 	{0x51 ,0xa3 ,0x40 ,0x8f ,0x92 ,0x9d ,0x38 ,0xf5 ,0xbc ,0xb6 ,0xda ,0x21 ,0x10 ,0xff ,0xf3 ,0xd2},
 	{0xcd ,0x0c ,0x13 ,0xec ,0x5f ,0x97 ,0x44 ,0x17 ,0xc4 ,0xa7 ,0x7e ,0x3d ,0x64 ,0x5d ,0x19 ,0x73},
 	{0x60 ,0x81 ,0x4f ,0xdc ,0x22 ,0x2a ,0x90 ,0x88 ,0x46 ,0xee ,0xb8 ,0x14 ,0xde ,0x5e ,0x0b ,0xdb},
 	{0xe0 ,0x32 ,0x3a ,0x0a ,0x49 ,0x06 ,0x24 ,0x5c ,0xc2 ,0xd3 ,0xac ,0x62 ,0x91 ,0x95 ,0xe4 ,0x79},
 	{0xe7 ,0xc8 ,0x37 ,0x6d ,0x8d ,0xd5 ,0x4e ,0xa9 ,0x6c ,0x56 ,0xf4 ,0xea ,0x65 ,0x7a ,0xae ,0x08},
 	{0xba ,0x78 ,0x25 ,0x2e ,0x1c ,0xa6 ,0xb4 ,0xc6 ,0xe8 ,0xdd ,0x74 ,0x1f ,0x4b ,0xbd ,0x8b ,0x8a},
 	{0x70 ,0x3e ,0xb5 ,0x66 ,0x48 ,0x03 ,0xf6 ,0x0e ,0x61 ,0x35 ,0x57 ,0xb9 ,0x86 ,0xc1 ,0x1d ,0x9e},
 	{0xe1 ,0xf8 ,0x98 ,0x11 ,0x69 ,0xd9 ,0x8e ,0x94 ,0x9b ,0x1e ,0x87 ,0xe9 ,0xce ,0x55 ,0x28 ,0xdf},
 	{0x8c ,0xa1 ,0x89 ,0x0d ,0xbf ,0xe6 ,0x42 ,0x68 ,0x41 ,0x99 ,0x2d ,0x0f ,0xb0 ,0x54 ,0xbb ,0x16}
};

std::vector<std::vector<int>> INV_S_BOX = 
{
	{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
    {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
    {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
    {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
    {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
    {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
    {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
    {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
    {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
    {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
    {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
    {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
    {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
    {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
    {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
};

std::vector<std::vector<int>> MIX_COL_MATRIX = 
{
	{2, 3, 1, 1},
	{1, 2, 3, 1},
	{1, 1, 2, 3},
	{3, 1, 1, 2}
};


//Operations:
void addRoundKey(std::vector<std::vector<std::bitset<8>>>& grid, std::vector<std::vector<std::bitset<8>>>& key);
void substitute(std::vector<std::vector<std::bitset<8>>>& grid);
void shiftGrid(std::vector<std::vector<std::bitset<8>>>& grid);
void mixColumns(std::vector<std::vector<std::bitset<8>>>& grid);

//Inverse Operations:

void invSubstitute(std::vector<std::vector<std::bitset<8>>>& grid);
void InvShiftGrid(std::vector<std::vector<std::bitset<8>>>& grid);

//Key
std::vector<std::vector<std::bitset<8>>> generateKey();
std::vector<std::vector<std::vector<std::bitset<8>>>> generateExpandedKey(std::vector<std::vector<std::bitset<8>>>& key);
std::vector<std::vector<std::bitset<8>>> generateRoundKey(std::vector<std::vector<std::bitset<8>>>& prevKey, int roundNumber);


//Helpers
std::bitset<8> sBox(std::bitset<8> byte);
std::bitset<8> ffMultiply(std::bitset<8> a, std::bitset<8> b);


//Meta
void printGrid(const std::vector<std::vector<std::bitset<8>>>& grid);
void printExpandedKey(std::vector<std::vector<std::vector<std::bitset<8>>>>& key);
std::vector<std::vector<std::bitset<8>>> generateGridFromPlainText(std::string message);
std::vector<std::vector<std::bitset<8>>> generateGridFromHexString(std::string s);
std::string gridToHexString(std::vector<std::vector<std::bitset<8>>> grid);

void runTests();

//Interface
std::string encrypt128BitMessage(std::vector<std::vector<std::bitset<8>>> grid, std::vector<std::vector<std::bitset<8>>>& key);






int main()
{
	bool test = true;
	bool randomKey = false;

	if(test) 
	{
		runTests();
		return 0;
	}

	std::string plaintext = 	"katthundfisklakskentoddeheterjeg";
	std::string keyString = 	"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	auto key = generateGridFromHexString(keyString);

	auto grid = generateGridFromPlainText(plaintext);
	if(randomKey)
	{
		key = generateKey();
	}
	std::cout << "Plaintext:\n\t" << plaintext << "\n";
	std::cout << "Plaintext in hex: \n\t" << gridToHexString(grid) << "\n";
	std::cout << "Key: \n\t" << keyString << "\n";

	std::string encrypted = encrypt128BitMessage(grid, key);
	std::cout << "EncryptedMessage: \n\t" << encrypted;
	return 0;
}

std::vector<std::vector<std::bitset<8>>> generateGridFromHexString(std::string s)
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



std::string encrypt128BitMessage(std::vector<std::vector<std::bitset<8>>> grid, std::vector<std::vector<std::bitset<8>>>& key)
{

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

std::string gridToHexString(std::vector<std::vector<std::bitset<8>>> grid)
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
std::vector<std::vector<std::bitset<8>>> generateKey()
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

std::vector<std::vector<std::vector<std::bitset<8>>>> generateExpandedKey(std::vector<std::vector<std::bitset<8>>>& key)
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

std::vector<std::vector<std::bitset<8>>> generateRoundKey(std::vector<std::vector<std::bitset<8>>>& prevKey, int roundNumber)
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

void printExpandedKey(std::vector<std::vector<std::vector<std::bitset<8>>>>& key)
{
	for(const auto& grid : key)
	{
		printGrid(grid);
	}
}


/*NORMAL STUFF*/
void addRoundKey(std::vector<std::vector<std::bitset<8>>>& grid, std::vector<std::vector<std::bitset<8>>>& key)
{
	for(int row = 0; row < N; row++)
	{
		for(int col = 0; col < N; col++)
		{
			grid.at(row).at(col) ^= key.at(row).at(col);
		}
	}
}

void mixColumns(std::vector<std::vector<std::bitset<8>>>& grid)
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


std::bitset<8> ffMultiply(std::bitset<8> a, std::bitset<8> b)
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



std::bitset<8> sBox(std::bitset<8> byte)
{
	std::bitset<8> divider(0x0F);
	unsigned col = std::bitset<4>((byte & divider).to_ulong()).to_ulong();
	unsigned row = std::bitset<4>(((byte >> 4) & divider).to_ulong()).to_ulong();

	return std::bitset<8>(S_BOX.at(row).at(col));
}

std::bitset<8> invSBox(std::bitset<8> byte)
{
	std::bitset<8> divider(0x0F);
	unsigned col = std::bitset<4>((byte & divider).to_ulong()).to_ulong();
	unsigned row = std::bitset<4>(((byte >> 4) & divider).to_ulong()).to_ulong();

	return std::bitset<8>(INV_S_BOX.at(row).at(col));
}

void printGrid(const std::vector<std::vector<std::bitset<8>>>& grid)
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

void shiftGrid(std::vector<std::vector<std::bitset<8>>>& grid)
{
	for(int i = 1; i < N; i++)
	{
		std::rotate(grid.at(i).begin(), grid.at(i).begin()+i, grid.at(i).end());

	}
}

void InvShiftGrid(std::vector<std::vector<std::bitset<8>>>& grid)
{
	for(int i = 1; i < N; i++)
	{
		std::rotate(grid.at(i).begin(), grid.at(i).end()-i, grid.at(i).end());
	}
}


void substitute(std::vector<std::vector<std::bitset<8>>>& grid)
{
	for(auto& vector : grid)
	{
		for(auto& byte : vector)
		{
			byte = sBox(byte);
		}
	}
}

void invSubstitute(std::vector<std::vector<std::bitset<8>>>& grid)
{
	for(auto& vector : grid)
	{
		for(auto& byte : vector)
		{
			byte = invSBox(byte);

		}
	}
}

std::vector<std::vector<std::bitset<8>>> generateGridFromPlainText(std::string message)
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
void runTests()
{

	std::cout << "Running tests:\n";

	std::string plaintext = 	"6bc1bee22e409f96e93d7e117393172a";
	std::string keyString = 	"2b7e151628aed2a6abf7158809cf4f3c";
	std::string cipherText = 	"3ad77bb40d7a3660a89ecaf32466ef97";
	auto grid = generateGridFromHexString(plaintext);
	auto key = generateGridFromHexString(keyString);
	auto cipher = generateGridFromHexString(cipherText);

	std::string encrypted = encrypt128BitMessage(grid, key);
	std::cout << "\tTest 1: ";
	if(cipherText.compare(encrypted) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

	plaintext = 	"ae2d8a571e03ac9c9eb76fac45af8e51";
	keyString = 	"2b7e151628aed2a6abf7158809cf4f3c";
	cipherText = 	"f5d3d58503b9699de785895a96fdbaaf";
	grid = generateGridFromHexString(plaintext);
	key = generateGridFromHexString(keyString);
	cipher = generateGridFromHexString(cipherText);

	encrypted = encrypt128BitMessage(grid, key);

	std::cout << "\tTest 2: ";
	if(cipherText.compare(encrypted) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

	plaintext = 	"30c81c46a35ce411e5fbc1191a0a52ef";
	keyString = 	"2b7e151628aed2a6abf7158809cf4f3c";
	cipherText = 	"43b1cd7f598ece23881b00e3ed030688";
	grid = generateGridFromHexString(plaintext);
	key = generateGridFromHexString(keyString);
	cipher = generateGridFromHexString(cipherText);

	encrypted = encrypt128BitMessage(grid, key);

	std::cout << "\tTest 2: ";
	if(cipherText.compare(encrypted) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

	plaintext = 	"f69f2445df4f9b17ad2b417be66c3710";
	keyString = 	"2b7e151628aed2a6abf7158809cf4f3c";
	cipherText = 	"7b0c785e27e8ad3f8223207104725dd4";
	grid = generateGridFromHexString(plaintext);
	key = generateGridFromHexString(keyString);
	cipher = generateGridFromHexString(cipherText);

	encrypted = encrypt128BitMessage(grid, key);

	std::cout << "\tTest 4: ";
	if(cipherText.compare(encrypted) == 0)
	{
		std::cout << "Passed\n";
	}
	else
	{
		std::cout << "Failed\n";
	}

}

