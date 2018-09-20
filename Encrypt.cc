#include <time.h>
#include <cstdlib>
#include <iostream>

bool isPrime(long long number) //CHECKS IF NUMBER IS PRIME
{
    //Testing all numbers
    for (long long i=2; i<number; i++)
    {
        //If a factor is found, number is not prime and we can exit
        if (number%i==0)
        {
            return false;
        }
    }
    //if no factors are found, we know number is prime and thus we can exit
    return true;
}

long long Encrypt(long long b, long long e, long long m){ //ENCRYPTS
    //Getting required values. These are independent of what is being encrypted
    
    //Declaring variables
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

long long GetP(){//GENERATE RANDOM PRIME NUMBER
    srand(time(NULL));
    //Generating a random number between 1 and the square root of long long max. (this is done so that it is imposible for n to exceed long long limitations)
    //Additionally, we have to ensure when multiplying by max ACII value, we don't have overflow!
    long long p=rand() % 500 + 1;
    //Checking if primality is true/false and assuring number is greater than 10000 for security integrity
    while (isPrime(p)==false || p<100){
        //If number failed primality test, generate new # and test primality!
        p=rand() % 500 + 1;
    }
    return p;
}

long long GetQ() //GENERATE RANDOM PRIME NUMBER
{
    //Generating a random number between 1 and the square root of long long max. (this is done so that it is imposible for n to exceed long long limitations)
    //Additionally, we have to ensure when multiplying by max ACII value, we don't have overflow!
    long long q=rand() % 500 + 1;
    //Checking if primality is true/false and assuring number is greater than 10000 for security integrity
    while (isPrime(q)==false || q<100){
        //If number failed primality test, generate new # and test primality!
        q=rand() % 500 + 1;
    }
    return q;
}

long long GetN(long long p, long long q) //GET N=PQ
{
    //Declaring variables and calculating n.
    long long n=p*q;
    //If n<0, then p*q resulted in an overflow which results in a negative number. This should never happen due to how p and q is generated.
    if (n<0){
        std::cout<<"FATAL ERROR! PROGRAM TERMINATING"<<std::endl;
        std::cout<<"Reason: N exceeded system limitations"<<std::endl;
    }
    return n;
}


long long GetPHI(long long p, long long q) //GETS PHI=(p-1)*(q-1)
{
    //Declaring variables and getting the value of PHI
    long long PHI=(p-1)*(q-1);
    return PHI;
}

long long GetE(long long PHI) //GENERATE RANDOM PRIME NUMBER<PHI
{
    srand(time(NULL));
    //Generate random number between 1 and PHI
    long long e=rand() % PHI + 1;
    //Checking if primality is true/false
    while (isPrime(e)==false)
    {
        //If number failed primality test, generate new # and test primality!
        e=rand() % PHI + 1;
    }
    return e;
}

long long GetD(long long PHI, long long e) //GETS PRIVATE KEY
{
    //Declaring Variables (q is quotient, r is remainder)
    long long s1;
    long long t1;
    long long r1;
    long long q1;
    long long s2;
    long long t2;
    long long r2;
    long long q2;
    long long sfinal;
    long long tfinal;
    long long rfinal;
    long long qfinal;

    //Initiallizing variables
    s1=1;
    t1=0;
    r1=PHI;
    q1=0;
    s2=0;
    t2=1;
    r2=e;
    q2=r1/r2;

    while (true)
    {
        sfinal=s1-(s2*q2);
        tfinal=t1-(t2*q2);
        rfinal=r1%r2;
        if (rfinal==0)
        {
            qfinal=0;
            break;
        }
        qfinal=r2/rfinal;

        s1=s2;
        t1=t2;
        r1=r2;
        q1=q2;

        s2=sfinal;
        t2=tfinal;
        r2=rfinal;
        q2=qfinal;
    }
    //From chart, we can pull the correct answer.
    long long d=t2;

    //Negative values are irrelevant and thus turned to positive
    while (d<0){
        d+=abs(tfinal);
    }
    return d;
}