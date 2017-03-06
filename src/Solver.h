#ifndef SOLVER_H
#define SOLVER_H

#include "Problem.h"

struct Problem;

struct Solution
{
    uint price;
    std::vector<uint> nodes;
};

class Solver
{
public:
    Solver();
    ~Solver();

    void run(const Problem* problem);

private:
    uint combinations(uint n, uint k) const;
    uint calculatePrice(const std::vector<uint>& state);

    const Problem* m_problem;
    Solution* m_solution;
};

#endif // SOLVER_H
