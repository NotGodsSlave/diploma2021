#include "verifier.h"
#include<iostream>
#include<random>
#include<time.h>

Verifier::Verifier()
{
    n = std::vector<mpz_class>();
    z1 = std::vector<mpz_class>();
    z2 = std::vector<mpz_class>();
}

std::tuple<mpz_class,mpz_class,mpz_class> Verifier::giveRandomChallenge(bool straight)
{
    srand(time(NULL));
    int i = rand()%n.size();
    std::tuple<mpz_class,mpz_class,mpz_class> res (n[i],z1[i],z2[i]);
    current_check = n[i];
    if (straight)
    {
        n.erase(n.begin()+i);
        z1.erase(z1.begin()+i);
        z2.erase(z2.begin()+i);
    }
    return res;
}

void Verifier::getData(std::vector<mpz_class> nt, std::vector<mpz_class> z1t, std::vector<mpz_class> z2t)
{
    n = nt;
    z1 = z1t;
    z2 = z2t;
}

bool Verifier::verify(mpz_class p)
{
    std::cout << "Verifier got number " << p << " as a factor of " << current_check << " from prover\n";
    mpz_class check = current_check % p;
    if (!check.get_ui())
        std::cout << "Authentication succesful!\n";
    else
        std::cout << "Authentication failed!\n";
    return !check.get_ui();
}