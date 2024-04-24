#include "FileManager.h"
#include "TextSplitter.h"
#include "FSM.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
	FileManager fin("fsm", "", "txt");
	//FileManager fin("test_b", "", "txt"), fout("test_b_out", "", "txt");
	//FileManager fin("test_b_1", "", "txt"), fout("test_b_1_out", "", "txt");
	//FileManager fin("test_ukr", "", "txt"), fout("test_ukr_out", "", "txt");
	//FileManager fin("test_pl", "", "txt"), fout("test_pl_out", "", "txt");
	//FileManager fin("test_kr", "", "txt"), fout("test_kr_out", "", "txt");
	/*std::vector<std::string> lines = fin.readFile();
	std::map<std::string, int> words;
	std::vector<std::vector<std::string>> splitedLines;
	for (const auto& l : lines) {
		splitedLines.push_back(TextSplitter(l, " ,-\t\n\\\"()'`{}[].:;!@#$%&_?|/~1234567890<>=+*").split(true));
	}
	for (const auto& spl : splitedLines) {
		for (const auto& word : spl) {
			words[word] += 1;
		}
	}
	fout.writeFile(words);*/
	FSM fsm = getFSM(fin);
	std::cout << fsm << std::endl;
	//std::string word = "aaaabba";
	std::string word;
	std::cout << "Enter a word: ";
	std::getline(std::cin, word);
	if (fsm.modelFSM(word)) {
		std::cout << "Word \"" << word << "\" is allowed by this FSM." << std::endl;
	}
	else {
		std::cout << "Word \"" << word << "\" is not allowed by this FSM." << std::endl;
	}
	system("pause");
}