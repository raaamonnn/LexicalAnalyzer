# LexicalAnalyzer


          Assignment 1 - Lexical Analyzer Documentation
Problem Statement

	The purpose of this assignment is to construct a functioning lexical analyzer (lexer). The most important component of the assignment is to create a function called lexer() that will return the correct token whenever it is necessary. There will be two parts of the output of the lexer, the first part being a field for the token, and the second part is another field that contains the value of the token, also known as a lexeme. In addition, we have to build the entire lexer using a finite state machine (FSM), or at least building the identifier, integer, and real using an FSM. 
	
How to use your program

	The program that we have created is fairly simple. All that is required is a text file name as input. When the executable (LexicalAnalyzer.exe ) is run it will ask the user to type in the name of the file to be analyzed(Keep in mind this file must be a .txt file and be located in the same folder as our executable). Upon locating this file, it will parse through the entirety of the file and will output the tokens and lexemes in the order that they were read in. The output will be located on the console. If the user wants to analyze a new text file, they must rerun the program and type in the name of the new text file to be analyzed. 
	
Design of your program

 The main function of the program is the analyze function, which will first look through the file word by word while looking specifically for the ! character, which would indicate that the following section will be a comment which needs to be ignored. After checking that the word isn't part of a comment, it will then pass the word into the Lexer function. This function will look through the word and look for any separators or operators. Since our LexicalAnalyzer class inherits from a FSM class, it manages the separate states that the analyzer is currently at. We begin at the starting state and go to the next state according to our input. By the time we are at the last state, the word has been fully parsed out and ready to be printed onto the console. Once a Separator or Operator is  found, it will be added to the list of token/lexemes with the correct identification and will pass the rest of the word into a final function ParseSub. This function will identify if the remaining word is a keyword, number, or identifier. To identify it as a keyword, it will try to find if it matches with a string that is contained within an unordered-map that holds all the different keywords. Keep in mind that all these actions are also managed and stored as separate states in the finite state machine. Our lexeme function returns a pair which consists of two strings, the first string being the Token and the second being the Lexeme. Once it has identified the correct lexeme, it will print it out in the correct format. 
