#include "Solver.h"

#include <algorithm>
#include <limits>
#include <iostream>

using namespace std;

Solver::Solver()
{
    m_solution = new Solution();
}

Solver::~Solver()
{
    delete m_solution;
}

ostream& operator<<(ostream& os, const vector<uint>& nodes)
{
    for (uint i = 0; i < nodes.size(); ++i)
    {
        os << nodes[i];
        if (i != nodes.size() - 1)
        {
            os << " ";
        }
    }
    return os;
}

ostream& operator<<(ostream& os, const Solution& solution)
{
    os << "------ Solution ------" << endl;
    os << "Price: " << solution.price << endl;
    os << "Nodes: " << '[' << solution.nodes << ']' << endl;
    os << "----------------------" << endl;
    return os;
}

uint Solver::combinations(uint n, uint k) const
{
    vector<bool> bitmask(k, true);
    bitmask.resize(n, false);

    int counter = 0;
    do {
        ++counter;
    } while (prev_permutation(bitmask.begin(), bitmask.end()));

    return counter;
}

uint Solver::calculatePrice(const vector<uint>& state)
{
    uint price = 0;

    for (uint row = 0; row < m_problem->graph.size(); ++row)
    {
        for (uint col = row + 1; col < m_problem->graph[row].size(); ++col)
        {
            if (m_problem->graph[row][col] && (binary_search(state.begin(), state.end(), row) != binary_search(state.begin(), state.end(), col)))
            {
                price++;
            }
        }
    }
    return price;
}

void Solver::run(const Problem* problem)
{
    m_problem = problem;
    if (!m_problem)
    {
        return;
    }

    vector<uint> state(m_problem->a);

    // Start state: (0, 1, ..., a - 1)
    for (uint i = 0; i < m_problem->a; ++i)
    {
        state[i] = i;
    }

    m_solution->price = calculatePrice(state);
    uint comb = combinations(m_problem->n, m_problem->a);

    cout << "Start price: " << m_solution->price << endl;
    cout << "Number of combinations: " << comb << endl;

    uint prevIter = 0;
    for (uint c = 1; c < comb; ++c)
    {
        uint i = m_problem->a;
        uint lastNode = m_problem->n;

        while (state[--i] == --lastNode) {}
        ++state[i];

        if (i != 0 && i != prevIter)
        {
            prevIter = i;
            uint price = calculatePrice(state);
            if (price >= m_solution->price)
            {
                state[i] = m_problem->n - m_problem->a - i;
                continue;
            }
        }

        for (uint j = i + 1; j < m_problem->a; ++j)
        {
            state[j] = state[j - 1] + 1;
        }

        uint price = calculatePrice(state);
        if (price < m_solution->price)
        {
            m_solution->price = price;
            m_solution->nodes = state;
        }

        if (state[0] >= m_problem->n - m_problem->a)
        {
            break;
        }
    }

    cout << *m_solution;
}
