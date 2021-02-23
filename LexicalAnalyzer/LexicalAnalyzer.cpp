#include "LexicalAnalyzer.h"

template <class T>
void PrintHelper(string type, T value)
{
	//print function to format results
	cout << left << setw(12) << type << " = " << value << endl;
}

void LexicalAnalyzer::ParseSub(string word, vector<pair<Token, Lexeme>>& subStrings)
{
	//Try to find word in our map to see if its keyword
	auto itr = language.find(word);

	if (itr != language.end()) {
		//word is a keyword 
		// printed and inserted into our map and vector
		PrintHelper(itr->second, itr->first);
		subStrings.push_back(pair<Token, Lexeme>(itr->second, word));
		fileLanguage.insert(pair<Token, Lexeme>(itr->first, itr->second));
	}
	else //check if its a number/identifier
	{
		if (word.find('.') < word.length()) {
			//if word contains a period then it is float
			// printed and inserted into our map and vector
			PrintHelper("Float", word);
			fileLanguage.insert(pair<Token, Lexeme>("Float", word));
			subStrings.push_back(pair<Token, Lexeme>("Float", word));

		}
		else if (!word.empty() && std::find_if(word.begin(), word.end(), [](unsigned char c) { return !std::isdigit(c); }) == word.end()) {
			//word is an int 
			// printed and inserted into our map and vector
			PrintHelper("Integer", word);
			fileLanguage.insert(pair<Token, Lexeme>("Integer", word));
			subStrings.push_back(pair<Token, Lexeme>("Integer", word));

		}
		else if (word != "") {
			//word is an Identifies 
			// printed and inserted into our mpa and vector
			PrintHelper("Identifier", word);
			fileLanguage.insert(pair<Token, Lexeme>("Identifier", word));
			subStrings.push_back(pair<Token, Lexeme>("Identifier", word));
		}
	}
}

vector<pair<Token, Lexeme>> LexicalAnalyzer::ParseWord(string word)
{
	//vector that holds substrings(keys) with correct lexeme 
	vector<pair<Token, Lexeme>> subStrings;

	for (int i = 0; i < word.length(); i++) {

		if (word[i] == '(' || word[i] == ')' || word[i] == '{'
			|| word[i] == '}' || word[i] == '[' || word[i] == ']'
			|| word[i] == ',' || word[i] == '.' || word[i] == ':'
			|| word[i] == ';') { //all seperators
			//Word contains seperator and it must be removed!
			// returns the word without seperator 
			auto sub = word.substr(0, i);

			if (!sub.empty()){
				//see the type of word
				ParseSub(sub, subStrings);
			}

			//insert seperator in a vector
			subStrings.push_back(pair<Token, Lexeme>("Separator",string(1, word[i])));
			//print seperator
			PrintHelper("Separator", string(1, word[i]));

			word.erase(0, i + 1);
			i = -1;
			continue;
		}

		if (word[i] == '+' || word[i] == '-' || word[i] == '='
			|| word[i] == '*' || word[i] == '/' || word[i] == '%'
			|| word[i] == '<' || word[i] == '>') { //all operator

			//Word contains seperator and it must be removed!
			// returns the word without seperator 
			auto sub = word.substr(0, i);

			if (!sub.empty()){
				//see the type of word
				ParseSub(sub, subStrings);
			}

			//insert seperator in a vector
			subStrings.push_back(pair<Token, Lexeme>("Operator", string(1, word[i])));
			//print seperator
			PrintHelper("Operator", string(1, word[i]));

			word.erase(0, i + 1);
			i = -1;
		}
	}

	//if the word doesn't contain operators or separators then 
	// it must be a different lexeme
	if(!word.empty())
		ParseSub(word, subStrings);

	return subStrings;
}

bool LexicalAnalyzer::Analyze()
{
	if (this->fileName.empty()) return false;

	ifstream file(this->fileName);
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
			if ((numEx % 2) > 0)
			{
				isComment = !isComment;
			}
			continue;
		}

		if (!isComment)
		{
			//Parse each word using function ParseWord
			auto sub = ParseWord(word);
		}
	}

	file.close();

	return true;
}

LexicalAnalyzer::LexicalAnalyzer(string inputFile) {
	//Set the file name
	this->fileName = inputFile;
}
