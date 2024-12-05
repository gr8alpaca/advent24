#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
#include <regex>
#include <regex.h>
using namespace std;


int count_word(vector<string> v, size_t i, size_t j, string word){

    if (v[i][j] != word[0])
        return 0;
    
    int c = 0;

    bool b[8] = {true, true, true, true, true, true, true, true};
    for (size_t k = 0; k < word.length(); k++){
        if (j+k < v[i].size()){

        }

        b[0] = b[0] && j+k < v[i].size() && v[i][j+k] == word[k];
        b[1] = b[1] && k <= j && v[i][j-k] == word[k];
        
        b[2] = b[2] && i+k < v.size() && v[i+k][j] == word[k];
        b[3] = b[3] && k <= i && v[i-k][j] == word[k];
        

        b[4] = b[4] && i+k < v.size() && j+k < v[i].size() && v[i+k][j+k] == word[k];
        b[5] = b[5] && k <= i && j+k < v[i].size() && v[i-k][j+k] == word[k];

        b[6] = b[6] && i+k < v.size() && k <= j && v[i+k][j-k] == word[k];
        b[7] = b[7] && k <= i && k <= j && v[i-k][j-k] == word[k];

    }

    for (int k = 0; k < 8; k++)
        c += b[k];
    
    return c;
}

bool xmas(vector<string> v, size_t i, size_t j){
    if (i==0 || i == v.size()-1 || j == 0 || j == v.size()-1 || v[i][j] != 'A')
        return false;
    string str = string({v[i+1][j+1], v[i+1][j-1], v[i-1][j-1], v[i-1][j+1]});
    return str == "SMMS" || str == "SSMM" || str == "MSSM" || str == "MMSS";
}


int main(){
    
	ifstream f("4.txt");
    
	if (!f.is_open()){
		cerr << "Error opening the file!";
		return 1;
	}

    vector<string> v;

    string s;
    while(getline(f, s)){
        v.push_back(s);
    }

	f.close();
    
	size_t sum = 0;

    for (size_t i = 0; i < v.size(); i++)
        for (size_t j = 0; j < v[i].size(); j++)
            sum += xmas(v, i, j);
        
    cout << "\nCount: " << sum << "\n" << endl;

	return sum;
}