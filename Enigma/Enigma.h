
#ifndef ENIGMA_H
#define ENIGMA_H

#include "Rotor.h"
#include <vector>
#include <algorithm>





class Enigma
{
public:
	Enigma(int rotorIds[3], int reflectorId, std::vector<std::string> _plugboardSettings);
	~Enigma();
	void setRotors(int r[3]);
	void setOffset(int o[3]);
	void setRingSetting(int s[3]);
	std::string transform(std::string& input);

	void printEnigmaStatus();


private:
	std::vector<Rotor> rotors;
	Rotor reflector;
	std::vector<std::string> plugboardSettings;
	char charThroughPlugboard(char c);
	void rotateRotors();


};


#endif