#include <string>
#include <iostream>
#ifndef ROTOR_H
#define ROTOR_H

class Rotor
{
public:
	Rotor();
	Rotor(int _id, char _pos);
	~Rotor();
	char getTransformedChar(char c);
	char getInverseTransformedChar(char c);
	void setRingSetting(int i);
	bool incrementOffset(bool doubleStep);
	void setOffset(int i);
	void printRotorStatus();
	bool isDoubleStep();
private:
	std::string alphabet;
	int ringSetting;
	int offset;
	int steppingPoint;
	int steppingPoint2 = -1;
	char intToAsciiChar(int i);
	int rotorId = 0;
	char rotorPosition;
	int charToAlphabetIndex(char c);
	int modulo(const int& a, const int& b);
	const int asciiOffset = 65;
};

//Assorted rotor data etc. 
static const std::string masterAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const std::string rotorAlphabets[9] = 
{
	"", //Dummy alphabet
	"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
	"ESOVPZJAYQUIRHXLNFTGKDCMWB",
	"VZBRGITYUPSDNHLXAWMJQOFECK",
	"JPGVOUMFYQBENHZRDKASXLICTW",
	"NZJHGRCXMYSWBOUFAIVLPEKQDT",
	"FKQHTLXOCBJSPDZRAMEWNIUYGV"
};
//Rotors will step the next, when stepping to these characters
static const std::string stepPoints[] = 
{
	"0", //Dummy stepper
	"R",
	"F",
	"W",
	"K",
	"A",
	"AN" //Have to add another stepping point at 'N' for this
};

static const std::string reflectorAlphabets[] = 
{
	"", //Dummy alphabet
	"EJMZALYXVBWFCRQUONTSPIKHGD",
	"YRUHQSLDPXNGOKMIEBFZCWVJAT",
	"FVPJIAOYEDRZXWGCTKUQSBNMHL"
};
#endif