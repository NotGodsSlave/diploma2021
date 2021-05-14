all: main

clean:
	rm -f main

main: main.cpp prover.cpp verifier.cpp provider.cpp eavesdropper.cpp
	g++ prover.cpp verifier.cpp provider.cpp eavesdropper.cpp main.cpp -o main -lgmp -lgmpxx