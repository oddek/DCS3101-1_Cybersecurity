
#include <iostream>
#include <bitset>
#include <string>



int main()
{
	std::bitset<8> a("11111111");
	std::bitset<8> b("01010101");

	std::bitset<8> c = (a ^= b);

	std::cout << c;
}