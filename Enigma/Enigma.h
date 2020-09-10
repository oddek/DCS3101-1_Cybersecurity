
#ifndef ENIGMA_H
#define ENIGMA_H

#include "Rotor.h"
#include <vector>
#include <algorithm>





class Enigma
{
public:
	Enigma(int rotorIds[3], int reflectorId);
	~Enigma();
	void setRotors(int r[3]);
	void setOffset(int o[3]);
	void setRingSetting(int s[3]);
	std::string transform(std::string& input);

	void printRotorStatus();


private:
	std::vector<Rotor> rotors;
	Rotor reflector;

	void rotateRotors();


};


#endif