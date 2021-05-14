#include "gmp.h"
#include<gmpxx.h>

class Eavesdropper
{
public:
    mpz_class guess(int t, gmp_randstate_t state);
    mpz_class beta(mpz_class n, mpz_class z1, mpz_class z2, unsigned int t, gmp_randstate_t state);
};