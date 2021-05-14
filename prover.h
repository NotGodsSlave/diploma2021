#include "gmp.h"
#include<gmpxx.h>

class Prover
{
public:
    Prover(int t, gmp_randstate_t state);
    void setNumbers(int t, gmp_randstate_t state);
    mpz_class gets1();
    mpz_class gets2();
    mpz_class beta(mpz_class z1, mpz_class z2, mpz_class n);
private:
    mpz_class s1, s2;
};