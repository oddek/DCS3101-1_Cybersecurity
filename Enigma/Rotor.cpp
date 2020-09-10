#include "Rotor.h"


Rotor::Rotor()
{

}

Rotor::Rotor(std::string _alphabet)
{
	alphabet = _alphabet;
	ringSetting = 0;
	offset = 0;
}

Rotor::~Rotor()
{

}


int Rotor::modulo(const int& a, const int& b)
{
	return (b + (a % b)) % b;
}

char Rotor::getTransformedChar(char c)
{
	//std::cout << "Incoming char: " << c << "\n";

	c = intToAsciiChar(modulo(charToAlphabetIndex(c) + offset - ringSetting, alphabet.size()));


	//std::cout << "char is now: " << c << "\n";

	char o = alphabet.at(charToAlphabetIndex(c));

	//std::cout << "Char is now after wiring: " << o << "\n";

	o = o + ringSetting;

	//std::cout << "Char is now after adding ringSetting: " << o << "\n";

	o = intToAsciiChar((modulo(charToAlphabetIndex(o) - offset, alphabet.size())));
	//std::cout << "char after final modulo: " << o << "\n";
	return o;
}

char Rotor::getInverseTransformedChar(char c)
{	

	//std::cout << "Inverse input: " << c << "\n";

//Operation: c = c + offset;
	c = intToAsciiChar(modulo(charToAlphabetIndex(c)+offset, alphabet.size()));
	//std::cout << "char after first operation: " << c << "\n";

//Operation: c = c -ringSetting;
	c = intToAsciiChar(modulo(charToAlphabetIndex(c) - ringSetting, alphabet.size()));
	//std::cout << "char after second operation: " << c << "\n";
//Operation: What gives c in masteralphabet:
	int i = alphabet.find(c);
	char o = masterAlphabet.at(i);
	//std::cout << "char after reg tranformation: " << o << "\n";

//Operation: o = o - offset + ring
	o = intToAsciiChar(modulo(charToAlphabetIndex(o) - offset + ringSetting, alphabet.size()));

	//std::cout << "Final output: " << o << "\n";

	return o;
}

void Rotor::setRingSetting(int i)
{
 	ringSetting = i;
}

bool Rotor::incrementOffset()
{
	offset++;

	return false;
}

void Rotor::setOffset(int i)
{
	offset = i;
}

char Rotor::intToAsciiChar(int i)
{
	return char(i + asciiOffset);
}

int Rotor::charToAlphabetIndex(char c)
{
	int i = (int)c - asciiOffset;
	return i;
}