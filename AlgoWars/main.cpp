#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

void splitString(string input, string* results);

int main() 
{
	ifstream inFile ("Input.dat");
	int ** requirements;
	int * intermediateResults;
	int modules;
	string temp;

	if (!inFile) 
	{
		cout << "ERROR: Could not find input file!" << endl;
		system("Pause");
		exit(0);
	}

	getline(inFile, temp);
	cout << temp << endl;

	modules = atoi(temp.c_str());
	requirements = new int*[modules];
	intermediateResults = new int[modules];

	for (int i=0; i<modules; i++)
	{
		string * tempResults = new string[modules];

		requirements[i] = new int[modules];
		getline(inFile, temp);
		splitString(temp, tempResults);

		for (int j = 0; j<modules; j++) 
		{
			requirements[i][j] = atoi(tempResults[j].c_str());
		}

		delete [] tempResults;
	}

	for (int i=0; i<modules; i++)
	{
		for (int j=0; j<modules; j++) 
		{
			cout << requirements[i][j] << " ";
		}
		cout << endl;
	}

	for (int i=0; i<modules; i++)
	{
		delete [] requirements[i];
	}

	delete [] requirements;
	delete [] intermediateResults;

	system("Pause");
	return 0;
}

void splitString(string input, string* results)
{
	string tempString = "";
	int counter = 0;

	for (unsigned int i=0; i < input.length(); i++)
	{
		if (input[i] == ' ')
		{
			if (tempString.length() > 0)
			{
				results[counter] = tempString;
				counter++;
			}
			tempString = "";
		}
		else 
		{
			tempString += input[i];
		}
	}

	if (tempString.length() > 0)
	{
		results[counter] = tempString;
		counter++;
	}

	return;
}
