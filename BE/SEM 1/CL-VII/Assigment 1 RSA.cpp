// Title : RSA Algorithm 
// @author : Ayan Gadpal, 43308 
// @brief : This is Assignment 1 of CL VII LAB, PICT SPPU To Demostrate working of RSA algorithm
// Date : 10.8.2020
#include <iostream>
#include<math.h>
#include<string.h>
using namespace std;

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



int main()
{
    double p,q,n,d,e,phi,flag;
    
    // Currently take a static p and q
    p = 19;
    q = 61;    
    n = p*q;
    phi = (p-1)*(q-1);

    e = getE(phi);

    d=fmod((1/e),phi);
 
    double message = 4;
    double c1 = pow(message,e); //encrypt the message
    double m = pow(c1,d); 
    double c=fmod(c1,n);
    m=fmod(m,n);

    cout<<"p: "<<p<<"\n";
    cout<<"q: "<<q<<"\n";
    cout<<"n: "<<n<<"\n";
    cout<<"phi: "<<phi<<"\n";
    cout<<"e: "<<e<<"\n";
    cout<<"Original Message: "<<message<<"\n";
    cout<<"Decrypted Message: "<<m<<"\n";
    cout<<"Encrypted Message: "<<c<<"\n";

    
    // cout<<generate_coprime(n,phi);
    cout<<"\n";
    return 0;
}