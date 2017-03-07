#include "InputManager.h"
#include "Problem.h"

#include "base.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <cstring>

using namespace std;

InputManager::~InputManager()
{
	if (m_problem)
	{
		delete m_problem;
	}
}

void InputManager::printHelp() const
{
    cout << "Run program: ./bw.out -f FILE_NAME -a NATURAL_NUMBER" << endl;
}

bool InputManager::parse(int argc, char* argv[])
{
	if (argc == 5)
	{
		m_problem = new Problem();

        string fileName;
		if (strcmp("-f", argv[1]) == 0)
		{
			fileName = argv[2];
		}
		else
		{
            cerr << "Argument " << argv[1] << " unknown" << endl;
            printHelp();
			return false;
		}

		if (strcmp("-a", argv[3]) == 0)
		{
            m_problem->a = stoi(argv[4]);
		}
		else
		{
            cerr << "Argument " << argv[3] << " unknown" << endl;
            printHelp();
			return false;
		}

        ifstream in(fileName);
		if (in.is_open())
		{
            string data;
            getline(in, data);

            istringstream iss(data);
			iss >> m_problem->n;

			if (m_problem->a < 5 || m_problem->a >(m_problem->n / 2))
			{
                cerr << "a must be in range [5, n/2]" << endl;
				return false;
			}
			
            while (getline(in, data))
			{
                vector<bool> row;
				if (data.size() != m_problem->n)
				{
                    cerr << "Incorrect file: " << fileName << endl;
					return false;
				}

				for (unsigned int i = 0; i < m_problem->n; ++i)
				{
					row.push_back(data[i] != '0');
				}
				m_problem->graph.push_back(row);
			}

            cout << m_problem->graph;
			in.close();
			return true;
		}
		else
		{
            cerr << "Unable to open file: " + fileName << endl;
		}
	}
	else
	{
        cerr << "Number of arguments must be 4" << endl;
        printHelp();
	}
	return false;
}
