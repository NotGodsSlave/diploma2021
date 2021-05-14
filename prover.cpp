#include "prover.h"
#include<iostream>
#include "gmp.h"
#include<gmpxx.h>

Prover::Prover(int t, gmp_randstate_t state)
{
    setNumbers(t, state);
}

void Prover::setNumbers(int t, gmp_randstate_t state)
{
    mpz_class low, high;
    mpz_ui_pow_ui(low.get_mpz_t(),10,t-1);
    mpz_ui_pow_ui(high.get_mpz_t(),10,t);
    mpz_class diff = high-low;

    mpz_urandomm(s1.get_mpz_t(),state,diff.get_mpz_t());
    s1 += low+1;

    mpz_urandomm(s2.get_mpz_t(),state,diff.get_mpz_t());
    s2 += low+1;
    mpz_class gc = gcd(s1,s2);
    while (gc != 1)
    {
        mpz_urandomm(s2.get_mpz_t(),state,diff.get_mpz_t());
        s2 += low+1;
        gc = gcd(s1,s2);
    }

    //std::cout << "Secret numbers for A are: " << s1 << ' ' << s2 << '\n';
}

mpz_class Prover::gets1()
{
    return s1;
}

mpz_class Prover::gets2()
{
    return s2;
}

mpz_class Prover::beta(mpz_class n, mpz_class z1, mpz_class z2)
{
    std::cout << "Prover got numbers " << z1 << " and " << z2 << " from verifier\n";
    return (n * z1 * z2) % s1;
}