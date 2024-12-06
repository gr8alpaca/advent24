#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

bool comp(int a, int b){
	return a < b;
}

int count(vector<int> v, int e){
	int c = 0;
	for (int i = 0; i < v.size(); i++)
		if(v[i]== e)
			c++;
	return c;
}


int main()
{
	ifstream f("locations.txt");

	if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

	string s;
	vector<int> alpha;
	vector<int> beta;
	
	while (getline(f, s)){
		alpha.push_back(stoi(s.substr(0, 5)));
		beta.push_back(stoi(s.substr(8, 5)));
	}

	sort(alpha.begin(), alpha.end(), comp); 
	sort(beta.begin(), beta.end(), comp);
	
	int size_a = alpha.size();
	int size_b = beta.size();

	// cout << "ALPHA: " << alpha.size() << endl;
	// cout << "MIN: " << alpha[0] << " MAX: " << alpha[size_a -1] << endl;
	// cout << "- - - - - -" << endl;
	// cout << "BETA: " << beta.size() << endl;
	// cout << "MIN: " << beta[0] << " MAX: " << beta[size_a -1] << endl;

	int delta = 0;
	for (int i = 0; i < size_a; i++){
		delta += abs(alpha[i] - beta[i]);
	}

	cout << "FINAL DELTA: " << delta << endl;

	int similarity = 0;
	for (int i = 0; i < size_a; i++){
		similarity += alpha[i] * count(beta, alpha[i]);
	}

	cout << "FINAL SIMILARITY: " << similarity << endl;

	f.close();
	return 0;
}
