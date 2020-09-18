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

std::vector<std::vector<int>> L_TABLE =
{
	{0x00, 0x00, 0x19, 0x01, 0x32, 0x02, 0x1A, 0xC6, 0x4B, 0xC7, 0x1B, 0x68, 0x33, 0xEE, 0xDF, 0x03},
	{0x64, 0x04, 0xE0, 0x0E, 0x34, 0x8D, 0x81, 0xEF, 0x4C, 0x71, 0x08, 0xC8, 0xF8, 0x69, 0x1C, 0xC1}, 
	{0x7D, 0xC2, 0x1D, 0xB5, 0xF9, 0xB9, 0x27, 0x6A, 0x4D, 0xE4, 0xA6, 0x72, 0x9A, 0xC9, 0x09, 0x78}, 
	{0x65, 0x2F, 0x8A, 0x05, 0x21, 0x0F, 0xE1, 0x24, 0x12, 0xF0, 0x82, 0x45, 0x35, 0x93, 0xDA, 0x8E}, 
	{0x96, 0x8F, 0xDB, 0xBD, 0x36, 0xD0, 0xCE, 0x94, 0x13, 0x5C, 0xD2, 0xF1, 0x40, 0x46, 0x83, 0x38},
	{0x66, 0xDD, 0xFD, 0x30, 0xBF, 0x06, 0x8B, 0x62, 0xB3, 0x25, 0xE2, 0x98, 0x22, 0x88, 0x91, 0x10}, 
	{0x7E, 0x6E, 0x48, 0xC3, 0xA3, 0xB6, 0x1E, 0x42, 0x3A, 0x6B, 0x28, 0x54, 0xFA, 0x85, 0x3D, 0xBA}, 
	{0x2B, 0x79, 0x0A, 0x15, 0x9B, 0x9F, 0x5E, 0xCA, 0x4E, 0xD4, 0xAC, 0xE5, 0xF3, 0x73, 0xA7, 0x57}, 
	{0xAF, 0x58, 0xA8, 0x50, 0xF4, 0xEA, 0xD6, 0x74, 0x4F, 0xAE, 0xE9, 0xD5, 0xE7, 0xE6, 0xAD, 0xE8}, 
	{0x2C, 0xD7, 0x75, 0x7A, 0xEB, 0x16, 0x0B, 0xF5, 0x59, 0xCB, 0x5F, 0xB0, 0x9C, 0xA9, 0x51, 0xA0}, 
	{0x7F, 0x0C, 0xF6, 0x6F, 0x17, 0xC4, 0x49, 0xEC, 0xD8, 0x43, 0x1F, 0x2D, 0xA4, 0x76, 0x7B, 0xB7}, 
	{0xCC, 0xBB, 0x3E, 0x5A, 0xFB, 0x60, 0xB1, 0x86, 0x3B, 0x52, 0xA1, 0x6C, 0xAA, 0x55, 0x29, 0x9D}, 
	{0x97, 0xB2, 0x87, 0x90, 0x61, 0xBE, 0xDC, 0xFC, 0xBC, 0x95, 0xCF, 0xCD, 0x37, 0x3F, 0x5B, 0xD1},
	{0x53, 0x39, 0x84, 0x3C, 0x41, 0xA2, 0x6D, 0x47, 0x14, 0x2A, 0x9E, 0x5D, 0x56, 0xF2, 0xD3, 0xAB},
	{0x44, 0x11, 0x92, 0xD9, 0x23, 0x20, 0x2E, 0x89, 0xB4, 0x7C, 0xB8, 0x26, 0x77, 0x99, 0xE3, 0xA5}, 
	{0x67, 0x4A, 0xED, 0xDE, 0xC5, 0x31, 0xFE, 0x18, 0x0D, 0x63, 0x8C, 0x80, 0xC0, 0xF7, 0x70, 0x07}
};

std::vector<std::vector<int>> E_TABLE = 
{
	{0x01, 0x03, 0x05, 0x0F, 0x11, 0x33, 0x55, 0xFF, 0x1A, 0x2E, 0x72, 0x96, 0xA1, 0xF8, 0x13, 0x35}, 
	{0x5F, 0xE1, 0x38, 0x48, 0xD8, 0x73, 0x95, 0xA4, 0xF7, 0x02, 0x06, 0x0A, 0x1E, 0x22, 0x66, 0xAA}, 
	{0xE5, 0x34, 0x5C, 0xE4, 0x37, 0x59, 0xEB, 0x26, 0x6A, 0xBE, 0xD9, 0x70, 0x90, 0xAB, 0xE6, 0x31}, 
	{0x53, 0xF5, 0x04, 0x0C, 0x14, 0x3C, 0x44, 0xCC, 0x4F, 0xD1, 0x68, 0xB8, 0xD3, 0x6E, 0xB2, 0xCD}, 
	{0x4C, 0xD4, 0x67, 0xA9, 0xE0, 0x3B, 0x4D, 0xD7, 0x62, 0xA6, 0xF1, 0x08, 0x18, 0x28, 0x78, 0x88}, 
	{0x83, 0x9E, 0xB9, 0xD0, 0x6B, 0xBD, 0xDC, 0x7F, 0x81, 0x98, 0xB3, 0xCE, 0x49, 0xDB, 0x76, 0x9A}, 
	{0xB5, 0xC4, 0x57, 0xF9, 0x10, 0x30, 0x50, 0xF0, 0x0B, 0x1D, 0x27, 0x69, 0xBB, 0xD6, 0x61, 0xA3}, 
	{0xFE, 0x19, 0x2B, 0x7D, 0x87, 0x92, 0xAD, 0xEC, 0x2F, 0x71, 0x93, 0xAE, 0xE9, 0x20, 0x60, 0xA0}, 
	{0xFB, 0x16, 0x3A, 0x4E, 0xD2, 0x6D, 0xB7, 0xC2, 0x5D, 0xE7, 0x32, 0x56, 0xFA, 0x15, 0x3F, 0x41}, 
	{0xC3, 0x5E, 0xE2, 0x3D, 0x47, 0xC9, 0x40, 0xC0, 0x5B, 0xED, 0x2C, 0x74, 0x9C, 0xBF, 0xDA, 0x75}, 
	{0x9F, 0xBA, 0xD5, 0x64, 0xAC, 0xEF, 0x2A, 0x7E, 0x82, 0x9D, 0xBC, 0xDF, 0x7A, 0x8E, 0x89, 0x80}, 
	{0x9B, 0xB6, 0xC1, 0x58, 0xE8, 0x23, 0x65, 0xAF, 0xEA, 0x25, 0x6F, 0xB1, 0xC8, 0x43, 0xC5, 0x54}, 
	{0xFC, 0x1F, 0x21, 0x63, 0xA5, 0xF4, 0x07, 0x09, 0x1B, 0x2D, 0x77, 0x99, 0xB0, 0xCB, 0x46, 0xCA}, 
	{0x45, 0xCF, 0x4A, 0xDE, 0x79, 0x8B, 0x86, 0x91, 0xA8, 0xE3, 0x3E, 0x42, 0xC6, 0x51, 0xF3, 0x0E}, 
	{0x12, 0x36, 0x5A, 0xEE, 0x29, 0x7B, 0x8D, 0x8C, 0x8F, 0x8A, 0x85, 0x94, 0xA7, 0xF2, 0x0D, 0x17}, 
	{0x39, 0x4B, 0xDD, 0x7C, 0x84, 0x97, 0xA2, 0xFD, 0x1C, 0x24, 0x6C, 0xB4, 0xC7, 0x52, 0xF6, 0x01}, 
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

std::vector<std::vector<int>> INV_MIX_COL_MATRIX = 
{
	{0x0E, 0x0B, 0x0D, 0x09},
	{0x09, 0x0E, 0x0B, 0x0D},
	{0x0D, 0x09, 0x0E, 0x0B},
	{0x0B, 0x0D, 0x09, 0x0E}
};


//Operations:
void addRoundKey(std::vector<std::vector<std::bitset<8>>>& grid, std::vector<std::vector<std::bitset<8>>>& key);
void substitute(std::vector<std::vector<std::bitset<8>>>& grid);
void shiftGrid(std::vector<std::vector<std::bitset<8>>>& grid);
void mixColumns(std::vector<std::vector<std::bitset<8>>>& grid);

//Inverse Operations:
void invSubstitute(std::vector<std::vector<std::bitset<8>>>& grid);
void invShiftGrid(std::vector<std::vector<std::bitset<8>>>& grid);
void invMixColumns(std::vector<std::vector<std::bitset<8>>>& grid);

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
std::string hexStringToPlaintext(std::string s);

void runTests();

//Interface
std::string encrypt128BitMessage(std::vector<std::vector<std::bitset<8>>> grid, std::vector<std::vector<std::bitset<8>>>& key);
std::string decrypt128BitMessage(std::vector<std::vector<std::bitset<8>>> grid, std::vector<std::vector<std::bitset<8>>>& key);

int main()
{
	bool test = true;
	bool randomKey = false;

	if(test) 
	{
		runTests();
		return 0;
	}

	std::string plaintext = 	"Dette er en melding som jeg ikke vet";
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
	std::cout << "EncryptedMessage: \n\t" << encrypted << "\n";

	auto grid2 = generateGridFromHexString(encrypted);

	std::string decrypted = decrypt128BitMessage(grid2, key);
	std::cout << "DecryptedMessage: \n\t" << decrypted << "\n";

	std::string decPlain = hexStringToPlaintext(decrypted);
	std::cout << "DecryptedPlainText: \n\t" << decPlain << "\n";

	return 0;
}

std::string hexStringToPlaintext(std::string s)
{
	std::string plain = "";
	for(int i = 0; i < s.size(); i+=2)
	{
		char temp = stoul(s.substr(i, 2), 0, 16);
		plain += temp;
	}
	return plain;
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

std::string decrypt128BitMessage(std::vector<std::vector<std::bitset<8>>> grid, std::vector<std::vector<std::bitset<8>>>& key)
{
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

std::bitset<8> L(std::bitset<8> byte)
{
	std::bitset<8> divider(0x0F);
	unsigned col = std::bitset<4>((byte & divider).to_ulong()).to_ulong();
	unsigned row = std::bitset<4>(((byte >> 4) & divider).to_ulong()).to_ulong();

	return std::bitset<8>(L_TABLE.at(row).at(col));	
}


std::bitset<8> E(std::bitset<8> byte)
{
	std::bitset<8> divider(0x0F);
	unsigned col = std::bitset<4>((byte & divider).to_ulong()).to_ulong();
	unsigned row = std::bitset<4>(((byte >> 4) & divider).to_ulong()).to_ulong();

	return std::bitset<8>(E_TABLE.at(row).at(col));	
}


void invMixColumns(std::vector<std::vector<std::bitset<8>>>& grid)
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

void invShiftGrid(std::vector<std::vector<std::bitset<8>>>& grid)
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

//TEST1
	std::string plaintext = 	"6bc1bee22e409f96e93d7e117393172a";
	std::string keyString = 	"2b7e151628aed2a6abf7158809cf4f3c";
	std::string cipherText = 	"3ad77bb40d7a3660a89ecaf32466ef97";
	auto grid = generateGridFromHexString(plaintext);
	auto key = generateGridFromHexString(keyString);
	auto cipher = generateGridFromHexString(cipherText);

	std::string encrypted = encrypt128BitMessage(grid, key);
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
	//std::cout << encrypted << "\n";
	//std::cout << cipherText << "\n";
	grid = generateGridFromHexString(encrypted);
	std::string decrypted = decrypt128BitMessage(grid, key);

	//std::cout << plaintext << "\n";
	//std::cout << decrypted << "\n";

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
	keyString = 	"2b7e151628aed2a6abf7158809cf4f3c";
	cipherText = 	"f5d3d58503b9699de785895a96fdbaaf";
	grid = generateGridFromHexString(plaintext);
	key = generateGridFromHexString(keyString);
	cipher = generateGridFromHexString(cipherText);

	encrypted = encrypt128BitMessage(grid, key);

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

	//std::cout << encrypted << "\n";
	//std::cout << cipherText << "\n";
	grid = generateGridFromHexString(encrypted);
	decrypted = decrypt128BitMessage(grid, key);

	//std::cout << plaintext << "\n";
	//std::cout << decrypted << "\n";

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
	keyString = 	"2b7e151628aed2a6abf7158809cf4f3c";
	cipherText = 	"43b1cd7f598ece23881b00e3ed030688";
	grid = generateGridFromHexString(plaintext);
	key = generateGridFromHexString(keyString);
	cipher = generateGridFromHexString(cipherText);

	encrypted = encrypt128BitMessage(grid, key);

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

	grid = generateGridFromHexString(encrypted);
	decrypted = decrypt128BitMessage(grid, key);

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
	keyString = 	"2b7e151628aed2a6abf7158809cf4f3c";
	cipherText = 	"7b0c785e27e8ad3f8223207104725dd4";
	grid = generateGridFromHexString(plaintext);
	key = generateGridFromHexString(keyString);
	cipher = generateGridFromHexString(cipherText);

	encrypted = encrypt128BitMessage(grid, key);

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
	//std::cout << encrypted << "\n";
	//std::cout << cipherText << "\n";
	grid = generateGridFromHexString(encrypted);
	decrypted = decrypt128BitMessage(grid, key);

	//std::cout << plaintext << "\n";
	//std::cout << decrypted << "\n";

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

