#include <string>
#ifndef ROTOR_H
#define ROTOR_H

class Rotor
{
public:
	Rotor(std::string _alphabet);
	~Rotor();
	char getTransformedChar(char c);
	void setRingSetting(int i);
	void incrementOffset();
	void setOffset(int i);
	
private:
	std::string alphabet;
	int ringSetting;
	int offset;

	int charToAlphabetIndex(char c);
};
#endif