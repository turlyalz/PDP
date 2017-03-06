#include "InputManager.h"
#include "Solver.h"

#include <iostream>

int main(int argc, char* argv[])
{
	InputManager input;

    std::cout << "---------------- Bisection width of graph ----------------" << std::endl;
    if (input.parse(argc, argv))
    {
        Solver().run(input.getProblem());
    }
    std::cout << "----------------------------------------------------------" << std::endl;

	return 0;
}
