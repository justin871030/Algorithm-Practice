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

void merge(vector<int>& sequence, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	vector<int>L(sequence.begin() + p, sequence.begin() + q + 1);
	vector<int>R(sequence.begin() + q + 1, sequence.begin() + r + 1);

	int i = 0;
	int j = 0;

	for (int k = p; k <= r; k++)
	{
		if (i >= n1)
		{
			sequence[k] = R[j++];
		}
		else if (j >= n2)
		{
			sequence[k] = L[i++];
		}
		else
		{
			if (L[i] <= R[j])
			{
				sequence[k] = L[i++];
			}
			else
			{
				sequence[k] = R[j++];
			}
		}
	}
}

void merge_sort(vector<int>& sequence, int p, int r) 
{
	if (p < r) {
		int q = (p + r) / 2;
		merge_sort(sequence, p, q);
		merge_sort(sequence, q + 1, r);
		merge(sequence, p, q, r);
	}
}

int main(int argc, char *argv[]) {

	vector<int>sequence(0);

	sequence = read_inputfile("input.txt");

	merge_sort(sequence,0,sequence.size()-1);

	make_outputfile(sequence);

	return 0;
}