#include <bits/stdc++.h>
using namespace std;


int main() {

/*
	Take some object, assign it a numerical value
	There are different ways to perform a hash on some object. We are going to learn about the rolling hash, which uses a polynomial function.


	p(x) = a0 + a1x + a2x^2 + a3x^3 + ... + anx^n

	p(x) --> rolling hash value
	x --> given constant
	a0,a1,...,an --> coefficients that change

	A -> 65, B -> 66, C -> 67, ... Z->90
	a -> 97, b -> 98, c -> 99, ... z -> 122

	Let's assume we are working with only lowercase characters.

*/
	//ascii operation
	//char character = 'c';
	//cout << (int)character;


	/*
	ai --> related to ascii values of each character in the string

	Instead of working with numbers 97,98,99,...,122 which are really big, we can simplify that to 0,1,2,3,...,25
	ascii value of character - 97
	OLD
	a -> 97, b -> 98, c -> 99, ... z -> 122
	NEW
	a -> 0, b -> 1, c -> 2, ....   z -> 25


	character-a to get better ascii value (easier to work with)
	*/

	//better version of assigning characters
	cout << 'c'-'a' << endl;


	/*
	p(x) = a0 + a1x + a2x^2 + a3x^3 + ... + anx^n
	ai --> value of character - 'a'
	Let's find a good value of x to use.
	a -> 0, b -> 1, c -> 2, ....   z -> 25
	Choose x > 25

	"ab", x = 10: p(10 for "ab") = 0 + 10(1) = 10
	"k", x = 10: p(10 for "k"): = 10

	0<= a0,a1,a2 ... <= 25
	
	value of x = 37 (> 25):
	x values will grow much faster than values of a0,a1,a2,...,an and as a result will prevent collision

	p(x) would exceed our maximum numerical value that C++ can hold if we just use this naive method with x > 25.

	SOLUTION: When we generate p(x), we want to do it modulo a huge number:

	p(x) = a0 % MOD + a1x % MOD + a2x^2 % MOD + ... + anx^n % MOD

	However, introducing a mod value can cause hashing collisions again. As a result, we want to have the MOD value really huge and also a prime number to minimize collisions.
	MOD = 10^9 + 7

	x > 25, by similar logic x being a prime number will be better than a composite number. x = 31,37,41,43,... are suitable options.

	WITH ALL CONDITIONS STATED,
	p(x,string) = (a0 % MOD + a1x % MOD + a2x^2 % MOD + ... + anx^n % MOD) % MOD
	p(x,string) will be the rolling hash value for an inputted string


	LET'S TRY TO IMPLEMENT THE ROLLING hash
	Given a string str (take input), output the rolling hash value of that string.

	1 <= length of string <= 10000 


	*/





}