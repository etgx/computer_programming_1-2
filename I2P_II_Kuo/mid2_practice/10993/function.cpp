/**
I2P - Kuo HW2 Problem 1 | NTHUOJ 10993 - Polynomial class
Create a class Polynomial. The internal representation of a Polynomial is an array of terms. Each term contains a coefficient and an exponent, e.g., the term 2x4 has the coefficient 2 and the exponent 4.
Use a 51-element array, coefficients, of digits to store each coefficient.
Use a integer variable, greatestPower, to store an exponent.
Provide public member functions that perform each of the following tasks:
Adding two Polynomial.
Subtracting two Polynomial.
Multiplying two Polynomial.
Printing coefficients of the Polynomial in descending order.

Note:

1. This problem involves three files.

function.h: Class definition of Polynomial.
function.cpp: Member-function definitions of Polynomial.
main.cpp: A driver program to test your class implementation.
You will be provided with main.cpp, and asked to implement function.h and function.cpp.

function.h

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>

class Polynomial
{

public:
    Polynomial();
    Polynomial(const int , const int [51]);
    Polynomial add( const Polynomial) const; // add function
    Polynomial subtract( const Polynomial ) const; // subtract function
    Polynomial multiplication( const Polynomial ) const; // multiplication function
    void output() const;
private:
    int coefficients[101]; // integer coefficients
    int greatestPower; // integer greatestPower
}; // end class Polynomial

#endif

main.cpp

#include <iostream>
#include <stdio.h>
#include <string>
#include "function.h"
using namespace std;

int main()
{
    int greatestPower1, greatestPower2;
    int coefficient1[51], coefficient2[51];
    Polynomial ans;

    cin>>greatestPower1;
    for(int i = greatestPower1 ; i >= 0; i--)
    {
        cin>>coefficient1[i];
    }
    cin>>greatestPower2;
    for(int i = greatestPower2 ; i >= 0 ; i--)
    {
        cin>>coefficient2[i];
    }
    Polynomial a(greatestPower1, coefficient1), b(greatestPower2, coefficient2) ;

    ans = a.add( b );
    ans.output();
    cout << endl;

    ans = a.subtract( b );
    ans.output();
    cout << endl;

    ans = a.multiplication( b );
    ans.output();
    cout << endl;

} // end main


2. For OJ submission:
    Step 1. Submit only your function.cpp into the submission block.
    (***Note that you don’t need to submit your function.h.)
    Step 2. Check the results and debug your program if necessary.

Input
There are four lines.
The first two lines represent the greatest power and the corresponding coefficients of the first polynomial.
The last two lines represent the greatest power and the corresponding coefficients of the second polynomial.
Note that the coefficients are in descending order and each element is separated by a blank.

Output
Your program should print the coefficients of the sum, difference and product of these two polynomials in descending order, respectively.
Note that every answer should be followed by a new line character.

Sample Input  
2
1 2 3
3
1 1 1 1

Sample Output  
1 2 3 4
-1 0 1 2
1 3 6 6 5 3
**/

#include <iostream>
#include "function.h"

#define MAX_COEF_LEN 101

Polynomial::Polynomial(){
    this->greatestPower = 0;
    for(int i = 0; i < MAX_COEF_LEN; i++){
        this->coefficients[i] = 0;
    }
};

Polynomial::Polynomial(const int greatestPower, const int coefficients[51]){
    this->greatestPower = greatestPower;
    for(int i = greatestPower; i >= 0; i--){
        this->coefficients[i] = coefficients[i];
    }

    for(int i = greatestPower + 1; i < MAX_COEF_LEN; i++){
        this->coefficients[i] = 0;
    }
}

Polynomial Polynomial::add(const Polynomial poly) const{ // add function
    int power = poly.greatestPower > this->greatestPower? poly.greatestPower : this->greatestPower;
    int coff[MAX_COEF_LEN] = {0};

    for(int i = 0; i <= power; i++){
        coff[i] = this->coefficients[i] + poly.coefficients[i];
    }

    return Polynomial(power, coff);
}

Polynomial Polynomial::subtract(const Polynomial poly) const{ // subtract function
    int power = poly.greatestPower > this->greatestPower? poly.greatestPower : this->greatestPower;
    int coff[MAX_COEF_LEN] = {0};

    for(int i = 0; i <= power; i++){
        coff[i] = this->coefficients[i] - poly.coefficients[i];
    }

    return Polynomial(power, coff);
}

Polynomial Polynomial::multiplication(const Polynomial poly) const{ // multiplication function
    int power = this->greatestPower + poly.greatestPower;
    int coff[MAX_COEF_LEN] = {0};

    for(int i = 0; i <= this->greatestPower; i++){
        for(int j = 0; j <= poly.greatestPower; j++){
            coff[i + j] = coff[i + j] + (this->coefficients[i] * poly.coefficients[j]);
        }
    }

    return Polynomial(power, coff);
}

void Polynomial::output() const{
    std::cout << this->coefficients[this->greatestPower];
    for(int i = this->greatestPower - 1; i >= 0; i--){
        std::cout << " " << this->coefficients[i];
    }
}