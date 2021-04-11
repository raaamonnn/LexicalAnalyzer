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
	string outputtxt;

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
		//cout << synInput.front().second;
		synInput.erase(synInput.begin());
		//cout << synInput.front().second;
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
			cout << "XXDDDDDD";
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

		else if (GetToken() == "-") {
			PrintLexerResult();
			NextInput();
			printf("<Expression Prime> - <Term> <Expression Prime>\n");
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

		return true;
	}

	bool Factor() {
		cout << "FACTOR GETS CALLED\n";
		if (GetLexeme() == "-") //For negative  factors
		{
			PrintLexerResult();
			printf("<Factor> -> - <Primary>\n");
			if (Primary()) {
				cout << outputtxt;
				return true;
			}
		}
		else if (Primary()) {
			printf("<Factor> ->  <Primary>\n");
			cout << outputtxt;
			return true;
		}
		else {
			printf("ERROR Expected -> FACTOR\n");
			return false;
		}

		return false;
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
					return false;
				}
			}
			else {
				printf("ERROR Expected -> Term\n");
				return false;
			}
		}

		return true;
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
			if (PeekLexeme() == "(") { 
				NextInput();
				PrintLexerResult();
				if (Ids()) {
					NextInput();
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
				outputtxt = "<Primary> -> <Identifier>\n";
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
			NextInput();
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

	bool Assign() {
		if (GetToken() == "Identifier") {
			printf("<Assign> -> <Identifier> = <Expression>\n");
			PrintLexerResult();
			NextInput();
			if (GetLexeme() == "=") {
				PrintLexerResult();
				NextInput();
				if (Expression()) {
					if (GetLexeme() == ";") {
						PrintLexerResult();
						NextInput();
						return true;
					}
					else {
						printf("ERROR Expected -> ;\n");
						return false;
					}
				}
				else {
					printf("ERROR Expected -> EXPRESSION\n");
					return false;
				}
			}
			else {
				printf("ERROR Expected -> =\n");
				return false;
			}
		}

		return false;
	}


public:
	SyntaxAnalyzer(vector<pair<Token, Lexeme>> &lexResult) {
		synInput = lexResult;

		NextInput(); //sets the first pair
		Assign();
	}
};