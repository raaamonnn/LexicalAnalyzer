#pragma once
#include <vector>
#include <string>
#include "common.h"
using namespace std;

class SyntaxAnalyzer {
private:
	vector<pair<Token, Lexeme>> synInput;
	pair<Token, Lexeme> pairInput;


	Token GetToken() {
		return pairInput.first;
	}

	Lexeme GetLexeme() {
		return pairInput.second;
	}

	void NextInput() {
		pairInput = synInput.begin();
	}

	string nextLexeme; //***temp!!!***
	string nextToken; //***temp!!!***

	bool Expression() {
		printf("<Expression> -> <Term> <Expression Prime>");
		if (Term()) {
			if (ExpressionPrime()) {
				return true;
			}
			else {
				printf("ERROR Expected -> EXPRESSION PRIME");
			}
		}
		else {
			printf("ERROR Expected -> TERM");
		}
		return false;
	}

	//TODO
	bool Term() {
		printf("<Term> -> <Factor> <Term Prime>");
		if (Factor()) {
			if (TermPrime()) {
				return true;
			}
			else {
				printf("ERROR Expected -> TERM PRIME");
			}
		}
		else {
			printf("ERROR Expected -> FACTOR");
		}
		return false;
	}

	//TODO
	bool ExpressionPrime() {
		//Lexeme newLexeme = synInput.nextLexeme();
		if (nextLexeme == "+") {
			printf("-> INSERT LEXER RESULTS <- *TOKEN AND LEXEME*");
			printf("<Expression Prime> + <Term> <Expression Prime>");
			if (Term()) {
				if (ExpressionPrime()) {
					return true;
				}
				else {
					printf("ERROR Expected -> EXPRESSION PRIME");
				}
			}
			else {
				printf("ERROR Expected -> TERM");
			}
		}

		if (nextLexeme == "-") {
			printf("-> INSERT LEXER RESULTS <- *TOKEN AND LEXEME*");
			printf("<Expression Prime> - <Term> <Expression Prime>");
			if (Term()) {
				if (ExpressionPrime()) {
					return true;
				}
				else {
					printf("ERROR Expected -> EXPRESSION PRIME");
				}
			}
			else {
				printf("ERROR Expected -> TERM");
			}
		}
		return false;
	}

	bool Factor() {

		if (nextLexeme == "-") //For negative  factors
		{
			printf("<Factor> -> - <Primary>");
			if (Primary()) {
				return true;
			}
		}
		else if (Primary()) {
			printf("<Factor> ->  <Primary>");
			return true;
		}
		else {
			printf("ERROR Expected -> FACTOR");
		}
		return true;
	}

	bool TermPrime() {
		if (nextLexeme == "*") {
			printf("-> INSERT LEXER RESULTS <- *TOKEN AND LEXEME*");
			printf("<Term Prime -> * <Term> <Term Prime>");

			if (Term()) {
				if (TermPrime()) {
					return true;
				}
				else {
					printf("ERROR Expected -> Term Prime");
				}
			}
			else {
				printf("ERROR Expected -> Term");
			}
		}

		if (nextLexeme == "/") {
			printf("-> INSERT LEXER RESULTS <- *TOKEN AND LEXEME*");
			printf("<Term Prime -> / <Term> <Term Prime>");

			if (Term()) {
				if (TermPrime()) {
					return true;
				}
				else {
					printf("ERROR Expected -> Term Prime");
				}
			}
			else {
				printf("ERROR Expected -> Term");
			}
		}

		return false;
	}

	bool Ids() {
		printf("<IDs> -> <Identifier> | <Identifier>, <IDs>");
		if (nextToken == "Identifier") {
			printf("-> INSERT LEXER RESULTS <- *TOKEN AND LEXEME*");
			if (nextLexeme == ",") {
				printf("-> INSERT LEXER RESULTS <- *TOKEN AND LEXEME*");
				return Ids();
			}
			return true;
		}
		else {
			printf("ERROR Expected -> IDENTIFIER");
		}
		return false;
	}
	bool Primary() {
		return true;
	}


public:
	SyntaxAnalyzer(vector<pair<Token, Lexeme>> &lexResult) {
		synInput = lexResult;
	}
};