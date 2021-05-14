#include "provider.h"

using namespace std;

mpz_class Provider::generatePrimeBetween(gmp_randstate_t state, mpz_class low, mpz_class high)
{
    mpz_class diff = high - low;
    mpz_class res;
    mpz_urandomm(res.get_mpz_t(),state,diff.get_mpz_t());
    res += low+1;

    while (!mpz_probab_prime_p(res.get_mpz_t(),20))
    {
        mpz_urandomm(res.get_mpz_t(),state,diff.get_mpz_t());
        res+=low+1;
    }
    return res;
}

tuple<mpz_class,mpz_class,mpz_class> Provider::alpha(mpz_class s1, mpz_class s2, unsigned int t, gmp_randstate_t state)
{
    mpz_class low; 
    mpz_ui_pow_ui(low.get_mpz_t(),2,t);
    mpz_class q, p, r, k1, k2;

    //generating all the primes we need for this operation
    q = generatePrimeBetween(state,low,s1);
    p = generatePrimeBetween(state,low,s1);
    r = generatePrimeBetween(state,low,s1);
    k1 = generatePrimeBetween(state,low,s1);
    k2 = generatePrimeBetween(state,low,s1);
    //n = p*q
    mpz_class n = p*q;

    //inverting values we need inverted
    mpz_class r_invert, q_invert, s2_invert;
    mpz_invert(r_invert.get_mpz_t(),r.get_mpz_t(),s1.get_mpz_t());
    mpz_invert(q_invert.get_mpz_t(),q.get_mpz_t(),s1.get_mpz_t()); 
    mpz_invert(s2_invert.get_mpz_t(),s2.get_mpz_t(),s1.get_mpz_t());

    //calculating z1
    mpz_class z1 = (r_invert * q_invert * s2_invert) % s1 + k1 * s1;

    //calculating z2
    mpz_class z2 = (r * s2) % s1 + k2 * s1;
    tuple<mpz_class,mpz_class,mpz_class> res (n,z1,z2);
    return res;
}

void Provider::setup(vector<mpz_class> &n, vector<mpz_class> &z1, vector<mpz_class> &z2, int m, mpz_class s1, mpz_class s2, unsigned int t, gmp_randstate_t state)
{
    tuple<mpz_class,mpz_class,mpz_class> temp;
    for (int i = 0; i < m; ++i) {
        temp = alpha(s1,s2,t,state);
        n.push_back(get<0>(temp));
        z1.push_back(get<1>(temp));
        z2.push_back(get<2>(temp));
    }
}