#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>


typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
			unsigned long long w[5] = {0,0,0,0,0};
			unsigned long long hash_val = 0;
			std::string k2 = k;
			int size = k2.size()-1;
			for(int i = 0; i < k2.size(); i++)
			{
				k2[i] = letterDigitToNumber(k2[i]);
			}

			for(int i = 4; i >=0; i--) //w[i]
			{
				if(size >= 5)
				{
					for(int j = 0; j < 6; j++) //6 or more characters left in the string
					{
						hash_val += k2[size - j] * pow(36,j);
					}
					w[i] = hash_val;
					hash_val = 0;
					size -= 6;
				}
				else if(size < 0)  // we have calulated everything
				{
					break;
				}
				else      // for when the string size is less than 6 but not empty
				{
					for(int z = 0; z <= size; z++)
					{
						hash_val += k2[size - z] * pow(36, z);
					}
					w[i] = hash_val;
					hash_val = 0;
					size = -1;
				}
			}
			unsigned long long result = 0;
    	for(int i = 0; i < 5; i++)
    	{
    	  result += w[i] * rValues[i];
				//std::cout << "w[" << i << "] = " << w[i] << std::endl;
    	}
    	return result;
			
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if (letter >= 'a' && letter <= 'z') 
				{
          return letter - 'a';
        }
				else if (letter >= 'A' && letter <= 'Z') 
				{
        	return letter - 'A'; 
				}
				else if (letter >= '0' && letter <= '9') 
				{
          return letter - '0' + 26;
        } 
				else 
				{
          return 0;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
