#include "Rotor.h"


Rotor::Rotor()
{

}

Rotor::Rotor(int _id, char _pos)
{
	rotorId = _id;
	rotorPosition = _pos;
	if(_pos == 'r')
	{
		alphabet = reflectorAlphabets[_id];
	}
	else
	{
		alphabet = rotorAlphabets[_id];
	}
	ringSetting = 0;
	offset = 0;
	steppingPoint = charToAlphabetIndex(stepPoints[_id]);
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
//Operation: c = c + offset - ringsetting
	c = intToAsciiChar(modulo(charToAlphabetIndex(c) + offset - ringSetting, alphabet.size()));
	//std::cout << "char is now: " << c << "\n";

//Operation: Normal transformation
	char o = alphabet.at(charToAlphabetIndex(c));
	//std::cout << "Char is now after wiring: " << o << "\n";

//Operation: o = o + ringSetting;
	o = intToAsciiChar(modulo(charToAlphabetIndex(o) + ringSetting, alphabet.size()));
	//std::cout << "Char is now after adding ringSetting: " << o << "\n";

//Operation: o = o - offset;
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

bool Rotor::incrementOffset(bool doubleStep)
{
	offset = modulo(offset + 1, alphabet.size());
	//If this is the rightmost rotor, and the middle rotor is in doublestep position, we also have to return true;
	if(offset == steppingPoint || rotorPosition == 'R' && doubleStep) 
	{
		std::cout << "Rotor " << rotorPosition << " at stepPoint: " << steppingPoint << "\n";
		return true;
	}
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

void Rotor::printRotorStatus()
{
	std::cout << "\tRotorID: " << rotorId << "\n";
	std::cout << "\t\tStepping point: " << steppingPoint << "\n";
	std::cout << "\t\tCurrent offset: " << offset << "\n";
	std::cout << "\t\tCurrent RingSetting: " << ringSetting << "\n";
	std::cout << "\t\tAlhpabet: " << alphabet << "\n\n\n";
}
//If the middle rotor is at the position before it is supposed to step the next, it shall just step to the next;
bool Rotor::isDoubleStep()
{
	return rotorPosition == 'M' && offset == steppingPoint - 1;
}