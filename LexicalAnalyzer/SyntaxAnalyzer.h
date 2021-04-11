#pragma once
#include <vector>
#include "common.h"
using namespace std;

class SyntaxAnalyzer {
private:
	typedef string Token;
	typedef string Lexeme;

	vector<pair<Token, Lexeme>> synInput;
	pair<Token, Lexeme> pairInput;


	Token GetToken() {
		return pairInput.first;
	}

	Lexeme GetLexeme() {
		//cout << "\nGETLEXEME -> " << pairInput.second << endl;
		return pairInput.second;
	}

	Lexeme PeekLexeme() {
		return synInput.front().second;
	}

	void NextInput() {
		//cout << "NEXT INPUT CALLED\n PAIR TOKEN ->" << synInput.front().first << endl;
		pairInput = synInput.front();
		synInput.erase(synInput.begin());
	}

	void PrintLexerResult() {
		cout << "\nTOKEN -> " << GetToken() << endl;
		cout << "LEXEME -> " << GetLexeme() << endl;
		cout << "-------------------\n";
	}

	bool Expression() {
		PrintLexerResult();
		printf("<Expression> -> <Term> <Expression Prime>\n");
		if (Term()) {
			if (ExpressionPrime()) {
				return true;
			}
			else {
				printf("ERROR Expected -> EXPRESSION PRIME\n");
			}
		}
		else {
			printf("ERROR Expected -> TERM\n");
		}
		return false;
	}

	bool Term() {
		printf("<Term> -> <Factor> <Term Prime>\n");
		if (Factor()) {
			NextInput();
			if (TermPrime()) {
				return true;
			}
			else {
				printf("ERROR Expected -> TERM PRIME\n");
			}
		}
		else {
			printf("ERROR Expected -> FACTOR\n");
		}
		return false;
	}

	bool ExpressionPrime() {
		if (GetToken() == "+") {
			PrintLexerResult();
			NextInput();
			printf("<Expression Prime> + <Term> <Expression Prime>\n");
			if (Term()) {
				if (ExpressionPrime()) {
					return true;
				}
				else {
					printf("ERROR Expected -> EXPRESSION PRIME\n");
					return false;
				}
			}
			else {
				printf("ERROR Expected -> TERM\n");
				return false;
			}
		}

		if (GetToken() == "-") {
			PrintLexerResult();
			NextInput();
			printf("<Expression Prime> - <Term> <Expression Prime>\n");
			if (Term()) {
				if (ExpressionPrime()) {
					return true;
				}
				else {
					printf("ERROR Expected -> EXPRESSION PRIME\n");
				}
			}
			else {
				printf("ERROR Expected -> TERM\n");
			}
		}
		return false;
	}

	bool Factor() {

		if (GetLexeme() == "-") //For negative  factors
		{
			PrintLexerResult();
			printf("<Factor> -> - <Primary>\n");
			if (Primary()) {
				return true;
			}
		}
		else if (Primary()) {
			printf("<Factor> ->  <Primary>\n");
			return true;
		}
		else {
			printf("ERROR Expected -> FACTOR\n");
		}
		return true;
	}

	bool TermPrime() {
		if (GetToken() == "*") {
			PrintLexerResult();
			NextInput();
			printf("<Term Prime -> * <Term> <Term Prime>\n");

			if (Term()) {
				if (TermPrime()) {
					return true;
				}
				else {
					printf("ERROR Expected -> Term Prime\n");
					return false;
				}
			}
			else {
				printf("ERROR Expected -> Term\n");
				return false;
			}
		}

		if (GetLexeme() == "/") {
			PrintLexerResult();
			NextInput();
			printf("<Term Prime -> / <Term> <Term Prime>\n");

			if (Term()) {
				if (TermPrime()) {
					return true;
				}
				else {
					printf("ERROR Expected -> Term Prime\n");
				}
			}
			else {
				printf("ERROR Expected -> Term\n");
			}
		}

		return false;
	}

	bool Ids() {
		printf("<IDs> -> <Identifier> | <Identifier>, <IDs>\n");
		if (GetToken() == "Identifier") {
			PrintLexerResult();
			NextInput();
			if (GetLexeme() == ",") {
				PrintLexerResult();
				NextInput();
				return Ids();
			}
			return true;
		}
		else {
			printf("ERROR Expected -> IDENTIFIER\n");
		}
		return false;
	}
	bool Primary() {
		if (PeekLexeme() == "(") {
			PrintLexerResult();
			NextInput();
			PrintLexerResult();
			NextInput();
			if (Ids()) {
				PrintLexerResult();
				return true;
			}
		}

		if (GetToken() == "Identifier") {
			PrintLexerResult();
			if (PeekLexeme() == "(") { 
				PrintLexerResult();
				if (Ids()) {
					if (GetLexeme() == ")") { 
						PrintLexerResult();
						printf("<Primary> -> <Identifier> (<IDs>)\n");
						return true;
					}
					else {
						printf("ERROR Expected -> Next To be )\n");
						return false;
					}
				}
				else {
					printf("ERROR Expected -> IDS\n");
					return false;
				}
				
			}
			else {
				printf("<Primary> -> <Identifier>\n");
				return true;
			}
		}
		else if (GetToken() == "Integer") {
			PrintLexerResult();
			printf("<Primary> -> <Integer>\n");
			return true;
		}
		else if (GetLexeme() == "(") {
			PrintLexerResult();
			if (Expression()) {
				if (GetLexeme() == ")") {
					PrintLexerResult();
					printf("<Primary> -> (<Expression>)\n");
					return true;
				}
				else {
					printf("ERROR Expected -> Next To be )\n");
					return false;
				}
			}
			else {
				printf("ERROR Expected -> EXPRESSION\n");
				return false;
			}
		}
		else if (GetLexeme() == "true") {
			PrintLexerResult();
			printf("<Primary> -> true\n");
			return true;
		}
		else if (GetLexeme() == "false") {
			PrintLexerResult();
			printf("<Primary> -> false\n");
			return true;
		}
		else {
			printf("ERROR Expected -> PRIMARY\n");
		}
		return false;
	}


public:
	SyntaxAnalyzer(vector<pair<Token, Lexeme>> &lexResult) {
		synInput = lexResult;

		for (auto test : synInput) {
			PrintHelper(test.first, test.second);
		}

		NextInput(); //sets the first pair
			Expression();
	}
};