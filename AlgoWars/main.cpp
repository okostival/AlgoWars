#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void splitString(string input, string* results);
unsigned int calcLength(int modules, int **& requirements, int *& indices);

int main() 
{
	ifstream inFile ("Input.dat");
	int ** requirements;
	int * indices;
	int * bestOption;
	int modules;
	unsigned int minLength;
	string temp;

	if (!inFile) 
	{
		cout << "ERROR: Could not find input file!" << endl;
		system("Pause");
		exit(0);
	}

	getline(inFile, temp);

	modules = atoi(temp.c_str());
	requirements = new int*[modules];
	indices = new int[modules];
	bestOption = new int[modules];

	for (int i=0; i<modules; i++)
	{
		string * tempResults = new string[modules];
		indices[i] = i;
		bestOption[i] = i;
		requirements[i] = new int[modules];
		getline(inFile, temp);
		splitString(temp, tempResults);

		for (int j = 0; j<modules; j++) 
		{
			requirements[i][j] = atoi(tempResults[j].c_str());
		}

		delete [] tempResults;
	}

	minLength = calcLength(modules, requirements, indices);

	while(next_permutation(indices, (indices+modules)))
	{
		int tempLength = calcLength(modules, requirements, indices);

		if (tempLength < minLength)
		{
			minLength = tempLength;
			copy(indices, indices + modules, bestOption);
		}
	}

	for (int i=0; i<modules; i++)
	{
		cout << bestOption[i] + 1 << " " ;
	}
	cout << endl << minLength << endl;;

	for (int i=0; i<modules; i++)
	{
		delete [] requirements[i];
	}

	delete [] bestOption;
	delete [] indices;
	delete [] requirements;

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

unsigned int calcLength(int modules, int **& requirements, int *& indices)
{
	unsigned int length = 0;

	for (int i=0; i<(modules-1); i++)
	{
		for (int j=i+1; j<modules; j++)
		{
			length += (requirements[indices[i]][indices[j]] * (j-i));
		}
	}

	return length;
}