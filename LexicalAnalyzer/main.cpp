#include <iostream>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
using namespace std;

ofstream myfile;

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
	string outName;
	string name;
	printf("Enter file name to be analyzed(Example sample.txt): ");
	getline(std::cin, name);

	if (!file_exists(name)) {
		printf("File doesn't exist try again :( \n");
		printf("Press Enter to close...\n");
		getchar();
		return 0;
	}

	printf("Enter file output file name: ");
	getline(std::cin, outName);

	if (outName.empty() || outName == "" || outName == "\n") {
		printf("output file name missing! :( \n");
		printf("Press Enter to close...\n");
		getchar();
		return 0;
	}
	myfile.open(outName);

	LexicalAnalyzer lAnalyzer(name);

	if (!lAnalyzer.Analyze())
	{
		printf("Unable to analyze file!\n");
		printf("Press Enter to close...\n");
		myfile.close();
		getchar();
		return 0;
	}

	lAnalyzer.PrintLanguage();
	Log("Lexical Analyzer result passed to Syntanx...\n");

	auto a = lAnalyzer.GetResult();
	SyntaxAnalyzer sAnalyzer(a);
	//analyzer.PrintLanguage();

	myfile.close();

	printf("Press Enter to close...\n");
	getchar();
	return 0;
}