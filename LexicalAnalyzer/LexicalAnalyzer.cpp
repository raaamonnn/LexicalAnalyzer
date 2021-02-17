#include "LexicalAnalyzer.h"

template <class T>
void PrintHelper(string type, T value)
{
	cout << left << setw(12) << type << " = " << value << endl;
}

void LexicalAnalyzer::ParseSub(string word, vector<pair<Token, Lexeme>>& subStrings)
{
	auto itr = language.find(word);
	if (itr != language.end()) {
		PrintHelper(itr->second, itr->first);
		subStrings.push_back(pair<Token, Lexeme>(itr->second, word));
		fileLanguage.insert(pair<Token, Lexeme>(itr->first, itr->second));
	}
	else //check if its a number/identifier
	{
		if (word.find('.') < word.length()) {
			PrintHelper("Float", word);
			fileLanguage.insert(pair<Token, Lexeme>("Float", word));
			subStrings.push_back(pair<Token, Lexeme>("Float", word));

		}
		else if (!word.empty() && std::find_if(word.begin(), word.end(), [](unsigned char c) { return !std::isdigit(c); }) == word.end()) {
			PrintHelper("Integer", word);
			fileLanguage.insert(pair<Token, Lexeme>("Integer", word));
			subStrings.push_back(pair<Token, Lexeme>("Integer", word));

		}
		else if (word != "") {
			PrintHelper("Identifier", word);
			fileLanguage.insert(pair<Token, Lexeme>("Identifier", word));
			subStrings.push_back(pair<Token, Lexeme>("Identifier", word));
		}
	}
}

vector<pair<Token, Lexeme>> LexicalAnalyzer::GiveSub(string word)
{
	vector<pair<Token, Lexeme>> subStrings;

	for (int i = 0; i < word.length(); i++) {

		if (word[i] == '(' || word[i] == ')' || word[i] == '{'
			|| word[i] == '}' || word[i] == '[' || word[i] == ']'
			|| word[i] == ',' || word[i] == '.' || word[i] == ':'
			|| word[i] == ';') { //all seperators

			auto sub = word.substr(0, i);

			if (!sub.empty()){
				ParseSub(sub, subStrings);
			}

			subStrings.push_back(pair<Token, Lexeme>("Seperator",string(1, word[i])));
			PrintHelper("Seperator", string(1, word[i]));

			word.erase(0, i + 1);
			i = -1;
			continue;
		}

		if (word[i] == '+' || word[i] == '-' || word[i] == '='
			|| word[i] == '*' || word[i] == '/' || word[i] == '%'
			|| word[i] == '<' || word[i] == '>') { //all seperators

			auto sub = word.substr(0, i);

			if (!sub.empty()){
				ParseSub(sub, subStrings);
			}

			subStrings.push_back(pair<Token, Lexeme>("Operator", string(1, word[i])));
			PrintHelper("Operator", string(1, word[i]));

			word.erase(0, i + 1);
			i = -1;
		}
	}

	if(!word.empty())
		ParseSub(word, subStrings);

	return subStrings;
}

LexicalAnalyzer::LexicalAnalyzer(string inputFile) {
	//read the file into their associated tokens and lexemes

	ifstream file(inputFile);
	string word = "";
	
	cout << "TOKEN    --    LEXEME\n";

	bool isComment = false;
	while (!file.eof()) {

		file >> word;

		//if its a comment ignore
		if (word.find('!') != string::npos) {
			//counts number of !
			int numEx = count(word.begin(), word.end(), '!');
			//number of ! are odd toggle isComment
			if((numEx % 2) > 0)
			{
				isComment = !isComment;
			}
			continue;
		}
		
		if (!isComment) 
		{
			auto sub = GiveSub(word);
		}
	}

	file.close();

	//-------
}
