#include <bits/stdc++.h>
using namespace std;

#define ll long long
string N,H;
const ll MOD = 44654641650887;

/*
p(x) = a0 + a1x + a2x^2 + a3x^3 + ... + anx^n
precalculate values for x^i, i in range(0,length of string)
x^k = x * x^(k-1)

p(x) needs to be taken by a prime modulus, and so we should take the x values mod the same prime number

Find a way to check if one string is a permutation of another really fast

IF A STRING IS A PERMUTATION OF ANOTHER, WHAT DO THEY HAVE IN COMMON?
Frequency of each character is the exact same!
They are of the same size

Size of N --> nSize 
Size of H --> hSize

Consider all substrings of H that have the same size as N (= nSize), check if their frequency of all characters is the same, and if so we need to store the permutation somehow (store the rolling hash values)

Substrings of H to consider:
[0,nSize-1],[1,nSize],[2,nSize+1],....,[hSize-nSize,hSize-1]

Here's one thing we can take in consideration when getting frequencies of every character in the substrings:
"abcdefabcedef"
abcde
bcdef
Frequency of every character is almost the same between 2 index- adjacent substrings. 
frequency[string[currentIndex]] += 1;
frequency[string[currentIndex-stringSize]] -= 1


LET'S SAY WE ARE GOING TO A SIZE OF n
p(x) = (a0 + a1x + a2x^2 + a3x^3 + ... + a(n-1)x^(n-1)) % MOD
For the next substring
p(x) = (a1 + a2x + a3x^2 + ... + anx^(n-1)) % MOD

6 % 5 = 1
6/2 = 3
1/2 = 0

p(x) = (a0x^(n-1)+a1x^(n-2)+a2x^(n-3)+...+a(n-1)) % MOD --> string of size n

p(x)= (a1x^(n-1)+a2x^(n-2)+a3x^(n-3)+...+an) % MOD

TO GO FROM PREVIOUS p(x) TO THE NEXT:
Subtract a0x^(n-1)
Multiply the remaining value by x
Add an

((a*b)% MOD) = ((a%MOD)*(b%MOD)) % MOD


*/

ll powerArray[200005];
int nSize;



ll createHash(string s) {
	ll val = 0;
	for (int i = 0; i < s.size(); i++) {
		val += (powerArray[nSize-i-1]*(s[i]-'a')) % MOD;
		val = val % MOD;
	}

	return val;
}


unordered_set<ll> rollHashValues;

int main() {
	cin >> N >> H;
	powerArray[0] = 1;
	for (int i = 1; i < 200005; i++) {
		powerArray[i] = (powerArray[i-1]*37) % MOD;
	}
	nSize = N.size();
	int hSize = H.size();
	//build frequency arrray for N
	int nFreq[26];
	memset(nFreq,0,sizeof(nFreq));
	for (char c : N) {
		nFreq[c-'a']++;
	}
	int hFreq[26]; //frequency not of H, but instead the current substring of H that we are considering
	//FIRST SUBSTRING TO CONSIDER, THIS IS THE FREQUENCY ARRAY
	memset(hFreq,0,sizeof(hFreq));
	for (int i = 0; i < nSize; i++) {
		hFreq[H[i]-'a']++;
	}
	bool permutation = true;
	for (int i = 0; i < 26; i++) {
		if (hFreq[i] != nFreq[i]) {
			permutation = false;
			break;
		}
	}
	ll hashVal = createHash(H.substr(0,nSize));
	if (permutation) {
		//insert the rolling hash value
		rollHashValues.insert(hashVal);
	}
	for (int idx = nSize; idx < hSize; idx++) {
		//modify the frequency array
		hFreq[H[idx]-'a']++;
		hFreq[H[idx-nSize]-'a']--;
		/*
		Subtract a0x^(n-1)
		Multiply the remaining value by x
		Add an
		*/
		hashVal -= ((H[idx-nSize]-'a')*powerArray[nSize-1]) % MOD;
		/*
		taking % of a negative number will result in a value that is in the range -modulus < value <= 0
		ADD MODULUS TO ADD SIDES
		0 < value + modulus <= modulus
		(value + modulus)%modulus --> between 0 and up to but not including the modulus value
		*/
		hashVal = (hashVal + MOD) % MOD;
		hashVal = (hashVal*37) % MOD;
		hashVal += (H[idx]-'a');
		hashVal %= MOD;



		permutation = true;
		for (int i = 0; i < 26; i++) {
			if (hFreq[i] != nFreq[i]) {
				permutation = false;
				break;
			}
		}
		if (permutation) {
			//insert the rolling hash value
			rollHashValues.insert(hashVal);
		}
	}
	//output --> number of different permutations
	cout << rollHashValues.size() << endl;



}