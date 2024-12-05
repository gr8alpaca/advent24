#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;


bool is_safe(vector<int> v)
{
	int delta = 0;

	for (int i = 0; i < v.size() - 1 ; i++){
		int d = v[i+1] - v[i];

		if ((delta > 0 && d < 0) || (delta < 0 && d > 0) || abs(d) > 3 || d == 0)
			return false;
		
		delta += d;
	}

	return true;
}


bool tolerable(vector<int> vec, int tol){
	
	if (is_safe(vec))
		return true;
	if (tol == 0)
		return false;


	for (int i = 0; i < vec.size() && tol; i++){
		vector<int> v = vec;
		v.erase(v.begin() + i); // TODO

		if (tolerable(v, tol - 1))
			return true;
	}
	
	return false;
} 


int main(){

	ifstream f("2.txt");

	if (!f.is_open())
	{
		cerr << "Error opening the file!";
		return 1;
	}

	string s;
	int safe = 0;

	while (getline(f, s)){
		stringstream ss(s);
		string str;
		
		vector<int> v;
		while(ss >> str){ 			// TODO
			v.push_back(stoi(str));
			}

		safe += tolerable(v, 1);
	}

	cout << "SAFE => " << safe << endl;

	f.close();
	return 0;
}