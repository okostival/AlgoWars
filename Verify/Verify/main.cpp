#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void splitString(string input, string* results);
unsigned int calcLength(int modules, int **& requirements, int *& indices);

int main() 
{
	ifstream inFile ("input.dat");
	int ** requirements;
	int * indices;
	int modules;
	int result;
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

	cout << "Please enter your nodes in order for verification of total:" << endl;

	for (int i=0; i<modules; i++)
	{
		string * tempResults = new string[modules];
		requirements[i] = new int[modules];
		getline(inFile, temp);
		splitString(temp, tempResults);
		int currentNode;

		for (int j = 0; j<modules; j++) 
		{
			requirements[i][j] = atoi(tempResults[j].c_str());
		}

		cout << "Number " << i + 1 << ": " << flush;
		cin >> currentNode;
		indices[i] = currentNode - 1;

		delete [] tempResults;
	}

	result = calcLength(modules, requirements, indices);

	cout << endl << "The total length for the nodes reported is: " << result << endl;

	for (int i=0; i<modules; i++)
	{
		delete [] requirements[i];
	}

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