#include <iostream>
#include "LexicalAnalyzer.h"

using namespace std;

bool file_exists(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}
/*
	Main Function:
		Construct analyzer class 
			analyzer class calls analyze function to 
			analyze text file. 
	@return 
		return 0 if analyzar is complete!
		return -1 if analyzer fails!
*/
int main() {
	string name = "Test.txt";
	cout << "Enter file name to be analyzed(Example sample.txt): ";
	//getline(std::cin, name);

	if (!file_exists(name)) {
		cout << "File doesn't exist try again :( \n";
		system("pause");
		return -1;
	}

	LexicalAnalyzer analyzer(name);

	if (!analyzer.Analyze())
	{
		cout << "Unable to analyze file!\n";
		system("pause");
		return -1;
	}

	cout << "Lexical Analyzer complete!\n";

	//analyzer.PrintLanguage();

	system("pause");
	return 0;
}