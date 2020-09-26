#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

vector<int> read_inputfile(string filename) // make a random sequence whose size is num
{
	fstream file;

	file.open(filename, ios::in);

	string temp;

	if (getline(file, temp))
	{
		vector<int> sequence(stoi(temp));

		for (int i = 0; i < sequence.size(); i++)
		{
			if (getline(file, temp))
			{
				sequence[i] = stoi(temp);
			}
			else
			{
				cout << "Not enough numbers in the file.";
				break;
			}
		}
		cout << "Read " << sequence.size() << " numbers in " << filename << ".";
		file.close();
		return sequence;
	}
	else
	{
		cout << "Nothing in the file.";
		file.close();
		return vector<int>(0);
	}
}

void make_outputfile(vector<int>& sequence) // make a random sequence whose size is num
{
	fstream file;

	file.open("output.txt", ios::out | ios::trunc);

	file << sequence.size() << endl;

	for (int i = 0; i < sequence.size(); i++)
	{
		file << sequence[i] << endl;
	}
	file.close();
}

void insertion_sort(vector<int>& sequence)
{
	int x = 0;
	for (int i = 1; i < sequence.size(); i++)
	{
		x = sequence[i];//store the value the key
		int j = i - 1;//compare from the left and first one of the key 
		for (; j >= 0 && sequence[j] > x; j--)//compare one by one until someone is smaller than the key
		{
			sequence[j + 1] = sequence[j];
		}
		sequence[j + 1] = x;//place the key into the place we find
	}
}

int main(int argc, char *argv[]) {

	vector<int>sequence(0);

	sequence = read_inputfile("input.txt");

	insertion_sort(sequence);

	make_outputfile(sequence);

	return 0;
}