
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h> 
#include<gmp.h>
#include <unistd.h>
#include <algorithm>
uintmax_t generateRandomNumber(uintmax_t min, uintmax_t max);



uintmax_t power(uintmax_t x, uintmax_t y, uintmax_t p)
{
	uintmax_t res = 1;
	x = x % p;

	if(x == 0) return 0;

	while(y > 0)
	{
		if(y & 1)
		{

			res = (res*x) % p;
		}
		y = y >> 1;
		x = (x*x) % p;
	}
	return res;
}


uintmax_t bitCount(uintmax_t n)
{
	uintmax_t count = 0;
	while(n)
	{
		count++;
		n >>= 1;
	}
	return count;
}

bool millerTest(int n, int d)
{
	uintmax_t a = generateRandomNumber(2, n-2);
	uintmax_t x = power(a,d,n);
	if(x == 1 || x == n-1) return true;

	while(d != n-1)
	{
		x = (x*x) % n;
		d *= 2;
		if (x == 1) return false;
		if (x == n-1) return true;
	}
	return false;
}


bool isPrime(uintmax_t n, uintmax_t k)
{
	if(n <= 3)
	{
		return n > 1;
	}
	else if(n % 2 == 0 || n % 3 == 0)
	{
		return false;
	}

	int d = n - 1;
	while(d % 2 == 0)
	{
		d /= 2;
	}

	for(int i = 0; i < k; i++)
	{
		if(millerTest(n, d) == false) return false;
	}
	return true;

	/*uintmax_t i = 5;

	while(i * i <= n)
	{
		if(n % i == 0 || n % (i+2) == 0)
		{
			return false;
		}
		i += 6;
	}
	return true;*/
}

uintmax_t generateRandomNumber(uintmax_t min, uintmax_t max)
{
	sleep(1);

	srand(time(nullptr));
	return rand() % (max - min + 1) + min;
}


uintmax_t generateRandomPrime(int bits)
{
	uintmax_t num = generateRandomNumber(pow(2, bits-1), pow(2, bits));

	num |= 1 << bits-1;
	num |= 1 << bits-2;
	num |= 1 << 0;
	while(true)
	{
		if(isPrime(num, 4)) return num;
		else num +=2;
	}
}

intmax_t modInv(uintmax_t a, uintmax_t m) 
{ 
    intmax_t m0 = m; 
    intmax_t y = 0, x = 1; 
  
    if (m == 1) 
      return 0; 
  
    while (a > 1) 
    { 
        // q is quotient 
        intmax_t q = a / m; 
        intmax_t t = m; 
  
        // m is remainder now, process same as 
        // Euclid's algo 
        m = a % m, a = t; 
        t = y; 
  
        // Update y and x 
        y = x - q * y; 
        x = t; 
    } 
  
    // Make x positive 
    if (x < 0) 
       x += m0; 
  
    return x; 
} 

void swap(uintmax_t &a, uintmax_t &b)
{
	uintmax_t temp = a;
	a = b;
	b = temp;
}

bool generateKeys(uintmax_t& N, uintmax_t& e, uintmax_t & d)
{
	uintmax_t k = 32;
	e = 65537;
	uintmax_t p;
	uintmax_t q;

	while(true)
	{
		p = 11;//generateRandomPrime(k/2);
		if(p % e != 1) break;
	}

	while(true)
	{
		q = 7;//generateRandomPrime(k - k/2);
		if(q % e != 1) break;
	}

	if(p < q)
	{
		swap(p, q);
	} 
	else if(p == q) 
	{
		std::cout << "P equals Q, returning false";
		return false;
	}

	std::cout << "P: " << p << " Num of bits: " << bitCount(p) << "\n";
	std::cout << "Q: " << q << " Num of bits: " << bitCount(q) << "\n";

	N = p * q;
	uintmax_t L = (p-1)*(q-1);
	d = modInv(e, L);

	return true;
}


uintmax_t encrypt(uintmax_t m, uintmax_t n, uintmax_t e)
{
	return power(m, e, n);
}

uintmax_t decrypt(uintmax_t m, uintmax_t n, uintmax_t d)
{
	return power(m, d, n);
}

uintmax_t stringToInt(std::string s)
{
	//Replace the ascii value of the string with the character. Add a 0 in front if it has less than 3 digits. 
	//Read in a 1 first, so that the 0 won't be deleted. 
	s.insert(0, "1");
	for(int i = s.size() - 1; i > 0; i--)
	{
		std::string replacementString = std::to_string((int)s.at(i));
		std::cout << "ReplacementString " << replacementString << " Size: " << replacementString.size() << "\n";
		while(replacementString.size() != 3)
		{
			std::cout << "NOT 3!!\n";
			replacementString.insert(0, "0");
		} 
		std::cout << "ReplacementString " << replacementString << " Size: " << replacementString.size() << "\n";

		s.replace(i, 1, replacementString);
	}
	return std::stoi(s.c_str());
}

std::string intToString(uintmax_t i)
{
	std::string s = std::to_string(i);
	s.erase(0, 1);

	for(int i = s.size()-3; i >= 0; i -= 3)
	{
		std::string substr = s.substr(i, 3);
		std::cout <<"substr: " << substr << "\n";
		int asc = std::stoi(substr.c_str());
		char c = asc;
		std::cout << "char " << c << "\n";
		
		s.replace(i, 3, std::string(1, c));
	}

	return s;
}

int main()
{
	std::cout << "Generating Keys\n";

	uintmax_t N, e, d;

	while(!generateKeys(N, e, d));
	std::cout << "N: " << N << "\n";
	std::cout << "e: " << e << "\n";
	std::cout << "d: " << d << "\n";

	const char* bytes = "d";

	std::string message = "D";
	uintmax_t intMessage = stringToInt(message);
	
	std::cout << "Original message: " << message << "\n";
	std::cout << "Converted to int is: " << intMessage << "\n";
	uintmax_t encrypted = encrypt(intMessage, N, e);
	std::cout << intMessage << " encrypted with Public is: " << encrypted << "\n";

	uintmax_t decrypted = decrypt(encrypted, N, d);
	std::cout << encrypted << " decrypted with Private is: " << decrypted << "\n";
	std::cout << "Decrypted to String is: \n" << intToString(decrypted) << "\n";

	uintmax_t encrypted2 = encrypt(intMessage, N, d);
	std::cout << intMessage << " encrypted with Private is: " << encrypted2 << "\n";

	uintmax_t decrypted2 = decrypt(encrypted2, N, e);
	std::cout << encrypted2 << " decrypted with Public is: " << decrypted2 << "\n";

}