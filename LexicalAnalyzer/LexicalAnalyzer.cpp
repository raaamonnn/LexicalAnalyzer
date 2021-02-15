#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(string inputFile) {
	//read the file into their associated tokens and lexemes

	ifstream file(inputFile);
	string word = "";

	cout << "TOKEN  -- LEXEME\n";
	bool isComment = false;
	while (!file.eof()) {

		file >> word;

		//if its a comment ignore
		if (word.find('!') < word.length()) {
			isComment = !isComment;
			continue;
		}
		
		if (!isComment) {
			vector<int> erase; //gotta delete the seperators out of the string later
			//check for seperator
			for (int i = 0; i < word.length(); i++) {
				if (word[i] == '(' || word[i] == ')' || word[i] == '{' || word[i] == '}' || word[i] == '[' || word[i] == ']' || word[i] == ',' || word[i] == '.' || word[i] == ':' || word[i] == ';') { //all seperators
					cout << "Seperator" << " -- " << word[i] << endl;
					fileLanguage.insert(pair<Token, Lexeme>("Seperator", string(1,word[i])));
					erase.push_back(i); 
				}
			}

			//takes the seperators out of the string starting from the back
			for (vector<int>::reverse_iterator i = erase.rbegin();i != erase.rend(); ++i) {
				word.erase(word.begin() + *i); 
			}

			//check if its in our language
			auto itr = language.find(word);
			if (itr != language.end()) {
				cout << itr->second << " -- " << itr->first << endl;
				fileLanguage.insert(pair<Token, Lexeme>(itr->first, itr->second));
			}
			//check if its a number/identifier
			else { 
				//either a float
				if (word.find('.') < word.length()) {
					cout << "Float" << " -- " << word << endl;
					fileLanguage.insert(pair<Token, Lexeme>("Float", word));
				} 
				//int
				else if (!word.empty() && std::find_if(word.begin(), word.end(), [](unsigned char c) { return !std::isdigit(c); }) == word.end()) {
					cout << "Integer" << " -- " << word << endl;
					fileLanguage.insert(pair<Token, Lexeme>("Integer", word));
				}
				//or an identifier
				else if (word != ""){
					cout << "Identifier" << " -- " << word << endl;
					fileLanguage.insert(pair<Token, Lexeme>("Identifier", word));
				}

				
			}
		}
	}

	file.close();

	//-------
}
