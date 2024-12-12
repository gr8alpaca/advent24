#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
#include <regex>
#include <regex.h>
#include <map>
using namespace std;

map<size_t, size_t> mp;
vector<unsigned long long> v;

vector<size_t> keys(map<size_t, size_t> &m){
    vector<size_t> k;
    for (map<size_t, size_t>::iterator i = m.begin(); i != m.end(); ++i)
        k.push_back(i->first);
    return k;
}

vector<size_t> values(map<size_t, size_t> &m){
    vector<size_t> k;
    for (map<size_t, size_t>::iterator i = m.begin(); i != m.end(); ++i)
        k.push_back(i->second);
    return k;
}


void add(size_t key, size_t v, map<size_t, size_t> &m){
    (m.count(key) > 0) ? m[key] += v : m[key] = v;
    // for (map<size_t, size_t>::iterator i = m.begin(); i != m.end(); ++i){
    //     if ((i->first) == key){
    //         m[key] += v;
    //         return;
    //         }
    //     }
    // m[key] = v;
}




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
    for (map<size_t, size_t>::iterator i = mp.begin(); i != mp.end(); ++i)
        s += to_string(i->first) + ": " + to_string(i->second) + " | ";
    return s;
}

void split(size_t key, size_t qty, map<size_t, size_t> &m){
    string s = to_string(key);
    int digits = s.length();
    add(stoull(s.substr(0, digits / 2)), qty, m);
    add(stoull(s.substr(digits / 2, digits / 2)), qty, m);
}


void apply_blink(size_t key, size_t qty, map<size_t, size_t> &m){
    if (key == 0)
        return add(1, qty, m);
        
    if (int(floor(log10(key)) + 1) % 2 == 0)
        return split(key, qty, m);

    add(key * 2024, qty, m);
}

void blink(){
    map<size_t, size_t> n;
    for (map<size_t, size_t>::iterator i = mp.begin(); i != mp.end(); ++i){
        apply_blink(i->first, i->second, n);
    }
    mp = n;
}

int main(){
    ifstream f("11.txt");
    
	if (!f.is_open()){
		cerr << "Error opening the file!";
		return 1;
	}


    string s;
    while(getline(f, s, ' '))
        add(stoull(s), 1, mp);
    
    cout << str() << endl;
    const int LOOP_COUNT = 75;
    for (size_t i = 0; i < LOOP_COUNT; i++){
        cout << "\n - - - BLINK " << i << " - - - \n";
        blink();
    }

    save_log("log.txt", str());
    size_t sum = 0;
    for (size_t i : values(mp))
        sum += i;
    cout << "FINAL SUM => " << sum << endl;

    return 0;
}
