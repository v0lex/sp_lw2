#include"TransitionFunction.h"

TransitionFunction::TransitionFunction(std::vector<std::string> tf) {
	this->start = *tf.begin();
	this->end = *(tf.end() - 1);
	if (tf.size() != 2) {
		for (auto pos = tf.begin() + 1; pos < tf.end() - 1; ++pos) {
			this->triggers.push_back(*pos);
		}
	}
	else {
		this->triggers = { "" };
	}
}

TransitionFunction::TransitionFunction(std::string s, std::string e, std::vector<std::string> tr) {
	this->start = s;
	this->end = e;
	this->triggers = tr;
}

std::string TransitionFunction::getStart() {
	return this->start;
}

std::string TransitionFunction::getEnd() {
	return this->end;
}

std::vector<std::string> TransitionFunction::getTriggers() {
	return this->triggers;
}

std::ostream& operator<<(std::ostream& os, const TransitionFunction& tf) {
	os << "Start: " << tf.start;
	os << "\nEnd: " << tf.end;
	os << "\nTriggers: ";
	for (const auto& f : tf.triggers) {
		os << f << " ";
	}
	os << "\n-------------------\n";
	return os;
}