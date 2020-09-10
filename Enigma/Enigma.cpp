#include "Enigma.h"

Enigma::Enigma(): reflector(reflectorAlphabets[1])
{
}

Enigma::~Enigma()
{

}

void Enigma::setRotors(int r[3])
{
	for(int i = 0; i <= 2; i++)
	{
		rotors.push_back(Rotor(rotorAlphabets[r[i]]));
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
		bool next = it->incrementOffset();
		if(!next) break;
	}		
}

std::string Enigma::transform(std::string& input)
{
	std::string output;
	
	for(const char c : input)
	{
		rotateRotors();

		//Through the rotors
		char temp = std::toupper(c);

		//temp = rotors.at(0).getTransformedChar(temp);
	
		
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
		

		//temp = rotors.at(0).getInverseTransformedChar(temp);

		output += temp;
	}
	return output;
}


