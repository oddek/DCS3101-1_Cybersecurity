#include "Enigma.h"

Enigma::Enigma(int rotorIds[3], int reflectorId, std::vector<std::string> _plugboardSettings): reflector(reflectorId, 'r')
{
	Rotor rotor1(rotorIds[0], 'L');
	Rotor rotor2(rotorIds[1], 'M');
	Rotor rotor3(rotorIds[2], 'R');
	rotors.push_back(rotor1);
	rotors.push_back(rotor2);
	rotors.push_back(rotor3);
	plugboardSettings = _plugboardSettings;
}

Enigma::~Enigma()
{

}

void Enigma::printEnigmaStatus()
{
	std::cout << "Enigma Status: \n\tPlugboard: \n\t";
	for(auto pair : plugboardSettings)
	{
		std::cout << pair << " ";
	} 

	std::cout << "\n\nRotor information from left to right: \n\n";

	for(auto rotor : rotors)
	{
		rotor.printRotorStatus();
	} 

	reflector.printRotorStatus();
}

void Enigma::setRotors(int r[3])
{

	for(int i = 0; i <= 2; i++)
	{
		Rotor rotor(r[i], r[i]);
		//rotor.setSteppingPoint(stepPoints[i])
		rotors.push_back(rotor);
		
	}
}

void Enigma::setOffset(int o[3])
{
	for(int i = 0; i < rotors.size(); i++)
	{
		rotors.at(i).setOffset(o[i] - 1);
	}

}

void Enigma::setRingSetting(int s[3])
{
	for(int i = 0; i < rotors.size(); i++)
	{
		rotors.at(i).setRingSetting(s[i] - 1);
	}

}

void Enigma::rotateRotors()
{	
	for(auto it = rotors.rbegin(); it != rotors.rend(); it++)
	{
		bool next = it->incrementOffset(rotors.at(1).isDoubleStep());
		if(!next) break;
	}	
	//printRotorStatus();
	
}

std::string Enigma::transform(std::string& input)
{
	std::string output;
	
	for(const char c : input)
	{
		rotateRotors();

		char temp = std::toupper(c);
		//Through the Plugboard
		temp = charThroughPlugboard(temp);

		//Through the rotors
		for(auto it = rotors.rbegin(); it != rotors.rend(); it++)
		{
			temp = it->getTransformedChar(temp);
		}
		//Through the reflector
		temp = reflector.getTransformedChar(temp);
		
		//Through the rotors backwards
		for(auto it = rotors.begin(); it != rotors.end(); it++)
		{
			temp = it->getInverseTransformedChar(temp);
		}

		temp = charThroughPlugboard(temp);

		//std::cout << "Input: " << c << " became: " << temp << "\n";
		output += temp;
	}
	return output;
}

char Enigma::charThroughPlugboard(char c)
{
	for(auto pair : plugboardSettings)
	{
		if(pair.front() == c) return pair.back();
		if(pair.back() == c) return pair.front();
	}
	return c;
}