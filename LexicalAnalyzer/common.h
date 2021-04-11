#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
template <class T>
void PrintHelper(string type, T value)
{
	//print function to format results
	cout << left << setw(12) << type << " = " << value << endl;
}