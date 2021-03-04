#include <iostream>
#include "LexicalAnalyzer.h"
using namespace std;


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
	string name;
	cout << "Enter file name to be analyzed(Example sample.txt): ";
	getline(std::cin, name);

	LexicalAnalyzer analyzer(name);

	if (!analyzer.Analyze())
	{
		cout << "Unable to analyze file!\n";
		return -1;
	}

	cout << "Lexical Analyzer complete!\n";
	return 0;
}