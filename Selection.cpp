#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

int read_inputfile(string filename, vector<int>& container) // input the name of the input file and container, output the n-th smallest number you want to find.
{
	fstream file;

	file.open(filename, ios::in);

	string temp;

	if (getline(file, temp))
	{

		container.resize(stoi(temp));

		int num = 0;

		if (getline(file, temp)) {
			num = stoi(temp);
			if (num > container.size()) {
				num = container.size();
				cout << "n-th is too big!";
			}
		}

		for (int i = 0; i < container.size(); i++)
		{
			if (getline(file, temp))
			{
				container[i] = stoi(temp);
			}
			else
			{
				cout << "Not enough numbers in the file.";
				break;
			}
		}
		cout << "Read " << container.size() << " numbers in " << filename << ".";
		file.close();
		return num;
	}
	else
	{
		cout << "Nothing in the file.";
		file.close();
		return 0;
	}
}

void make_outputfile(int size, int num, int result) // make a random sequence whose size is num
{
	fstream file;

	file.open("output.txt", ios::out | ios::trunc);

	file << size << endl << num << endl << result;

	file.close();

}

struct medium_item { // record the value and the index of the item
	int num;
	int index;
	medium_item(int num = 0, int index = 0) {
		this->num = num;
		this->index = index;
	}
};

int insertion_sort(vector<int>& sequence, vector<int> index) //do insertionsort and return the index of the medium.
{
	vector<medium_item>item_sequence(0);
	for (int i = 0; i < index.size(); i++)
	{
		item_sequence.push_back(medium_item(sequence[index[i]], index[i]));
	}
	int x = 0;
	for (int i = 1; i < item_sequence.size(); i++)
	{
		x = item_sequence[i].num;//store the value the key
		int j = i - 1;//compare from the left and first one of the key 
		for (; j >= 0 && item_sequence[j].num > x; j--)//compare one by one until someone is smaller than the key
		{
			item_sequence[j + 1] = item_sequence[j];
		}
		item_sequence[j + 1] = item_sequence[i];//place the key into the place we find
	}
	return item_sequence[item_sequence.size()/2].index;
}

int find_medium(vector<int>& sequence, vector<int> index) { // find the medium of the sequence, and return its index.
	if (index.size() <= 5) { // if num of item <= 5 solve it by insertionsort.
		return insertion_sort(sequence, index);
	}
	else { // else: divide it,and collect the partial answer.
		vector<int>partial_medium_index_list(0);

		int i = index.size();
		while (i > 0) // divide it to the groups of <=5 items.
		{
			vector<int>subsequence(0);
			for (int j = 0; j < 5 && i > 0; j++)
			{
				subsequence.push_back(index[index.size()-(i--)]);
			}
			partial_medium_index_list.push_back(insertion_sort(sequence, subsequence));
		}
		return find_medium(sequence, partial_medium_index_list);
	}
}

int partition(vector<int>& sequence, int p, int r)//find the medium which should be the key, and then do partition.
{
	vector<int>partial_index_list(0); // the vector that store the indices which we want find their medium.
	for (int i = p; i <= r; i++)
	{
		partial_index_list.push_back(i);
	}

	int medium = find_medium(sequence, partial_index_list); // find the index of partial medium(key).

	int i = p;//record the place we put the value which is smaller than key,the values in the left side are which is smaller than key.
	int temp = 0;

	//swap the medium to the last place.
	temp = sequence[r];
	sequence[r] = sequence[medium];
	sequence[medium] = temp;

	for (int j = p; j < r && i < r; j++)//check the values from left to right
	{
		if (sequence[j] <= sequence[r])//take s[r] as the key,if the value is smaller than key,move it to the left side of key.
		{
			temp = sequence[j];
			sequence[j] = sequence[i];
			sequence[i] = temp;
			i++;
		}
	}
	//place the key into the middle.
	temp = sequence[r];
	sequence[r] = sequence[i];
	sequence[i] = temp;
	//return the place of the key
	return i;
}

int select(vector<int>& sequence, int p, int r, int i)
{
	if (p == r) {// the only one last is the answer 
		return sequence[p];
	}

	int q = partition(sequence, p, r); // find the index of pivot value (partial medium).

	int k = q - p + 1;
	if (i == k) { // the pivot value is the answer 
		return sequence[q];
	}
	else if (i < k) { // the pivot value is bigger than the answer 
		return select(sequence, p, q-1, i);
	}
	else { // the pivot value is smaller than the answer 
		return select(sequence, q+1, r, i-k);
	}
}

int main(int argc, char* argv[]) {

	vector<int>container(0);

	int num = read_inputfile("input.txt",container);

	int result = select(container, 0, container.size() - 1, num);

	make_outputfile(container.size(), num, result);

	return 0;
}