#include "Rotor.h"


Rotor::Rotor(std::string _alphabet)
{
	alphabet = _alphabet;
	ringSetting = 0;
	offset = 0;
}

Rotor::~Rotor()
{

}

char Rotor::getTransformedChar(char c)
{
	return alphabet.at(charToAlphabetIndex(c));
}

void Rotor::setRingSetting(int i)
{
 	ringSetting = i;
}

void Rotor::incrementOffset()
{
	offset++;
}

void Rotor::setOffset(int i)
{
	offset = i;
}

int Rotor::charToAlphabetIndex(char c)
{
	return (int)c - 97;
}