
#include <iostream>
#include <bitset>
#include <string>



int main()
{



	std::bitset<8> a(0xfe);
	std::bitset<8> b(0xd2);

	std::bitset<8> c = (a ^ b);

	std::cout << a << "\n";
	std::cout << b << "\n";

	std::cout << std::hex << c.to_ulong() << "\n";

	std::cout << c << "\n";
}