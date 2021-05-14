#include<iostream>
#include<time.h>
#include "gmp.h"
#include<gmpxx.h>
#include "prover.h"
#include "verifier.h"
#include "provider.h"
#include "eavesdropper.h"
#include<vector>
#include<tuple>
#include<chrono>

using namespace std;

static void helpText()
{
    cout << "Possible parametrs: [-h] [-p] [-P] [-v] [-V] [-e] [-E] [-t T] [-m M]\n";
    cout << "[-h] \t\t Prints this\n";
    cout << "[-p] [-P] \t View as prover\n";
    cout << "[-v] [-V] \t View as verifier\n";
    cout << "[-e] [-E] \t View as eavesdropper\n";
    cout << "[-t T] \t\t Security settings, T is unsigned integer\n";
    cout << "[-m M] \t\t How many numbers n are generated, M is unsigned integer\n";
}

void processArguments(int argc, char *argv[], unsigned int& t, int& m, char& c)
{
    for (int i = 0; i < argc; ++i)
    {
        if (!strcmp(argv[i],"-p") || !strcmp(argv[i],"-P"))
        {
            c = 'P';
            continue;
        }
        if (!strcmp(argv[i],"-v") || !strcmp(argv[i],"-V"))
        {
            c = 'V';
            continue;
        }
        if (!strcmp(argv[i],"-e") || !strcmp(argv[i],"-E"))
        {
            c = 'E';
            continue;
        }
        if (!strcmp(argv[i],"-t"))
        {
            if (i < argc-1)
            {
                i++;
                try {
                    t = strtoul(argv[i], NULL, 10);
                }
                catch (exception e){
                    cout << "incorrect input for -t flag\n";
                    exit(1);
                }
            }
            continue;
        }
        if (!strcmp(argv[i],"-m"))
        {
            if (i < argc-1)
            {
                i++;
                try {
                    m = strtoul(argv[i], NULL, 10);
                }
                catch (exception e){
                    cout << "incorrect input for -m flag\n";
                    exit(1);
                }
            }
            continue;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        helpText();
        exit(1);
    }
    //initialization
    unsigned int t = 6;
    int m = 10;
    char c = 'A';

    processArguments(argc, argv, t, m, c);

    gmp_randstate_t state;
    gmp_randinit_default (state);
    unsigned long int tm = static_cast<unsigned long int> (time(NULL));
    gmp_randseed_ui(state,tm);

    //creating entities
    Prover A(t, state);
    Verifier B;
    Provider T;
    Eavesdropper E;

    //setup
    vector<mpz_class> n, z1, z2;
    T.setup(n,z1,z2,m,A.gets1(),A.gets2(),t,state);
    B.getData(n,z1,z2);

    if (c == 'P') cout << "Secret:\n" << A.gets1() << ", " << A.gets2() << '\n';

    cout << "Generated public key:\n";
    for (int i = 0; i < min(m,5); ++i)
    {
        cout << n[i] << " ";
    }
    cout << '\n';

    if (c == 'B')
    {
        cout << "Values of z pairs:\n";
        for (int i = 0; i < min(m,5); ++i)
        {
            cout << z1[i] << ", " << z2[i] << "\n";
        }
    }
    cout << '\n';

    tuple<mpz_class,mpz_class,mpz_class> mes = B.giveRandomChallenge(true);
    if (c != 'E'){
        B.verify(A.beta(get<0>(mes),get<1>(mes),get<2>(mes)));
    }
    else {
        B.verify(E.beta(get<0>(mes),get<1>(mes),get<2>(mes),t,state));
    }
}