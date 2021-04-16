#pragma once
#include <vector>
#include "common.h"
using namespace std;

/*class SyntaxAnalyzer
*	private:
*		typedef string Token: to make a string more readable
*		typedef string Lexeme: to make a string more readable
*
*		synInput: A vector that holds a pair of Token, Lexeme
*		pairInput: the Input from the lexical analyzer (pair)
*		outputtxt: a string that holds outputs that will be printed
*
*	private method:
*		GetToken: Gets the current Token
*		GetLexeme: Gets the current Lexeme
*		PeekLexeme: Gets the next Lexeme
*		NextInput: Gets the next Input(token,lexeme)
*		PrintLexerResult: Prints current Token, Lexeme being analyzed
*		[The rest of methods are commented within the class for better clarification]
*
*	public method:
*		Constructor: sets the value of synInput, which is what gets analyzed
*/
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
		return pairInput.second;
	}

	Lexeme PeekLexeme() 
	{
		if (!synInput.empty()) {
			return synInput.front().second;
		}
		return " ";
	}

	void NextInput() {
		if (!synInput.empty()) {
			pairInput = synInput.front();
			synInput.erase(synInput.begin());
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
		if (GetToken() == "Identifier" && PeekLexeme() != " ") {
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
		if (GetLexeme() == "-")
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
		if (GetToken() == "Identifier" && PeekLexeme() == "=") { 
			PrintLexerResult();
			Log("<Statement> -> <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>\n");
			Log("<Assign> -> <Identifier> = <Expression>\n");
			
			NextInput();
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
				NextInput();
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
			PrintLexerResult();
			Log("<Statement> -> <If>\n");
			Log("<If> -> if  ( <Condition>  ) <Statement>   endif |\nif  ( <Condition>  ) <Statement>   else  <Statement>  endif\n");
			NextInput();
			if (GetLexeme() == "(") {
				PrintLexerResult();
				NextInput();
				if (Conditional()) {
					if (GetLexeme() == ")") {
						PrintLexerResult();
						NextInput();

						if (GetLexeme() == "{") {
							PrintLexerResult();
							NextInput();
						}
						else {
							Log("ERROR Expected -> {\n");
							return false;
						}

						while (Statement()) {
						}

						if (GetLexeme() == "}") {
							PrintLexerResult();
							NextInput();
						}
						else {
							Log("ERROR Expected -> }\n");
							return false;
						}

						if (GetLexeme() == "endif") {
							PrintLexerResult();
							NextInput();
							return true;
						}
						else if (GetLexeme() == "else") {
							PrintLexerResult();
							NextInput();

							if (GetLexeme() == "{") {
								PrintLexerResult();
								NextInput();
							}
							else {
								Log("ERROR Expected -> {\n");
								return false;
							}

							while (Statement()) {
							}

							if (GetLexeme() == "}") {
								PrintLexerResult();
								NextInput();
							}
							else {
								Log("ERROR Expected -> }\n");
								return false;
							}
						}
					}
					else {
						Log("ERROR Expected -> )\n");
						return false;
					}
				}
				else {
					Log("ERROR Expected -> CONDITIONAL\n");
					return false;
				}
			}
			else {
				Log("ERROR Expected -> (\n");
				return false;
			}
		}
		return false;
	}

	bool While() {
		if (GetLexeme() == "while") {
			PrintLexerResult();
			Log("<Statement> -> <While>\n");
			Log("<While> -> ( <Condition>  )  <Statement>\n");
			NextInput();

			if (GetLexeme() == "(") {
				PrintLexerResult();
				NextInput();
				if (Conditional()) {
					if (GetLexeme() == ")") {
						PrintLexerResult();
						NextInput();

						if (GetLexeme() == "{") {
							PrintLexerResult();
							NextInput();
						}

						while (Statement()) {
			
						}

						if (GetLexeme() == "}") {
							PrintLexerResult();
							NextInput();
							return true;
						}
						else {
							Log("ERROR Expected -> }\n");
							return false;
						}
					}
					else {
						Log("ERROR Expected -> )\n");
						return false;
					}
				}
				else {
					Log("ERROR Expected -> CONDITIONAL\n");
					return false;
				}
			}
			else {
				Log("ERROR Expected -> (\n");
				return false;
			}
		}
		return false;
	}

	bool Conditional() {
		Log("<Condition> -> <Expression> <Relop> <Expression>\n");
		if (Expression()) {
			if (Relop()) {
				if (Expression()) {
					return true;
				}
				else if(GetToken() == "Integer" || GetToken() == "Real"){
					PrintLexerResult();
					Log("<Expression> -> <Term> <Expression Prime> \n");
					Log("<Term> -> <Factor> <Term Prime> \n");
					Log("<Factor> ->  <Primary> \n");
					Log("<Primary> -> <");
					cout << GetToken();
					myfile << GetToken();
					Log("> \n");
					NextInput();
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

	bool Statement() {
		if (Assign()) {
			return true;
		}
		if (Declaration()) {
			return true;
		}
		if (If()) {
			return true;
		}

		if (While()) {
			return true;
		}
		if (Expression()) {
			return true;
		}

		return false;
	}

public:
	SyntaxAnalyzer(vector<pair<Token, Lexeme>> &lexResult) {
		synInput = lexResult;
		NextInput(); //sets the first pair

		while (Statement()) {
		}
		return;
	}

	~SyntaxAnalyzer()
	{
	}
};