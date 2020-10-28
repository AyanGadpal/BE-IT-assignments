/*====================================================
Auther : Ayan N Gadpal P11 43308
Code : CRT Algorithm basic
Date : Aug 25 2020
=====================================================*/
#include <iostream>
#include <vector>

#define long long long int
using namespace std;

int Mul_inv(int a, int m) 
{ 
    a = a%m; 
    for (int x=1; x<m; x++) 
       if ((a*x) % m == 1) 
          return x; 
    return 0;
} 


int CRT(std::vector<int> a, std::vector<int> m) {
	int product = 1;
	int result = 0;
	int size = a.size();

	for(int n : m)
		product *= n;

	std::vector<int> M(size);
	for(int i = 0; i < size; i++)
		M[i] = product / m[i];

	//Applyinig Multiplicative inverse of m_i to calculate x_i
	for(int i = 0; i < size; i++) {
		int x = a[i] * Mul_inv(M[i], m[i]) * M[i];
		//cout<<"x"<<i+1<<" = "<<x<<"\n";
		result += x;
	}

	return (result % product);
}


int main() {

	std::vector<int> a(3);
	std::vector<int> m(3);
	
    // Take user input
    for (int i = 0; i < 3; i++)
    {
        cout << "\nEnter a" << i << " : ";
        cin >> a[i];
        cout << "\nEnter m" << i << " : ";
        cin >> m[i];
    }

	cout<<"X is : "<<CRT(a, m)<<endl;
	return 0;
}