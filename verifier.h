#include "gmp.h"
#include<gmpxx.h>
#include<vector>
#include<tuple>

class Verifier
{
public:
    Verifier();
    void getData(std::vector<mpz_class> n, std::vector<mpz_class> z1, std::vector<mpz_class> z2);
    std::tuple<mpz_class,mpz_class,mpz_class> giveRandomChallenge(bool straight);
    bool verify(mpz_class p);
private:
    std::vector<mpz_class> n;
    std::vector<mpz_class> z1;
    std::vector<mpz_class> z2;
    mpz_class current_check;
};