
#include <vector>
#include <iostream>
#include <bitset>
#include <string>

std::bitset<8> multiply(std::bitset<8> a, std::bitset<8> b)
{
	if(b.to_ulong() == 0x01)
	{
		std::cout << "Returning a...\n";
		return a;
	} 
 	std::bitset<8> magicByte(std::string("00011011"));

	std::bitset<8> c = a << 1;
	if(a[a.size() - 1])
	{
		std::cout << "inne i xor\n";
		c ^= magicByte;
	}

	if(b.to_ulong() == 0x03)
	{
		c ^= a;
	}
	return c;
}

int main()
{
	std::vector<std::bitset<8>> mixer = {	std::bitset<8>(0x03), 
											std::bitset<8>(0x01), 
											std::bitset<8>(0x01), 
											std::bitset<8>(0x02)};

	std::vector<std::bitset<8>> column = {	std::bitset<8>(0xd4), 
											std::bitset<8>(0xbf), 
											std::bitset<8>(0x5d), 
											std::bitset<8>(0x30)};
	std::vector<std::bitset<8>> c;

	for(auto i : mixer)
	{
		std::cout << std::hex << i.to_ulong() << "\t";
	}
	std::cout << "\n\n";

	for(auto i : column)
	{
		std::cout << std::hex << i << "\n";
	}

	for(int i = 0; i < mixer.size(); i++)
	{
		c.push_back(multiply(column.at(i), mixer.at(i)));
	}

	std::bitset<8> final;

	for(auto i : c)
	{
		std::cout << i << "\n";
		final ^= i;
	}

	std::cout << "Final: " << std::hex << final.to_ulong() << "\n";
	return 0;
}