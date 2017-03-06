#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

struct Problem;

class InputManager
{
public:
	InputManager() : m_problem(nullptr) {}
	~InputManager();

	bool parse(int argc, char* argv[]);
	inline Problem* getProblem() { return m_problem; }

private:
	Problem* m_problem;

    void printHelp() const;
};

#endif // INPUT_MANAGER_H
