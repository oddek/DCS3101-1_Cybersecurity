#include <bitset>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

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
std::string gridToString(std::vector<std::vector<std::bitset<8>>> grid);

void test();

//Interface
std::string encrypt128BitMessage(std::vector<std::vector<std::bitset<8>>> grid, std::vector<std::vector<std::bitset<8>>>& key);






int main()
{
	


	std::string plaintext = 	"6a84867cd77e12ad07ea1be895c53fa3";
	std::string keyString = 	"00000000000000000000000000000000";
	std::string cipherText = 	"732281c0a0aab8f7a54a0c67a0c45ecf";


	auto grid = generateGridFromHexString(plaintext);
	auto key = generateGridFromHexString(keyString);
	auto cipher = generateGridFromHexString(cipherText);


	/*std::string message = "katthundfisklaks";//kentoddeengaarne";

	auto grid = generateGrid(message);
	auto key = generateKey();
	*/std::cout << "Message as grid:\n";
	printGrid(grid);
	std::cout << "Key:\n";
	printGrid(key);
	std::string encrypted = encrypt128BitMessage(grid, key);
	std::cout << "EncryptedMessage: \n" << encrypted;
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

	substitute(grid);
	shiftGrid(grid);
	addRoundKey(grid, expandedKey.at(10));



	std::cout << "EncryptedGRID: \n";
	printGrid(grid);
	return gridToString(grid);
}

std::string gridToString(std::vector<std::vector<std::bitset<8>>> grid)
{
	std::string s = "";
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			unsigned long n = grid.at(j).at(i).to_ulong();
			s += static_cast<unsigned char>(n);
		}
	}
	return s;
}




/*KEY STUFF*/
std::vector<std::vector<std::bitset<8>>> generateKey()
{
	std::vector<std::vector<std::bitset<8>>> grid(4, std::vector<std::bitset<8>>(4));

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			//grid.at(i).at(j) = std::bitset<8>(rand() % 256);
			grid.at(i).at(j) = std::bitset<8>(0xFF);

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

std::vector<std::vector<std::bitset<8>>> generateGrid(std::string message)
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



void test()
{
















	std::vector<std::vector<std::bitset<8>>> grid;

	grid.push_back({std::bitset<8>(0x32), 
					std::bitset<8>(0x88), 
					std::bitset<8>(0x31), 
					std::bitset<8>(0xe0)});
	grid.push_back({std::bitset<8>(0x43), 
					std::bitset<8>(0x5a), 
					std::bitset<8>(0x31), 
					std::bitset<8>(0x37)});
	grid.push_back({std::bitset<8>(0xf6), 
					std::bitset<8>(0x30), 
					std::bitset<8>(0x98), 
					std::bitset<8>(0x07)});
	grid.push_back({std::bitset<8>(0xa8), 
					std::bitset<8>(0x8d), 
					std::bitset<8>(0xa2), 
					std::bitset<8>(0x34)});

	std::vector<std::vector<std::bitset<8>>> key;

	key.push_back({std::bitset<8>(0x2b), 
					std::bitset<8>(0x28), 
					std::bitset<8>(0xab), 
					std::bitset<8>(0x09)});
	key.push_back({std::bitset<8>(0x7e), 
					std::bitset<8>(0xae), 
					std::bitset<8>(0xf7), 
					std::bitset<8>(0xcf)});
	key.push_back({std::bitset<8>(0x15), 
					std::bitset<8>(0xd2), 
					std::bitset<8>(0x15), 
					std::bitset<8>(0x4f)});
	key.push_back({std::bitset<8>(0x16), 
					std::bitset<8>(0xa6), 
					std::bitset<8>(0x88), 
					std::bitset<8>(0x3c)});

	std::vector<std::vector<std::bitset<8>>> sol;

	sol.push_back({std::bitset<8>(0x39), 
					std::bitset<8>(0x02), 
					std::bitset<8>(0xdc), 
					std::bitset<8>(0x19)});
	sol.push_back({std::bitset<8>(0x25), 
					std::bitset<8>(0xdc), 
					std::bitset<8>(0x11), 
					std::bitset<8>(0x61)});
	sol.push_back({std::bitset<8>(0x84), 
					std::bitset<8>(0x09), 
					std::bitset<8>(0x85), 
					std::bitset<8>(0x0b)});
	sol.push_back({std::bitset<8>(0x1d), 
					std::bitset<8>(0xfb), 
					std::bitset<8>(0x97), 
					std::bitset<8>(0x32)});


	std::cout << "Running test: ";

	/*std::cout << "Plaintext as grid:\n";
	printGrid(grid);
	std::cout << "Key as grid:\n";
	printGrid(key);
	std::string encrypted = encrypt128BitMessage(grid, key);

	std::cout << "Solution as grid: \n";
	printGrid(sol);
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if()
		}
	}
	return 0;*/
}

