#include <math.h>
#include <iostream>
#include <vector>


namespace threads {


inline bool IsPrime(unsigned int a_num)
{
	if(a_num < 2) {
        return false;
    }
    if(a_num == 2) {
        return true;
    }

    if(a_num % 2 == 0) {
        return false;
    }

    for(unsigned int i = 3; i < a_num/2; i += 2) {
        if(a_num % i == 0) {
            return false;
        }
    }
    return true;
}

inline bool isSumDigits0(unsigned int a_num) {
    unsigned char sumDigits = 0;
    for ( ; a_num > 0 ; a_num /= 10) {
        sumDigits += (a_num % 10);
    }

    return sumDigits % 10 == 0;
}

inline bool isPolyndrum(unsigned int a_num) {
    std::vector<unsigned char> asDigits;
    asDigits.reserve(20);

    for ( ; a_num > 0 ; a_num /= 10) {
        asDigits.push_back(a_num % 10);
    }

    size_t front = 0;
    size_t back = asDigits.size();
    while (front < back) {
        if (asDigits[front] != asDigits[back]) {
            return false;
        }
        --front;
        --back;
    }
    return true;
}

inline void IsPrimeActFunc(unsigned int a_num)
{
	if (IsPrime(a_num)) {
		std::cout << a_num <<" is prime\n" << std::endl;
	} else {
		std::cout << a_num << " is NOT a prime\n" << std::endl;
	}
} 

inline void IsSumOfDigits0ActFunc(unsigned int a_num)
{
	if (isSumDigits0(a_num)) {
		std::cout << a_num <<" Sum of Digits is 0\n" << std::endl;
	} else {
		std::cout << a_num << " Sum of Digits is NOT 0\n" << std::endl;
	}
} 

inline void IsPolyndrumActFunc(unsigned int a_num)
{
	if (isPolyndrum(a_num)) {
		std::cout << a_num <<" is Polyndrom\n" << std::endl;
	} else {
		std::cout << a_num << " is NOT Polyndrom\n" << std::endl;
	}
} 




}//threads