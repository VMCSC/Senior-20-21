#include <bits/stdc++.h>
using namespace std;


/*
A class is something that has objects that have certain properties. For example, every person in CSC has the following properties:

Wears glasses/ does not wear glasses
They have a certain age
Gender
Weight
Grade
Height
Preferred language
Preferrred drink


C++ struct: Very similar to a class. The only recognizable differences are syntax and security.


struct <Name of your struct> {
	//properties of objects in the class
} <certain containers or values predetermined as objects>;


Example 1: Struct named CSCMember:
Properties: Wears glasses (true/false), age, preferred language
Pretermined objects: kevin, evan, joshua

*/

struct CSCMember {
	bool glassesUser;
	int age;
	string preferredLang;
} kevin,evan,joshua,weirdPeople[5];

struct keys {
	int num;
};

int main() {
	kevin.glassesUser = false;
	kevin.age = 17;
	kevin.preferredLang = "English";
	cout << kevin.age << endl;


	weirdPeople[2].age = 15;


	//not predetermined
	int joe;
	//similarly
	CSCMember lily;
	lily.glassesUser = false;
	lily.age = 16;
	lily.preferredLang = "English";
	
}
