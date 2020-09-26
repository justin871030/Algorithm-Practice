#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

int read_inputfile(string filename, vector<int>& v, vector<int>& w) // read the input file
{
	fstream file;

	file.open(filename, ios::in);

	string temp;
	int bag_size = 0;
	int max_load = 0;

	if (getline(file, temp))//read bag size
	{
		bag_size = stoi(temp);

		if (getline(file, temp))//read max load
		{
			max_load = stoi(temp);
		}
		else {
			cout << "Not get the max load number." << endl;
		}

		for (int i = 0; i < bag_size; i++)//read objects
		{
			if (getline(file, temp))
			{
				string v_str;
				string w_str;
				for (int j = 0; j < temp.size(); j++)
				{
					v_str.push_back(temp[j]);
					if (temp[j] == ' ') {
						for (; j < temp.size(); j++)
						{
							w_str.push_back(temp[j]);
						}
					}
				}
				v.push_back(stoi(v_str));
				w.push_back(stoi(w_str));
			}
			else
			{
				cout << "Not enough objects in the file." << endl;
				break;
			}
		}
		cout << "Read " << v.size() << " objects in " << filename << "." << endl;
		file.close();
	}
	else
	{
		cout << "Nothing in the file." << endl;
		file.close();
	}
	return max_load;
}

void make_outputfile(int maximum, vector<int>& result) // make a output file
{
	fstream file;

	file.open("output.txt", ios::out | ios::trunc);

	file << "Total revenue = " << maximum << endl;
	file << "Selected item : ";

	for (int i = result.size()-1; i >= 0; i--)//put the result
	{
		file << result[i];
		if (i != 0) {
			file << " ";
		}
	}
	file.close();
}

vector<int> knapsack(vector<int>& v, vector<int>& w, int max_load, vector<int>& c, vector<vector<bool>>& p)//return the result
{
	vector<int>result(0);
	for (int i = 0; i < v.size(); ++i)//check all the object
		for (int j = max_load; j >= w[i]; --j)//
			if (c[j - w[i]] + v[i] > c[j])//if put the object is better
			{
				c[j] = c[j - w[i]] + v[i];//record the solution
				p[i][j] = true; // record put
			}

	cout << "maximal value is " << c[max_load] << endl;//print result

	for (int i = v.size() - 1, j = max_load; i >= 0; --i)//print selected object
		if (p[i][j])    // true if in the bag
		{
			cout << i + 1 << " ";
			j -= w[i];
			result.push_back(i + 1);//store result
		}
	cout << "in the bag";//print result
	return result;
}

int main(int argc, char* argv[]) {

	vector<int>v(0);//vector to record value
	vector<int>w(0);//vector to record weight
	vector<int>result(0);//vector to record result

	int max_load = read_inputfile("input.txt", v, w);//read file
	vector<int>c(max_load + 1);//count the local optimal solution.
	vector<vector<bool>>p(v.size(), vector<bool>(max_load + 1, false));//record put or dont put
	for (int i = 0; i < v.size(); i++)//print input data
	{
		cout << "V:" << v[i] << " " << "W:" << w[i] << endl;
	}
	result = knapsack(v, w, max_load, c, p);
	make_outputfile(c[max_load], result);

	return 0;
}