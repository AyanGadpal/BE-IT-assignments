// Title : RSA Algorithm 
// @author : Ayan Gadpal, 43308 
// @brief : This is Assignment 1 of CL VII LAB, PICT SPPU To Demostrate working of RSA algorithm
// Date : 10.8.2020
#include <iostream>
#include<math.h>
#include<string.h>
using namespace std;


// Calculate the GCD
int gcd(int a, int b)
{
    while (b)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// Get the 'e' 
double getE(double phi)
{
    int flag =0;
    double e;
    for(e = 2;e<phi;e++)
    {
        flag = gcd(e,phi);
        if(flag==1)
            break;
    }

    return e;
}


// Driver code
int main()
{
    // RSA Variable
    double p,q,n,d,e,phi;
    
    // Currently take a static p and q
    p = 19;
    q = 61;    
    n = p*q; // Calculate n
    phi = (p-1)*(q-1); // Total number of co prime of 'n'

    e = getE(phi); // Get e (encryption key) such that, 1 < e < phi(n) AND e and phi n are co prime 

    d=fmod((1/e),phi); // Decryption key
 
    double message = 4;

    // Encryption and Decryption of message
    double c1 = pow(message,e);
    double m = pow(c1,d); 
    double c = fmod(c1,n);
    m=fmod(m,n);

    cout<<"p: "<<p<<"\n";
    cout<<"q: "<<q<<"\n";
    cout<<"n: "<<n<<"\n";
    cout<<"phi: "<<phi<<"\n";
    cout<<"e: "<<e<<"\n";
    cout<<"Original Message: "<<message<<"\n";
    cout<<"Encrypted Message: "<<c<<"\n";
    cout<<"Decrypted Message: "<<m<<"\n";


    
    // cout<<generate_coprime(n,phi);
    cout<<"\n";
    return 0;
}