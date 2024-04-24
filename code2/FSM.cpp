#include"FSM.h"
#include"TextSplitter.h"
#include<algorithm>

FSM::FSM(std::vector<std::vector<std::string>> fsm) {
	this->numberOfSymbols = stoi(fsm.at(0).at(0));
	this->numberOfStates = stoi(fsm.at(1).at(0));
	this->startState = fsm.at(2).at(0);
	this->numberOfFinalStates = stoi(fsm.at(3).at(0));
	std::vector<std::string> fs;
	for (auto pos = fsm.at(3).begin() + 1; pos < fsm.at(3).end(); ++pos) {
		fs.push_back(*pos);
	}
	this->finalStates = fs;
	std::vector<TransitionFunction> tr;
	for (auto pos = fsm.begin() + 4; pos < fsm.end(); ++pos) {
		tr.push_back(TransitionFunction(*pos));
	}
	this->trFunctions = tr;
	this->currentStates.push_back(this->startState);
}

FSM::FSM(int nos, int nost, std::string s, int nofs, std::vector<std::string> fs, std::vector<TransitionFunction> tr) {
	this->numberOfSymbols = nos;
	this->numberOfStates = nost;
	this->startState = s;
	this->numberOfFinalStates = nofs;
	this->finalStates = fs;
	this->trFunctions = tr;
	this->currentStates.push_back(this->startState);
}

std::vector<std::string> FSM::getTriggersFromCurrentState() {
	std::vector<std::string> triggers;
	for (const auto& state : currentStates) {
		for (auto& tf : trFunctions) {
			if (state._Equal(tf.getStart())) {
				for (auto tr : tf.getTriggers()) {
					triggers.push_back(tr);
				}
			}
		}
	}
	return triggers;
}

std::vector<std::string> FSM::getPossibleEndsByCurrentStateAndTrigger(std::string tr) {
	std::vector<std::string> possEnds;
	for (const auto& state : currentStates) {
		for (auto& tf : trFunctions) {
			if (state._Equal(tf.getStart())) {
				for (auto trf : tf.getTriggers()) {
					if (trf._Equal(tr)) {
						possEnds.push_back(tf.getEnd());
					}
				}
			}
		}
	}
	return possEnds;
}

void FSM::setCurrentStates(std::vector<std::string> states) {
	this->currentStates = states;
}

bool FSM::modelFSM(std::string word) {
	std::string buffer = "";
	int  i = 0;
	while (i < word.length()) {
		std::vector<std::string> triggers = this->getTriggersFromCurrentState();
		int maxLengthOfTrigger = maxLengthOfWord(triggers);
		buffer += word.at(i);
		std::cout << "Current states: ";
		for (const auto& state : currentStates) {
			std::cout << state << " ";
		}
		std::cout << std::endl;
		std::cout << "Buffer: " << buffer << std::endl;
		if (buffer.length() > maxLengthOfTrigger) {
			if (std::count(triggers.begin(), triggers.end(), "")) {
				std::cout << "There is an empty trigger" << std::endl;
				this->currentStates = getPossibleEndsByCurrentStateAndTrigger("");
				std::cout << "Trigger: " << "" << std::endl;
				buffer = "";
				i -= maxLengthOfTrigger;
				std::cout << "New states: ";
				for (const auto& state : currentStates) {
					std::cout << state << " ";
				}
				std::cout << "\n____________________________" << std::endl;
				continue;
			}
			else {
				return false;
			}
		}
		if (std::count(triggers.begin(), triggers.end(), buffer)) {
			this->currentStates = getPossibleEndsByCurrentStateAndTrigger(buffer);
			std::cout << "Trigger: " << buffer << std::endl;
			buffer = "";
		}
		std::cout << "New states: ";
		for (const auto& state : currentStates) {
			std::cout << state << " ";
		}
		std::cout <<"\n____________________________"<< std::endl;
		i++;
	}
	if (buffer.length()) return false;
	for (const auto& state : currentStates) {
		if (std::count(finalStates.begin(), finalStates.end(), state)) {
			std::cout << "State " << state << " is final." << std::endl;
			return true;
		}
	}
	return false;
}

FSM getFSM(FileManager f) {
	std::vector<std::string> lines = f.readFile();
	std::vector<std::vector<std::string>> textFSM;
	for (const auto& l : lines) {
		textFSM.push_back(TextSplitter(l, " ").split(true));
	}
	return FSM(textFSM);
}

std::ostream& operator<<(std::ostream& os, const FSM& fsm) {
	os << "Number of symbols: " << fsm.numberOfSymbols;
	os << "\nNumber of states: " << fsm.numberOfStates;
	os << "\nStart state: " << fsm.startState;
	os << "\nNumber of final states: " << fsm.numberOfFinalStates;
	os << "\nFinal states: ";
	for (const auto& fs : fsm.finalStates) {
		os << fs << " ";
	}
	os << "\nTransition functions:\n";
	for (const auto& tf : fsm.trFunctions) {
		os << tf;
	}
	return os;
}

int maxLengthOfWord(std::vector<std::string> words) {
	int maxLength = words.at(0).length();
	for (auto pos = words.begin() + 1; pos < words.end(); pos++) {
		if ((*pos).length() > maxLength) {
			maxLength = (*pos).length();
		}
	}
	return maxLength;
}