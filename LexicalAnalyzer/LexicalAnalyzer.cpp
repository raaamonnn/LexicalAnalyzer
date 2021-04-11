#include "LexicalAnalyzer.h"

void LexicalAnalyzer::GetKeyword(string word, std::list<pair<const Token, Lexeme>,
	std::allocator<pair<const Token, Lexeme>>>::const_iterator itr, int state)
{
	//word is a keyword 
	subStrings.push_back(pair<Token, Lexeme>(itr->second, word));

	FSM::SetCurrentState(state);
}

void LexicalAnalyzer::GetIdentifies(string word, vector<pair<Token, Lexeme>>& subStrings, int state )
{
	if (word.find('.') < word.length()) {
		//if word contains a period then it is float
		subStrings.push_back(pair<Token, Lexeme>("Real", word));

	}
	else if (!word.empty() && std::find_if(word.begin(), word.end(), [](unsigned char c) { return !std::isdigit(c); }) == word.end()) {
		//word is an int 
		subStrings.push_back(pair<Token, Lexeme>("Integer", word));

	}
	else if (word != "") {
		//word is an Identifies 
		subStrings.push_back(pair<Token, Lexeme>("Identifier", word));
	}

	FSM::SetCurrentState(state);
}

void LexicalAnalyzer::ParseSub(string word, vector<pair<Token, Lexeme>>& subStrings)
{
	//Try to find word in our map to see if its keyword
	std::list<pair<const Token, Lexeme>, 
		std::allocator<pair<const Token, Lexeme>>>::const_iterator itr = language.find(word);
	if (itr != language.end()) {
		GetKeyword(word, itr);
	}
	else //check if its a number/identifier
	{
		GetIdentifies(word, subStrings);
	}
}

bool LexicalAnalyzer::GetSeparator()
{
	if (currentWord[i] == '(' || currentWord[i] == ')' || currentWord[i] == '{'
		|| currentWord[i] == '}' || currentWord[i] == '[' || currentWord[i] == ']'
		|| currentWord[i] == ',' || currentWord[i] == ':'
		|| currentWord[i] == ';') { //all seperators

		//Word contains seperator and it must be removed!
		// returns the word without seperator 
		auto sub = currentWord.substr(0, i);
		//cout << "CURRENT I -> " << i << endl;
		if (!sub.empty()) {
			//see the type of word
			ParseSub(sub, subStrings);
		}

		//insert seperator in a vector
		subStrings.push_back(pair<Token, Lexeme>("Separator", string(1, currentWord[i])));

		currentWord.erase(0, i + 1);
		i = -1;
		return true;
	}

	return false;
}

bool LexicalAnalyzer::GetOperator()
{
	if (currentWord[i] == '+' || currentWord[i] == '-' || currentWord[i] == '='
		|| currentWord[i] == '*' || currentWord[i] == '/' || currentWord[i] == '%'
		|| currentWord[i] == '<' || currentWord[i] == '>')
	{ //all operator
		//Word contains seperator and it must be removed!
		// returns the word without seperator 
		auto sub = currentWord.substr(0, i);

		if (!sub.empty()) {
			//see the type of word
			ParseSub(sub, subStrings);
		}

		//insert seperator in a vector
		subStrings.push_back(pair<Token, Lexeme>("Operator", string(1, currentWord[i])));

		currentWord.erase(0, i + 1);
		i = -1;
		return true;
	}
	return false;
}

bool LexicalAnalyzer::TriggerEvent()
{
	int index = 0;
	do
	{
		index++;
		auto state = FSM::GetNextState();

		switch (state)
		{
		case 1:
		{
			auto stat = GetSeparator();

			if (stat)
				return true;
			break;
		}

		case 2:
		{
			auto stat = GetOperator();

			if (stat)
				return true;
			break;
		}
		}
	} while (index <= 2);

	return false;
}

vector<pair<Token, Lexeme>> LexicalAnalyzer::Lexer()
{
	for (i = 0; i < currentWord.length(); i++) {
		TriggerEvent();
	}

	//if the word doesn't contain operators or separators then 
	// it must be a different lexeme
	if(!currentWord.empty())
		ParseSub(currentWord, subStrings);

	return subStrings;
}

void LexicalAnalyzer::ParseSyntax()
{
	for (auto token : fileLanguage)
	{
		
	}
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
			subStrings.clear();
			this->currentWord = word;
			//Parse each word using function ParseWord
			auto subs = Lexer();
			for (auto sub : subs)
			{
				fileLanguage.push_back({ sub.first, sub.second });
				PrintHelper(sub.first, sub.second);
			}
		}
	}

	file.close();

	return true;
}

void LexicalAnalyzer::PrintLanguage()
{
	for (auto test : fileLanguage) {
		PrintHelper(test.first, test.second);
	}
}

LexicalAnalyzer::LexicalAnalyzer(string inputFile) : FSM(2){
	//Set the file name
	this->fileName = inputFile;
}
