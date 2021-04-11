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
		if (!synInput.empty()) {
			pairInput = synInput.front();
			//cout << synInput.front().second;
			synInput.erase(synInput.begin());
			//cout << synInput.front().second;
		}
	}

	void PrintLexerResult() {
		myfile << "\nTOKEN -> " << GetToken() << endl;
		myfile << "LEXEME -> " << GetLexeme() << endl;
		myfile << "-------------------\n";
		cout << "\nTOKEN -> " << GetToken() << endl;
		cout << "LEXEME -> " << GetLexeme() << endl;
		cout << "-------------------\n";
	}

	bool Expression() {
		PrintLexerResult();
		Log("<Expression> -> <Term> <Expression Prime>\n");
		if (Term()) {
			if (ExpressionPrime()) {
				return true;
			}
			else {
				Log("ERROR Expected -> EXPRESSION PRIME\n");
			}
		}
		return false;
	}

	bool Term() {
		Log("<Term> -> <Factor> <Term Prime>\n");
		if (Factor()) {
			NextInput();
			if (TermPrime()) {
				return true;
			}
			else {
				Log("ERROR Expected -> TERM PRIME\n");
			}
		}
		else {
			Log("ERROR Expected -> FACTOR\n");
		}
		return false;
	}

	bool ExpressionPrime() {
		if (GetLexeme() == "+") {
			PrintLexerResult();
			NextInput();
			Log("<Expression Prime> + <Term> <Expression Prime>\n");
			PrintLexerResult();
			if (Term()) {
				if (ExpressionPrime()) {
					return true;
				}
				else {
					Log("ERROR Expected -> EXPRESSION PRIME\n");
					return false;
				}
			}
			else {
				Log("ERROR Expected -> TERM\n");
				return false;
			}
		}

		else if (GetLexeme() == "-") {
			PrintLexerResult();
			NextInput();
			Log("<Expression Prime> - <Term> <Expression Prime>\n");
			PrintLexerResult();
			if (Term()) {
				if (ExpressionPrime()) {
					return true;
				}
				else {
					Log("ERROR Expected -> EXPRESSION PRIME\n");
					return false;
				}
			}
			else {
				Log("ERROR Expected -> TERM\n");
				return false;
			}
		}

		return true;
	}

	bool Factor() {
		if (GetLexeme() == "-") //For negative  factors
		{
			PrintLexerResult();
			Log("<Factor> -> - <Primary>\n");
			if (Primary()) {
				myfile << outputtxt;
				cout << outputtxt;
				return true;
			}
		}
		else if (Primary()) {
			Log("<Factor> ->  <Primary>\n");
			myfile << outputtxt;
			cout << outputtxt;
			return true;
		}
		else {
			Log("ERROR Expected -> FACTOR\n");
			return false;
		}

		return false;
	}

	bool TermPrime() {
		if (GetLexeme() == "*") {
			PrintLexerResult();
			NextInput();
			Log("<Term Prime -> * <Term> <Term Prime>\n");
			PrintLexerResult();
			if (Term()) {
				if (TermPrime()) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				Log("ERROR Expected -> Term\n");
				return false;
			}
		}

		if (GetLexeme() == "/") {
			PrintLexerResult();
			NextInput();
			Log("<Term Prime -> / <Term> <Term Prime>\n");
			PrintLexerResult();
			if (Term()) {
				if (TermPrime()) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				Log("ERROR Expected -> Term\n");
				return false;
			}
		}

		return true;
	}

	bool Ids() {
		Log("<IDs> -> <Identifier> | <Identifier>, <IDs>\n");
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
			Log("ERROR Expected -> IDENTIFIER\n");
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
						Log("<Primary> -> <Identifier> (<IDs>)\n");
						return true;
					}
					else {
						Log("ERROR Expected -> Next To be )\n");
						return false;
					}
				}
				else {
					Log("ERROR Expected -> IDS\n");
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
			Log("<Primary> -> <Integer>\n");
			return true;
		}
		else if (GetLexeme() == "(") {
			//PrintLexerResult();
			NextInput();
			if (Expression()) {
				if (GetLexeme() == ")") {
					PrintLexerResult();
					Log("<Primary> -> (<Expression>)\n");
					return true;
				}
				else {
					Log("ERROR Expected -> Next To be )\n");
					return false;
				}
			}
			else {
				Log("ERROR Expected -> EXPRESSION\n");
				return false;
			}
		}
		else if (GetLexeme() == "true") {
			PrintLexerResult();
			Log("<Primary> -> true\n");
			return true;
		}
		else if (GetLexeme() == "false") {
			PrintLexerResult();
			Log("<Primary> -> false\n");
			return true;
		}
		else {
			Log("ERROR Expected -> PRIMARY\n");
		}
		return false;
	}

	bool Assign() {
		if (GetToken() == "Identifier") { 
			PrintLexerResult();
			Log("<Assign> -> <Identifier> = <Expression>\n");
			
			NextInput();
			if (GetLexeme() == "=") {
				PrintLexerResult();
				NextInput();
				if (Expression()) {
					if (GetLexeme() == ";") {
						PrintLexerResult();
						Log("<Expression Prime> -> <Empty>\n");
						Log("<Empty> -> Epsilon\n");
						NextInput();
						return true;
					}
					else {
						Log("ERROR Expected -> ;\n");
						return false;
					}
				}
				else {
					Log("ERROR Expected -> EXPRESSION\n");
					return false;
				}
			}
			else {
				Log("ERROR Expected -> =\n");
				return false;
			}
		}

		return false;
	}

	vector<string> declareKeywords = { "int", "bool", "float", "double", "string" };

	bool Declaration() {
		if (count(declareKeywords.begin(), declareKeywords.end(), GetLexeme())) {
			PrintLexerResult();
			Log("<Statement> -> <Declarative>\n");
			if (Type()) {
				NextInput();
				PrintLexerResult();
				myfile << "<ID> -> " << GetLexeme() << endl;
				cout << "<ID> -> " << GetLexeme() << endl;
				return true;
			}
			return false;
		} 
		else {
			return false;
		}
	}

	bool Type() {
		myfile << "<Type> -> " << GetLexeme() << endl;
		cout << "<Type> -> " << GetLexeme() << endl;
		return true;
	}

	bool If() {

		if (GetLexeme() == "if") {
			Log("<Statement> -> <If>\n");
			Log("<If> -> if  ( <Condition>  ) <Statement>   endif |\n if  ( <Condition>  ) <Statement>   else  <Statement>  endif\n");
			PrintLexerResult();
			NextInput();
			if (GetLexeme() == "(") {
				PrintLexerResult();
				NextInput();
				if (Conditional()) {
					if (GetLexeme() == ")") {
						PrintLexerResult();
						NextInput();
						//if (Statement())
					}
				}
			}
		}

	}

	bool Conditional() {
		Log("<Condition> -> <Expression> <Relop> <Expression>\n");
		if (Expression()) {
			if (Relop()) {
				if (Expression()) {
					return true;
				}
				else {
					Log("ERROR Expected -> EXPRESSION\n");
					return false;
				}
			}
			else {
				Log("ERROR Expected -> RELOP\n");
				return false;
			}
		}
		else {
			Log("ERROR Expected -> EXPRESSION\n");
			return false;
		}
		return false;
	}

	bool Relop() {
		Log("<Relop> -> == | ^= | > | < | => | =<\n");
		PrintLexerResult();
		NextInput();
		return true;
	}

public:
	SyntaxAnalyzer(vector<pair<Token, Lexeme>> &lexResult) {
		synInput = lexResult;
		NextInput(); //sets the first pair
		if (Assign()) {
			return;
		}

		if (Declaration()) {
			return;
		}

	}

	~SyntaxAnalyzer()
	{
	}
};