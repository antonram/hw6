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
			std::size_t substrIndex = 0;
			std::size_t wIndex = 4;
			unsigned long long w[5] = {0, 0, 0, 0, 0};
			for(int i = (int) k.size() -1; i >= 0; i--) {
			//		std::cout << substrIndex << " " << w[wIndex] << std::endl;
				w[wIndex]	+= pow(36, substrIndex)*letterDigitToNumber(k[i]);
				substrIndex++;
				if(substrIndex == 6) {
					wIndex--;
					substrIndex = 0;
				}
			}

			HASH_INDEX_T r[5];

			HASH_INDEX_T hash = 0;

			for(std::size_t i = 0; i < 5; i++) {
				std::cout << w[i] << std::endl;
				r[i] = rValues[i];
				hash += r[i]*w[i];
			}

			return hash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				HASH_INDEX_T result = 0;

				if(letter >= 'a') {
					result = letter - 'a';
				}
				else if(letter >= 'A' && letter <= 'Z') {
					result = letter - 'A';
				}
				else{
					result = letter - 22;
				}

				return result;

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
