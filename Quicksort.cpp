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

int partition(vector<int>& sequence, int p, int r)
{
	int i = p - 1;//record the place we put the value which is smaller than key,the values in the left side are which is smaller than key.
	int temp = 0;

	for (int j = p; j < r; j++)//check the values from left to right
	{
		if (sequence[j] <= sequence[r])//take s[r] as the key,if the value is smaller than key,move it to the left side of key.
		{
			i++;
			temp = sequence[j];
			sequence[j] = sequence[i];
			sequence[i] = temp;
		}
	}
	//place the key into the middle.
	temp = sequence[r];
	sequence[r] = sequence[i + 1];
	sequence[i + 1] = temp;
	//return the place of the key
	return i + 1;
}

void quick_sort(vector<int>& sequence, int p, int r) 
{
	if (p < r) {
		int q = partition(sequence, p, r);//classify and replace the numbers in sequence,then get the place of the key
		quick_sort(sequence, p, q - 1);//continue to solve the subsequence of smaller values
		quick_sort(sequence, q + 1, r);//continue to solve the subsequence of bigger values
	}
}

int main(int argc, char *argv[]) {

	vector<int>sequence(0);

	sequence = read_inputfile("input.txt");

	quick_sort(sequence,0,sequence.size()-1);

	make_outputfile(sequence);

	return 0;
}