#include <string>
#include <iostream>
#include <memory>
#include "Rotor.h"





int main()
{
	std::string alphabets[8] = 
	{
		"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
		"AJDKSIRUXBLHWTMCQGZNPYFVOE",
		"BDFHJLCPRTXVZNYEIWGAKMUSQO",
		"ESOVPZJAYQUIRHXLNFTGKDCMWB",
		"VZBRGITYUPSDNHLXAWMJQOFECK",
		"JPGVOUMFYQBENHZRDKASXLICTW",
		"NZJHGRCXMYSWBOUFAIVLPEKQDT",
		"FKQHTLXOCBJSPDZRAMEWNIUYGV"
	};
	//auto rotor1 = new Rotor(alphabets[0]);
	std::unique_ptr<Rotor> rotor1 = std::make_unique<Rotor>(alphabets[0]);

	
	return 0;
}