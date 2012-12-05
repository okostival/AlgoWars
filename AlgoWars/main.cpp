#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct ModuleNode {
	int index;
	int size;
}; 

struct ModuleSubset {
	int numNodes;
	int * indices;
	int * bestOption;
};

void splitString(string input, string* results);
unsigned int calcLength(int modules, int **& requirements, int *& indices);
void computeExhaustiveOnSubset(ModuleSubset& subset, int **& requirements);
bool compare (const ModuleNode& lhs, const ModuleNode& rhs);

int main() 
{
	ifstream inFile ("input.dat");
	int ** requirements;
	int * indices;
	int * bestOption;
	int * moduleIndices;
	int modules;
	int moduleSubsetCount;
	unsigned int minLength;
	string temp;
	vector<ModuleNode> moduleNodes;
	vector<ModuleNode>::iterator moduleIterator;
	ModuleSubset * moduleSubsets;

	if (!inFile) 
	{
		cout << "ERROR: Could not find input file!" << endl;
		system("Pause");
		exit(0);
	}

	getline(inFile, temp);

	modules = atoi(temp.c_str());
	moduleSubsetCount = (modules+9)/10;
	requirements = new int*[modules];
	indices = new int[modules];
	bestOption = new int[modules];
	moduleSubsets = new ModuleSubset[moduleSubsetCount];
	moduleIndices = new int[moduleSubsetCount];

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

	for (int i=0; i<modules; i++)
	{
		ModuleNode tempNode;
		int sum = 0;

		for (int j=0; j<modules; j++)
		{
			sum += requirements[i][j];
		}

		tempNode.index = i;
		tempNode.size = sum;

		//moduleNodes.emplace(moduleNodes.end(), tempNode);
		moduleNodes.push_back(tempNode);
	}

	sort (moduleNodes.begin(), moduleNodes.end(), compare);
	reverse (moduleNodes.begin(), moduleNodes.end());

	int counter = 0;
	int subsetCount = 0;
	int * tempIndices;
	int * tempBestOption;

	if (moduleNodes.size() >= 10)
	{
		tempIndices = new int[10];
		tempBestOption = new int[10];
	}
	else
	{
		tempIndices = new int[moduleNodes.size()];
		tempBestOption = new int[moduleNodes.size()];
	}

	while (!moduleNodes.empty())
	{
		tempIndices[counter] = moduleNodes.begin()->index;
		tempBestOption[counter] = moduleNodes.begin()->index;

		if (counter == 9)
		{
			ModuleSubset tempSubset;

			tempSubset.numNodes = 10;
			tempSubset.indices = tempIndices;
			tempSubset.bestOption = tempBestOption;

			moduleSubsets[subsetCount] = tempSubset;
			subsetCount++;

			if (moduleNodes.size() > 10)
			{
				tempIndices = new int[10];
				tempBestOption = new int[10];
			}
			else if (moduleNodes.size() > 1)
			{
				tempIndices = new int[moduleNodes.size() - 1];
				tempBestOption = new int[moduleNodes.size() - 1];
			}
		}

		moduleNodes.erase(moduleNodes.begin());
		counter = (++counter) % 10;
	}

	if (counter != 0)
	{
		ModuleSubset tempSubset;

		tempSubset.numNodes = counter;
		tempSubset.indices = tempIndices;
		tempSubset.bestOption = tempBestOption;

		moduleSubsets[subsetCount] = tempSubset;
	}

	//
	// This was the original proof of concept for the exhaustive search
	//
	//minLength = calcLength(modules, requirements, indices);

	//while(next_permutation(indices, (indices+modules)))
	//{
	//	int tempLength = calcLength(modules, requirements, indices);

	//	if (tempLength < minLength)
	//	{
	//		minLength = tempLength;
	//		copy(indices, indices + modules, bestOption);
	//	}
	//}

	//for (int i=0; i<modules; i++)
	//{
	//	cout << bestOption[i] + 1 << " " ;
	//}
	//cout << endl << minLength << endl;

		
	for (int i=0; i<moduleSubsetCount; i++)
	{
		moduleIndices[i] = i;
		computeExhaustiveOnSubset(moduleSubsets[i], requirements);
	}

	for (int i=0; i<moduleSubsetCount; i++)
	{
		copy(moduleSubsets[i].bestOption, moduleSubsets[i].bestOption+moduleSubsets[i].numNodes, indices+(i*10));
	}

	copy(indices, indices + modules, bestOption);
	minLength = calcLength(modules, requirements, indices);

	while(next_permutation(moduleIndices, (moduleIndices+moduleSubsetCount)))
	{
		int previousModules = 0;

		for (int i=0; i<moduleSubsetCount; i++)
		{
			copy(moduleSubsets[moduleIndices[i]].bestOption, moduleSubsets[moduleIndices[i]].bestOption+moduleSubsets[moduleIndices[i]].numNodes, indices+previousModules);
			previousModules += moduleSubsets[moduleIndices[i]].numNodes;
		}

		int tempLength = calcLength(modules, requirements, indices);

		if (tempLength < minLength)
		{
			minLength = tempLength;
			copy(indices, indices + modules, bestOption);
		}
	}
		
	ofstream outFile("output.txt");
	for (int i=0; i<modules; i++)
	{
		cout << bestOption[i] + 1 << " " ;
		outFile << bestOption[i] + 1 << " ";
	}
	cout << endl << minLength << endl;
	outFile << endl << minLength << endl;
	outFile.close();

	for (int i=0; i<modules; i++)
	{
		delete [] requirements[i];
	}

	for (int i=0; i<moduleSubsetCount; i++)
	{
		delete [] moduleSubsets[i].indices;
		delete [] moduleSubsets[i].bestOption;
	}

	delete [] indices;
	delete [] bestOption;
	delete [] moduleSubsets;
	delete [] moduleIndices;
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

void computeExhaustiveOnSubset(ModuleSubset& subset, int **& requirements)
{
	int minLength = calcLength(subset.numNodes, requirements, subset.indices);

	while(next_permutation(subset.indices, (subset.indices+subset.numNodes)))
	{
		int tempLength = calcLength(subset.numNodes, requirements, subset.indices);

		if (tempLength < minLength)
		{
			minLength = tempLength;
			copy(subset.indices, subset.indices + subset.numNodes, subset.bestOption);
		}
	}
}

bool compare (const ModuleNode& lhs, const ModuleNode& rhs)
{
	if (lhs.size < rhs.size) return true;
	return false;
}