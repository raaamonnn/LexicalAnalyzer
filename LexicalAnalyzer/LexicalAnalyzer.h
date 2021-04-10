#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "FSM.h"
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
   
using namespace std;

typedef string Token;
typedef string Lexeme;

/*
* keep a map of all keywords for fast searches.
* 
*  -Token is our key, -string
*  -Lexeme is the type of Token, -string
*/
const unordered_map<Token, Lexeme> language = {
	{"while" , "Keyword"},
	{"int" , "Keyword"},
	{"whileend" , "Keyword"},
	{"if", "Keyword"},
	{"else", "Keyword"}
	//...
	//{"(" , "Seperator"}, -> too annoying to iterate to find if the character is a seperator
	//{")" , "Seperator"},
	//...
};


/*
	Class - LexicalAnalyzer 
	Function: This class will read through a file and will parse any tokens it comes accross.
	Tokens found will be correctly identified as either keyword, operator, separator, or identifier
	The tokens will be outputted into a file with two columns, one which identifies the token type
	and another that contains the lexeme. The tokens will be printed in the same order that they 
	are read in.
	
*/
class LexicalAnalyzer : public FSM
{
private:
	//holds the file name that will be analyzed 
	string fileName;
	string currentWord;
	int i;

	vector<pair<Token, Lexeme>> subStrings;
	//keep an unordered map of our result 
	vector<pair<Token, Lexeme>> fileLanguage;

	//separate operands and separators from strings
	vector<pair<Token, Lexeme>> Lexer();
	//Parse sub words and match the with the correct lexeme type. 
	void ParseSub(string word, vector<pair<Token, Lexeme>>& subStrings);

	bool TriggerEvent();

	bool GetSeparator();
	bool GetOperator();
	void GetKeyword(string word, std::list<pair<const Token, Lexeme>,
		std::allocator<pair<const Token, Lexeme>>>::const_iterator itr, int state = 3);
	void GetIdentifies(string word, vector<pair<Token, Lexeme>>& subStrings, int state = 4);


	void ParseSyntax();

public:
	//sets final name and constructs the class
	LexicalAnalyzer(string inputFile);

	void PrintLanguage();
	//Main function to start analyzing the file
	//	returns true if file successfully analyzed
	// returns false if file name is not set
	bool Analyze();
};

