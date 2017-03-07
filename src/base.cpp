#include "base.h"
#include "Solution.h"

using namespace std;

ostream& operator<<(ostream& os, const vector<vector<bool>>& graph)
{
    os << "----------------- Graph -----------------" << endl;
    for (uint i = 0; i < graph.size(); ++i)
    {
        os << graph[i] << endl;
    }
    os << "-----------------------------------------" << endl;
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
    for (uint i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
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
    os << "Nodes: " << '{' << solution.nodes << '}' << endl;
    os << "----------------------" << endl;
    return os;
}
