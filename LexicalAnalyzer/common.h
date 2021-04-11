#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

extern ofstream myfile;

//#define Log(text, ...) myfile << text;//printf(text, __VA_ARGS__)

template<typename ...A>
void Log(const char* text, const A ...arguments)
{
	myfile << text;
	printf(text, arguments...);
}
template <class T>
void PrintHelper(string type, T value)
{
	//print function to format results
	cout << left << setw(12) << type << " = " << value << endl;
	myfile << left << setw(12) << type << " = " << value << endl;
}