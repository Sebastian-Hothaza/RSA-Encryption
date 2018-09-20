#ifndef ENCRYPT_H
#define ENCRYPT_H

long long Encrypt(long long b, long long e, long long m);
long long GetP();
long long GetQ();
long long GetN(long long p, long long q);
long long GetPHI(long long p, long long q);
long long GetE(long long PHI);
long long GetD(long long PHI, long long e);
bool isPrime(long long number);

#endif