#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
#include <regex>
#include <regex.h>
using namespace std;

const char OOB = '0';

size_t x = 0;
size_t y = 0;

size_t tx = 0;
size_t ty = 0;

struct grid{
    vector<string> vs;
    bool in_bounds(size_t i, size_t j){
        return (j < vs.size() && i < vs[j].size());
    }
    char at(size_t x, size_t y){
        return vs[y][x];
    }
    void set(size_t x, size_t y, char c){
        if (y < vs.size() && x < vs[y].size())
            vs[y][x] = c;
        else
            cout << "ERROR: CANNOT SET VALUE \"" + to_string(c) + "\" at (" << to_string(x) << ", " << to_string(y) << ")" << endl; 
    }
    inline char operator[](array<size_t, 2> idx){
        if (idx[1] < vs.size() && idx[0] < vs[idx[1]].size())
            return vs[idx[1]][idx[0]];
        else
            return OOB;
    }
    inline string operator[](size_t i){
        if (i < vs.size())
            return vs[i];
        return string(vs[0].size(), '#');
        // string s = "";
        // s.assign(vs[0], '#');
        // return s;
    }
    inline size_t size(){
        return vs.size();
    }
    inline void push_back(string s){
        vs.push_back(s);
    }
    size_t count(){
        size_t c = 0;
        for (size_t i = 0; i < vs.size(); i++)
            for (size_t j = 0; j < vs[i].size(); j++)
                if (vs[i][j] == 'X')
                    c++;
        return c;
    }
    void print(){
        cout << " ";
        for (size_t i = 0; i < vs[0].size(); i++)
            cout << " " << i;
        for (size_t i = 0; i < vs.size(); i++){
            cout << "\n" << i << " ";
            for (size_t j = 0; j < vs[i].size(); j++)
                cout << vs[i][j] << " ";
            }
        cout << "\n";
    }
} v;

char ch(size_t i, size_t j){
    return v[j][i];
}

void print_pos(){
    cout << "(" << x << ", " << y << ")" << endl;
}

void find_guard(){
    for(size_t i = 0; i < v.size(); i++)
        for(size_t j = 0; j < v[i].size(); j++)
            if (v[i][j] == '^' || v[i][j] == 'v' || v[i][j] == '>' || v[i][j] == '<'){
                x = j;
                y = i;
            }
}

bool is_target_valid(){
    return v[ty][tx] != '#';
}

bool update_target(bool f = true){
    if (v[y][x] != '^' && v[y][x] != '>' && v[y][x] != 'v' && v[y][x] != '<'){
        cout << "Character is not cursor -> \"" << v[y][x] << "\"\n"; 
        return false;
        }

    if (v[y][x] == '^'){
        tx = x;
        ty = y - 1;
        if (!is_target_valid())
            v[y][x] = '>';
    }

    if (v[y][x] == '>'){
        tx = x + 1;
        ty = y;
        if (!is_target_valid())
            v[y][x] = 'v';
    }
    
    if (v[y][x] == 'v'){
        tx = x;
        ty = y + 1;
        if (!is_target_valid())
            v[y][x] = '<';
    }

    if (v[y][x] == '<'){
        tx = x - 1;
        ty = y;
    }

    if (!is_target_valid() && f){
            v[y][x] = '^';
            return update_target(false);
    }
    
    return true;
}

void move(){
    // v.print();
    // cout << "MOVING << (" << x << ", " << y << ") => " << "(" << tx << ", " << ty << ")" << endl;

    v.set(tx, ty, v[y][x]);
    v.set(x, y, 'X');
    x = tx;
    y = ty;

    // cout << "__NEW GRID__" << endl;
    // v.print();
}


int main(){
	ifstream f("test.txt");
    
	if (!f.is_open()){
		cerr << "Error opening the file!";
		return 1;
	}
    
    string s;
    while(getline(f, s)){
        v.push_back(s);
    }
    
	f.close();

    find_guard();
    print_pos();
    while (update_target()){
        move();
    }
    v.print();
    // v.set(x, y, 'X');
    size_t sum = v.count();
    cout << "UNIQUE POSTIONS: " << sum << endl;;
	return sum;
}
