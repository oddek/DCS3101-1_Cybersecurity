
#ifndef ENIGMA_H
#define ENIGMA_H

#include "Rotor.h"
#include <vector>
#include <algorithm>


static const std::string rotorAlphabets[9] = 
	{
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
		"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
		"AJDKSIRUXBLHWTMCQGZNPYFVOE",
		"BDFHJLCPRTXVZNYEIWGAKMUSQO",
		"ESOVPZJAYQUIRHXLNFTGKDCMWB",
		"VZBRGITYUPSDNHLXAWMJQOFECK",
		"JPGVOUMFYQBENHZRDKASXLICTW",
		"NZJHGRCXMYSWBOUFAIVLPEKQDT",
		"FKQHTLXOCBJSPDZRAMEWNIUYGV"
	};

static const std::string reflectorAlphabets[3] = 
	{
		"EJMZALYXVBWFCRQUONTSPIKHGD",
		"YRUHQSLDPXNGOKMIEBFZCWVJAT",
		"FVPJIAOYEDRZXWGCTKUQSBNMHL"
	};

class Enigma
{
public:
	Enigma();
	~Enigma();
	void setRotors(int r[3]);
	void setOffset(int o[3]);
	void setRingSetting(int s[3]);
	std::string transform(std::string& input);



private:
	std::vector<Rotor> rotors;
	Rotor reflector;

	void rotateRotors();


};


#endif