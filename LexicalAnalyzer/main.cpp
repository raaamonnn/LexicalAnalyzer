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
		Constuct Syntax analyzer class
			this class constructor analyzes the
			syntax and prints it to a file and CMD
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

	/*Vector<Token, Lexeme> is returned by GetResult:
	*This is the result of the LexicalAnalyzer, which
	*is a vector of Tokens from the given input file
	*/
	auto a = lAnalyzer.GetResult();

	//Constructor of SyntaxAnalyzer: Analyzes the 
	//tokens from the vector of tokens given 
	//by the lexical analzyer
	SyntaxAnalyzer sAnalyzer(a);
	//analyzer.PrintLanguage();

	myfile.close();

	printf("Press Enter to close...\n");
	getchar();
	return 0;
}