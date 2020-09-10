#include <string>
#include <iostream>
#ifndef ROTOR_H
#define ROTOR_H

static const std::string masterAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


class Rotor
{
public:
	Rotor();
	Rotor(std::string _alphabet);
	~Rotor();
	char getTransformedChar(char c);
	char getInverseTransformedChar(char c);
	void setRingSetting(int i);
	bool incrementOffset();
	void setOffset(int i);
	
private:
	std::string alphabet;
	int ringSetting;
	int offset;
	char intToAsciiChar(int i);

	int charToAlphabetIndex(char c);
	int modulo(const int& a, const int& b);

	const int asciiOffset = 65;
};
#endif