
#include <iostream>
#include <bitset>
#include <string>



int main()
{



	std::bitset<16> a(0x0B1A);
	std::bitset<16> b(0x4f58);

	std::bitset<16> c = (a ^ b);

	std::cout << a << "\n";
	std::cout << b << "\n";

	std::cout << std::hex << c.to_ulong() << "\n";

	std::cout << c << "\n";
}