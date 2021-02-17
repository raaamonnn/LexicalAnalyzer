#pragma once
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

typedef string Token;
typedef string Lexeme;


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


//there are more things like real and identifier which are numbers / variables

//finish this
//const vector<Language> language = {
//	{"keyword"},  {{"while", "whileend"}},
//	{"seperator"},  {{"(", ")"} }
//};
   
const map<Token, Lexeme> language = {
	{"while" , "Keyword"},
	{"int" , "Keyword"},
	{"whileend" , "Keyword"}
	//...
	//{"(" , "Seperator"}, -> too annoying to iterate to find if the character is a seperator
	//{")" , "Seperator"},
	//...
};


class LexicalAnalyzer
{
private:
	map<Token, Lexeme> fileLanguage;

	vector<pair<Token, Lexeme>> GiveSub(string word);
	void ParseSub(string word, vector<pair<Token, Lexeme>> subStrings);
public:
	LexicalAnalyzer(string inputFile);
};

