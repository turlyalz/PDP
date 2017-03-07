#include "Solver.h"

#include "base.h"

#include <algorithm>
#include <limits>
#include <iostream>
#include <chrono>

using namespace std;

Solver::Solver()
{
    m_solution = new Solution();
}

Solver::~Solver()
{
    delete m_solution;
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
            if (m_problem->graph[row][col] && (binary_search(state.cbegin(), state.cend(), row) != binary_search(state.cbegin(), state.cend(), col)))
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
    auto start = chrono::high_resolution_clock::now();

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

        while (state[--i] == --lastNode);
        ++state[i];

        if (i != 0 && i != prevIter)
        {
            prevIter = i;

            // Calculate predicate price
            vector<uint> predState(state.begin(), state.begin() + i);
            uint price = calculatePrice(predState);

            // If the price is bigger than the min price then ignore branch
            if (price > m_solution->price)
            {
                state[i] = m_problem->n - m_problem->a + i;
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

    auto stop = chrono::high_resolution_clock::now();
    using fpSeconds = chrono::duration<float, chrono::seconds::period>;
    auto elapsedTime = fpSeconds(stop - start).count();
    cout << "Elapsed time: " << elapsedTime << " seconds" << endl;
}
