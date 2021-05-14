#include "gmp.h"
#include<gmpxx.h>
#include<tuple>
#include<vector>

class Provider
{
public:
    Provider(){};
    mpz_class generatePrimeBetween(gmp_randstate_t state, mpz_class low, mpz_class high);
    std::tuple<mpz_class,mpz_class,mpz_class> alpha(mpz_class s1, mpz_class s2, unsigned int t, gmp_randstate_t state);
    void setup(std::vector<mpz_class> &n, std::vector<mpz_class> &z1, std::vector<mpz_class> &z2, 
                int m, mpz_class s1, mpz_class s2, unsigned int t, gmp_randstate_t state);
};