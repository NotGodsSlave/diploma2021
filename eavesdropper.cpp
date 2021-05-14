#include "eavesdropper.h"

mpz_class Eavesdropper::guess(int t, gmp_randstate_t state)
{
    mpz_class low, high;
    mpz_ui_pow_ui(low.get_mpz_t(),10,t-1);
    mpz_ui_pow_ui(high.get_mpz_t(),10,t);
    mpz_class diff = high-low;

    mpz_class guessed;
    mpz_urandomm(guessed.get_mpz_t(),state,diff.get_mpz_t());
    guessed += low+1;
    return guessed;
}

mpz_class Eavesdropper::beta(mpz_class n, mpz_class z1, mpz_class z2, unsigned int t, gmp_randstate_t state)
{
    return (n * z1 * z2) % guess(t,state);
}