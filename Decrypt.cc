#include <cmath>

long long Decrypt(long long b, long long e, long long m) //DECRYPTS
{
    //Declaring Variables
    //This section uses algorithms from Wikipedia; specifically the Right-to-left binary method under Modular Exponentiation. It has been implemented below
    long long result=1;
    b=b%m;
    while (e>0)
    {
        if (e%2==1)
            result=(result*b)%m;
        e=e>>1;
        b=(b*b)%m;
    }
    return result;
}