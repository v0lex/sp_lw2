#pragma once
#include "TransitionFunction.h"
#include "FileManager.h"
#include<vector>
#include<string>
#include<iostream>

class FSM {
public:
	FSM(std::vector<std::vector<std::string>>);
	FSM(int, int, std::string, int, std::vector<std::string>, std::vector<TransitionFunction>);
	std::vector<std::string> getTriggersFromCurrentState();
	std::vector<std::string> getPossibleEndsByCurrentStateAndTrigger(std::string);
	void setCurrentStates(std::vector<std::string>);
	bool modelFSM(std::string);
	friend std::ostream& operator<<(std::ostream&, const FSM&);
private:
	int numberOfSymbols;
	int numberOfStates;
	std::string startState;
	int numberOfFinalStates;
	std::vector<std::string> finalStates;
	std::vector<TransitionFunction> trFunctions;
	std::vector<std::string> currentStates;
};

FSM getFSM(FileManager);
int maxLengthOfWord(std::vector<std::string>);