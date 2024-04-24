#pragma once
#include<vector>
#include<string>
#include<iostream>
class TransitionFunction {
public:
	TransitionFunction(std::vector<std::string>);
	TransitionFunction(std::string, std::string, std::vector<std::string>);
	std::string getStart();
	std::string getEnd();
	std::vector<std::string> getTriggers();
	friend std::ostream& operator<<(std::ostream&, const TransitionFunction&);
private:
	std::string start;
	std::string end;
	std::vector<std::string> triggers;
};