#include "InputManager.h"
#include "Problem.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <cstring>

InputManager::~InputManager()
{
	if (m_problem)
	{
		delete m_problem;
	}
}

void InputManager::printHelp() const
{
    std::cout << "Run program: ./gbw.out -f FILE_NAME -a NATURAL_NUMBER" << std::endl;
}

bool InputManager::parse(int argc, char* argv[])
{
	if (argc == 5)
	{
		m_problem = new Problem();

		std::string fileName;
		if (strcmp("-f", argv[1]) == 0)
		{
			fileName = argv[2];
		}
		else
		{
			std::cerr << "Argument " << argv[1] << " unknown" << std::endl;
            printHelp();
			return false;
		}

		if (strcmp("-a", argv[3]) == 0)
		{
			m_problem->a = std::stoi(argv[4]);
		}
		else
		{
			std::cerr << "Argument " << argv[3] << " unknown" << std::endl;
            printHelp();
			return false;
		}

		std::ifstream in(fileName);
		if (in.is_open())
		{
			std::string data;
			std::getline(in, data);

			std::istringstream iss(data);
			iss >> m_problem->n;

			if (m_problem->a < 5 || m_problem->a >(m_problem->n / 2))
			{
				std::cerr << "a must be in range [5, n/2]" << std::endl;
				return false;
			}
			
			while (std::getline(in, data))
			{
				std::vector<bool> row;
				if (data.size() != m_problem->n)
				{
					std::cerr << "Incorrect file: " << fileName << std::endl;
					return false;
				}

				for (unsigned int i = 0; i < m_problem->n; ++i)
				{
					row.push_back(data[i] != '0');
				}
				m_problem->graph.push_back(row);
			}

			in.close();
			return true;
		}
		else
		{
            std::cerr << "Unable to open file: " + fileName << std::endl;
		}
	}
	else
	{
		std::cerr << "Number of arguments must be 4" << std::endl;
        printHelp();
	}
	return false;
}
