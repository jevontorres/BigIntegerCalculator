#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt()
{
		base = 10;
		isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase)
{
		if (setbase < 2 || setbase > 36) {
				throw InvalidBaseException();
		}
		base = setbase;
		isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt() {}

/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input, int setbase)
{
		if (setbase < 2 || setbase > 36) {
				throw InvalidBaseException();
		}
		/************* You complete *************/
		isPositive = true;
		if (input < 0) {
				isPositive = false;
				input *= -1;
		}
		//cout<<input;
		base = setbase;
		int temp = 0;
		if (input == 0) {
				vec.push_back(input);
		}
		while (input > 0) {
				temp = input % base;
				vec.push_back(temp);
				//cout<<temp;
				input -= temp;
				input /= base;
		}
		//cout<<endl;
}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input strings will contain only
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=36]
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string& s, int setbase)
{
		if (setbase < 2 || setbase > 36) {
				throw InvalidBaseException();
		}
		/************* You complete *************/
		base = setbase;
		isPositive = true;
		//not right yet maybe?

		for (int i = s.size() - 1; i >= 0; i--) {
				if ((int)s[i] == 45) {
						isPositive = false;
				}
				else if ((int)s[i] <= 57) {
						int temp = (int)s[i] - 48;
						vec.push_back(temp);
				}
				else {
						int temp = (int)s[i] - 55;
						vec.push_back(temp);
				}
		}
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
*/
BigInt::BigInt(const BigInt& b)
{

		/************* You complete *************/
		*this = b;
}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  Overriding a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt& BigInt::operator=(const BigInt& b)
{

		/************* You complete *************/
		//WRONG
		if (this==&b){
			return *this;
		}
		vec.clear();
		base = b.base;
		isPositive = b.isPositive;
		for (unsigned int i=0; i<b.vec.size(); i++){
			 vec.push_back(b.vec[i]);
		}

		return *this;
}

//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string()
{

		/************* You complete *************/
		vector<char> intString;
		//cout<<vec.size();
		for (int i = vec.size() - 1; i >= 0; i--) {
				if (vec[i] <= 9) {
						char temp = (char)vec[i] + 48;
						//cout<<temp;
						intString.push_back(temp);
				}
				else {
						char temp = vec[i] + 55;
						intString.push_back(temp);
				}
		}

		string s;
		if (!isPositive) {
				s += '-';
		}
		for (char c : intString) {
				s += c;
		}
		return s;
		//return "";//for now
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const
{

		/************* You complete *************/
		
		int temp = 0;
		BigInt intmax(INT_MAX, base);
		int mini = -1 * INT_MAX;
		BigInt intmin(mini, base);
		BigInt one(-1, base);
		intmin -= one;
	
		if (*this >= intmax) {
				return INT_MAX;
		}
		if (*this <= intmin) {
				return INT_MIN;
		}
		for (int i = vec.size() - 1; i >= 0; i--) {
				temp += (int)vec[i] * (pow(base, i));
		}
		if (!isPositive) {
				temp *= -1;
		}
		return temp;
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt& b) const
{
		if (base != b.base) {
				throw DiffBaseException();
		}
		/************* You complete *************/

		int asize = vec.size();
		int bsize = b.vec.size();
		//check sign
		if (isPositive != b.isPositive) {
				cout << "";
				if (isPositive && (!b.isPositive)) {
						return 1;
				}
				else
						return -1;
		}

		//size not equal
		if (asize != bsize) {
				if (asize > bsize) {
						if (!isPositive && !b.isPositive) {
								return -1;
						}
						else
								return 1;
				}
				else {
						if (!isPositive && !b.isPositive) {
								return 1;
						}
						else
								return -1;
				}
		}

		for (int i = asize - 1; i >= 0; i--) {
				int lhs = vec[i];
				int rhs = b.vec[i];
				if (lhs > rhs) {
						if (!isPositive && !b.isPositive) {
								return -1;
						}
						return 1;
				}
				else if (lhs < rhs) {
						if (!isPositive && !b.isPositive) {
								return 1;
						}
						return -1;
				}
		}
		//HINT:
		//1. do NOT call the to_int() or to_string() function
		//2. do NOT convert bigInt to other datatypes first (e.g., long long, int)

		//First let's compare the signs
		//    - if the signs aren't the same,
		//              how do you know which one is larger?

		//If they have the same sign, let's compare their vec sizes
		//    - what if both are positive, but a's vec is larger (a or b is larger?)
		//    - other cases?

		//If they have the same vec size, let's compare their digits one by one
		// Starting from the most-significant digits. --> in what vector position?
		// Remember that the BigInt vectors are in reverse order!
		//    - what if both are positive, but the digit of a is greater than that of b (a or b is larger?)
		//    - other cases?

		//If ALL digits are the same, then they MUST be equal!!
		return 0;
}

//Call the compare function above to check if a == b
bool operator==(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		if (a.compare(b) == 0) {
				return true;
		}
		else
				return false;
}

//Call the compare function above to check if a != b
bool operator!=(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		if (a.compare(b) != 0) {
				return true;
		}
		else
				return false;
}

//Call the compare function above to check if a <= b
bool operator<=(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		if (a.compare(b) == 0 || a.compare(b) == -1) {
				return true;
		}
		else {
				return false;
		}
}

//Call the compare function above to check if a >= b
bool operator>=(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		if (a.compare(b) == 0 || a.compare(b) == 1) {
				return true;
		}
		else {
				return false;
		}
}

//Call the compare function above to check if a > b
bool operator>(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		if (a.compare(b) == 1) {
				return true;
		}
		else {
				return false;
		}
}

//Call the compare function above to check if a < b
bool operator<(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		if (a.compare(b) == -1) {
				return true;
		}
		else {
				return false;
		}
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator+(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		BigInt copy = a;
		copy += b;
		return copy; 
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt& BigInt::operator+=(const BigInt& b)
{
		if (base != b.base) {
				throw DiffBaseException();
		}
		/************* You complete *************/
		int asign = 1;
		int bsign = 1;
		int carry = 0;
		int aval = 0;
		int bval = 0;
		
		if (!isPositive){
			asign=-1;
		}
		if (!b.isPositive){
			bsign=-1;
		}
		//both are positive
		if(isPositive&&b.isPositive){
			for (unsigned int i = 0; i < (max(vec.size(), b.vec.size())); i++) {
					if (i < vec.size()) {
							aval = vec[i];
					}
					else {
							aval = 0;
							vec.push_back(0);
					}
					if (i < b.vec.size()) {
							bval = b.vec[i];
					}
					else {
							bval = 0;
					}

					int temp = asign*aval + bsign*bval + carry;
					carry = temp / base; //int division will just give 1 if needed
					vec[i] = temp % base;
			}
			
			if (carry) { //any value
					vec.push_back(carry);
			}
		}
		else if(isPositive&&!b.isPositive){
				BigInt copyB = b;
				BigInt copyA = *this;
				copyB.isPositive = true;
				if(copyA==copyB){
					vec.clear();
					vec.push_back(0);
					isPositive=true;
					return *this;
				}
				if (copyA>copyB){
					*this-=copyB;
				}
				else{
					copyB-=copyA;
					copyB.isPositive = false;
					*this=copyB;
				}
		}
		else if(!isPositive&&b.isPositive){
			BigInt copyB = b;
			isPositive = true;
			if (*this>copyB){
				*this-=copyB;
				isPositive=false;
			}
			else{
				isPositive = true;
				copyB-=*this;
				*this=copyB;
			}
		}
		else if(!isPositive&&!b.isPositive){
			isPositive=true;
			BigInt copyB = b;
			copyB.isPositive = true;
			asign=1;
			bsign=1;
			for (unsigned int i = 0; i < (max(vec.size(), copyB.vec.size())); i++) {
					if (i < vec.size()) {
							aval = vec[i];
					}
					else {
							aval = 0;
							vec.push_back(0);
					}
					if (i < copyB.vec.size()) {
							bval = copyB.vec[i];
					}
					else {
							bval = 0;
					}

					int temp = asign*aval + bsign*bval + carry;
					carry = temp / base; //int division will just give 1 if needed
					vec[i] = temp % base;
			}
			
			if (carry) { //any value
					vec.push_back(carry);
			}
			isPositive=false;
		}
		
		//delete extra 0s. ie (009 should be 9) //somehow i dont need this anymore?
//     if (vec[vec.size() - 1] == 0 && vec.size()!=1) {
//         int i=1;
//         while(vec[vec.size()-i]==0){
//           vec.erase(vec.begin() + vec.size() - i);
//           i++;
//         }
//     }
		
		if (this->to_int()<0){
			isPositive = false;
		}
	
		return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator-(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		BigInt copy = a;
		copy -= b;
		return copy;
}

/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt& BigInt::operator-=(const BigInt& b)
{
		if (base != b.base) {
				throw DiffBaseException();
		}
		/************* You complete *************/
		//int carry = 0;
		int aval = 0;
		int bval = 0;
		if (*this==b){
			vec.clear();
			vec.push_back(0);
			isPositive=true;
		}
		else if(isPositive&&b.isPositive){
			if(*this>b){
				for (unsigned int i = 0; i < (max(vec.size(), b.vec.size())); i++) {
				
				if(i < vec.size()) {
						aval = vec[i];
				}
				else {
						aval = 0;
						vec.push_back(0);
				}
				if (i < b.vec.size()) {
						bval = b.vec[i];
				}
				else {
						bval = 0;
				}
			
				aval -= bval;
				if (aval < 0) {
					if(i==vec.size()-1){
						aval*=-1;
						vec[i]=aval;
						isPositive=false;
					}
					else{
						vec[i] = base + aval;
						vec[i + 1] = vec[i + 1] - 1;
					}
				}
				else {
						vec[i] = aval;
				}
		}
			}
			else{
				BigInt copyB = b;
				BigInt copyA = *this;
				copyB-=copyA;
				*this=copyB;
				isPositive=false;
			}
		}
		else if(isPositive&&!b.isPositive){
			BigInt copyB = b;
			copyB.isPositive = true;
			*this+=copyB;
		}
		else if(!isPositive&&b.isPositive){
			BigInt copyB = b;
			BigInt copyA = *this;
			copyA.isPositive = true;
			copyB+=copyA;
			*this=copyB;
			isPositive = false;
		}
		else if(!isPositive&&!b.isPositive){
			BigInt copyA = *this;
			BigInt copyB = b;
			copyA.isPositive = true;
			copyB.isPositive = true;
			if (copyA>copyB){
				copyA-=copyB;
				copyA.isPositive = false;
				*this = copyA;
			}
			else{
				copyB-=copyA;
				*this = copyB;
				isPositive = true;
			}
		}
		
		 //figure out two negatives and fix when answer goes into neg during subtract
		
		//based on how this is, if 2 digit turns to 1 digit it leaves the zero
		//that got added to help with subtraction. this removes
		//if last digit is 0 and 0 is not only digit
		int SIZE = vec.size(); //must be declared outside
		if (vec[SIZE - 1] == 0 && SIZE!=1) {
				//vec.erase(vec.begin() + vec.size() - 1);
				int i=1;
				while(vec[SIZE-i]==0&&SIZE-i!=0){
					vec.erase(vec.begin() + SIZE - i);
					i++;
				}
		}
		
		return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator*(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		BigInt copy = a;
		copy*=b;
		return copy; //works?
}

/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt& BigInt::operator*=(const BigInt& b)
{
		if (base != b.base) {
				throw DiffBaseException();
		}
		/************* You complete *************/
		BigInt zero(0,base);
		BigInt one(1,base);
		BigInt negone(-1,base);
		
		//begin with base cases
		if (*this==zero||b==zero){
			vec.clear();
			vec.push_back(0);
			isPositive = true;
			return *this;
		}
		else if(*this==one){
			*this=b;
			return *this;
		}
		else if(b==one){
			return *this;
		}
		else if(*this==negone){
			*this=b;
			if(isPositive){
				isPositive = false;
			}
			else{
				isPositive=true;
			}
			return *this;
		}
		else if(b==negone){
			if(isPositive){
				isPositive = false;
			}
			else{
				isPositive=true;
			}
			return *this;
		}
		 
	 BigInt total(0, base);

	for (unsigned int i=0; i < b.vec.size(); i++) {
		BigInt temp(base);
		int product;
		int carry = 0;
		for (unsigned int j=0; j < i; j++) {
			temp.vec.push_back(0);
		}
		
		for (unsigned int k=0; k < vec.size(); k++) {
			product = vec[k]*b.vec[i] + carry;
			temp.vec.push_back(product%base);
			carry = product/base;
		}
		
		if (carry != 0) {
			temp.vec.push_back(carry);
		}
		
		total += temp;
	}
	
	if ( (isPositive && b.isPositive) || (!isPositive && !b.isPositive) ) {
		total.isPositive = true;
	}
	else {
		total.isPositive = false;
	}
	
	*this = total;
	return *this;

}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator/(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		BigInt copy = a;
		copy/=b;
		return copy; //for now
}

/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt& BigInt::operator/=(const BigInt& b)
{
		if(base != b.base){
				throw DiffBaseException();
		}
		if(b.vec.size() == 1 && b.vec[0] == 0){
				throw DivByZeroException();
		}
		/************* You complete *************/
	BigInt quotient(base);
	BigInt remainder(base);
	divisionMain(b,quotient, remainder);
	*this = quotient;
	return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator%(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		BigInt copy = a;
		copy%=b;
		return copy; //for now
}

/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt& BigInt::operator%=(const BigInt& b)
{
		if(base != b.base){
				throw DiffBaseException();
		}
		if(b.vec.size() == 1 && b.vec[0] == 0){
				throw DivByZeroException();
		}
		/************* You complete *************/
	BigInt quotient(base);
	BigInt remainder(base);
	divisionMain(b, quotient, remainder);
	*this = remainder;
	return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt& b, BigInt& quotient, BigInt& remainder)
{

		/************* You complete *************/
		BigInt div = b;
		div.isPositive = true;
		BigInt rem(base);
		int c = 0, n = vec.size();
		for(int i = 0; i < n; i++){
				rem.vec.insert(rem.vec.begin(),vec[n-i-1]);
				if(i > 0 && rem.vec[rem.vec.size() - 1] == 0){
						rem.vec.pop_back();
				}
				while(rem.compare(div) != -1){
						rem -= div;
						c++;
				}
				quotient.vec.insert(quotient.vec.begin(),c);
				c = 0;
		}
		remainder = rem;

		while((quotient.vec[quotient.vec.size()-1] == 0) && quotient.vec.size() > 1){
				quotient.vec.pop_back();
		}
		if(((!isPositive && b.isPositive) || (isPositive && !b.isPositive)) && quotient.to_int() != 0)
				quotient.isPositive = false;
		else
				quotient.isPositive = true;
		
		if(!isPositive && remainder.to_int() != 0)
				remainder.isPositive = false;
		else
				remainder.isPositive = true;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const BigInt& a, const BigInt& b)
{

		/************* You complete *************/
		BigInt copy = a;
		copy.exponentiation(b);
		return copy; //for now
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt& BigInt::exponentiation(const BigInt& b)
{
		if(base != b.base){
				throw DiffBaseException();
		}
		if(!b.isPositive){
				throw ExpByNegativeException();
		}
		/************* You complete *************/

		//attempting with recursion instead of while
		if(b.vec[0] == 0 && b.vec.size() == 1){
				BigInt one(1,base);
				*this = one;
		}
		else if(b.vec[0] == 1 && b.vec.size() == 1)
				return *this;
		else if((b.to_int() % 2 == 0) && b.vec.size() > 0){
				BigInt copyB = b;
				return *this *= exponentiation(copyB/BigInt(2,base));
		}
		else if((b.to_int() % 2 != 0) && b.vec.size() > 0){
				BigInt copyA = *this;
				BigInt copyB = b;
				copyB -= BigInt(1,base);
				*this *= exponentiation(copyB/ BigInt(2,base));
				*this *= copyA;
		}
		return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt& a, const BigInt& b, const BigInt& m)
{

		/************* You complete *************/
		BigInt copy = a;
		copy.modulusExp(b,m);
		return copy; //for now
}

/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt& BigInt::modulusExp(const BigInt& b, const BigInt& m)
{
		if (base != b.base || base != m.base) {
				throw DiffBaseException();
		}
		if (!b.isPositive) {
				throw ExpByNegativeException();
		}
		/************* You complete *************/

		BigInt ans(1,base);
		BigInt zero(0, base);
		
			if(b.vec[0]==0 && b.vec.size()==1){
				ans = *this % b;
			}
			else if(b.vec[0]==1 && b.vec.size()==1){
				ans = *this % b;
			}
			else{
				BigInt temp = b;
				while(temp.compare(zero) != 0){
					if(temp.vec[0]%2==0){
						temp/=BigInt(2,base);
						*this *= (*this);
						*this %= m;
					}
					else{
						ans = (ans*(*this)) % m;
						temp -= BigInt(1,base);
					}
				}
			}
			*this = ans;
			return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************