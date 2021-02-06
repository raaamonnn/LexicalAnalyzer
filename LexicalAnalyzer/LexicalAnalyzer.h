#pragma once
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Language {
	string token;
	string lexeme[];
};



//TOKENS			Example Lexemes
//
//KEYWORDS = int, float, bool, True, False, if, else, then, endif, endelse, while, whileend, do, enddo, for, endfor, STDinput, STDoutput, and, or , not
//IDENTIFIERS = legal identifiers must start with alphabetic character follow by digits, letters, underscore or $
//SEPARATORS = (){}[], .:;
//OPERATORS = *+-= / > < %
//
//
//	Additional examples and symbols:
//Valid IDENTIFIERS : num, num1, large$, num$1, num2, num2$, a9, ab, ab2, my_num, Max_Num, etc...
//Valid Numbers : integers whole numbers(0, 1, 2, 3, ...9) and reals or floats(5.0, 0.9, 1.75, ...)
//Valid Block Comments : !this is a block comment to be ignored by the Lexical Analyzer !
//Special Characters : the !(exclamation mark), the _(underscore) and the sp(space character)


//finish this
const vector<Language> language = {
	{"keyword"},  {{"while", "whileend"}},
	{"seperator"},  {{"(", ")"} }
};

class LexicalAnalyzer
{
private:
	//we could have a a language vector here holding all the data from the textfile but if we just print it in the init we wont need it for now
public:
	LexicalAnalyzer(string inputFile);
};

