#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
#include <regex>
#include <regex.h>
using namespace std;

vector<array<int, 2>> rule_sets;
vector<int> rules;

size_t idx(int x){
    for (size_t i = 0; i < rules.size(); i++)
        if (rules[i] == x)
            return i;
    return -1;
}

bool has(vector<int> v, int x){
    for(size_t i = 0; i < v.size(); i++)
         if (v[i] == x)
            return true;
    return false;
}

vector<int> find_rules(int x, bool greater, vector<int> r = {}){

    for(size_t i = 0; i < rule_sets.size(); i++){
        if (rule_sets[i][greater] != x)
            continue;

        int y = rule_sets[i][!greater];

        if (!has(r, y)){
            r.push_back(y);
            r = find_rules(y, greater, r);
            }
        }

    return r;
}


bool comp(int a, int b){
    if (has(find_rules(a, true), b))
        return false;
    return true;
}


bool is_ordered(vector<int> v) {

    vector<int> o = v;
    sort(o.begin(), o.end(), comp);

    for (size_t i = 0; i < v.size(); i++)
        if (v[i] != o[i])
            return false;

    return true;
}


bool is_invalid(int x, int y){
    for (size_t i = 0; i < rule_sets.size(); i++)
        if (rule_sets[i][0] == y && rule_sets[i][1] == x)
            return true;
    return false;
}

bool is_line_valid(vector<int> v){
    for (size_t i = 0; i < v.size(); i++){
        for (size_t j = 0; j < v.size(); j++){
            if (i < j && is_invalid(v[i], v[j]))
                return false;
            if (i > j && is_invalid(v[j], v[i]))
                return false;
        }
    }
    return true;
}


int main(){
	ifstream f("5.txt");
    
	if (!f.is_open()){
		cerr << "Error opening the file!";
		return 1;
	}
    
    vector<vector<int>> v;

    string s;
    while(getline(f, s)){
        
        if (s.length() > 1 && s[2] == '|'){
            array<int, 2> rule_set = {stoi(s.substr(0, 2)), stoi(s.substr(3, 2))};
            rule_sets.push_back(rule_set);

            if (!has(rules, rule_set[0]))
                rules.push_back(rule_set[0]);

            if (!has(rules, rule_set[1]))
                rules.push_back(rule_set[1]);
            }
        
        else if (s.size() > 2){
            vector<int> r;
            for (size_t i = 0; i < s.size(); i+=3)
                r.push_back(stoi(s.substr(i, 2)));
            v.push_back(r);
        }
    }

	f.close();

	size_t sum = 0;

    for (size_t i = 0; i < v.size(); i++){
        for (size_t j = 0; j < v[i].size(); j++)
            cout << v[i][j] << " ";

        if (!is_line_valid(v[i])){

            cout << "| " << "FALSE" << endl;  
            do{
                
                vector<int> initial_vector = vector(v[i]);
                sort(v[i].begin(), v[i].end(), is_invalid);
                for (size_t j = 0; j < v[i].size(); j++)
                    cout << v[i][j] << " ";
                
                if (v[i] == initial_vector){
                    cout << "BREAKING..." << endl;
                    break;
                cout << endl;
                }

                    
            } while (!is_line_valid(v[i]));
            int k = v[i].size()/2;
            cout << "\t ADDING => " << v[i][k] << endl;
            sum += v[i][k];
        }

              
    }

    cout << "\nCount: " << sum << "\n" << endl;

	return sum;
}