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
	int i = p - 1;
	int temp = 0;

	for (int j = p; j < r; j++)
	{
		if (sequence[j] <= sequence[r])
		{
			i++;
			temp = sequence[j];
			sequence[j] = sequence[i];
			sequence[i] = temp;
		}
	}
	temp = sequence[r];
	sequence[r] = sequence[i + 1];
	sequence[i + 1] = temp;

	return i + 1;
}

void quick_sort(vector<int>& sequence, int p, int r, int k) 
{
	if (p < r) {
		int q = partition(sequence, p, r);
		if (q - p > k) 
		{
			quick_sort(sequence, p, q - 1, k);
		}
		if (r - q > k)
		{
			quick_sort(sequence, q + 1, r, k);
		}
	}
}

void insertion_sort(vector<int>& sequence)
{
	int x = 0;
	for (int i = 1; i < sequence.size(); i++)
	{
		x = sequence[i];
		int j = i - 1;
		for (; j >= 0 && sequence[j] > x; j--)
		{
			sequence[j + 1] = sequence[j];
		}
		sequence[j + 1] = x;
	}
}

void mix_sort(vector<int>& sequence, int p, int r, int k)
{
	quick_sort(sequence, p, r, k);
	insertion_sort(sequence);
}

int main(int argc, char *argv[]) {

	vector<int>sequence(0);

	sequence = read_inputfile("input.txt");

	mix_sort(sequence,0,sequence.size()-1, 10);

	make_outputfile(sequence);

	return 0;
}