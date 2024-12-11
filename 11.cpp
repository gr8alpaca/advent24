#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
#include <regex>
#include <regex.h>
using namespace std;


vector<unsigned long long> v;

int ctoi(char c){
    return int(c - '0');
}

void save_log(string path, string txt){
    ofstream of(path);
    of << txt;
    of.close();
}

string str(){
    string s = "";
    for (size_t i = 0; i < v.size(); i++)
        s += to_string(v[i]) + " ";
    return s;
}

void split(size_t i){
    string s = to_string(v[i]);
    int digits = s.length(); 
    v[i] = stoull(s.substr(0, digits/2));
    v.push_back(stoull(s.substr(digits/2, digits/2)));
}


void apply_blink(size_t i){
    if (v[i] == 0){
        v[i] = 1;
        return;
        }
    
    if (int(floor(log10(v[i])) + 1) % 2 == 0){
        split(i);
        return;
        }

    v[i] = v[i] * 2024;

}

void blink(){
    size_t size = v.size();
    for (size_t i = 0; i < size; i++)
        apply_blink(i);
}

int main(){
    ifstream f("11.txt");
    
	if (!f.is_open()){
		cerr << "Error opening the file!";
		return 1;
	}


    string s;
    while(getline(f, s, ' ')){
        v.push_back(stoull(s));
    }
    cout << str() << endl;

    const size_t BLINK_AMOUNT = 75; 
    for (size_t i = 0; i < BLINK_AMOUNT; i++){
        blink();
        cout << "\nBLINK #" << i << endl;//"\n\t"<< str() << endl;
    }


    cout << "SCORE => " << v.size() << endl;

    return 0;
}
