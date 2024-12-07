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

vector<array<size_t, 2>> block_spots;

char prev_char = '^';

struct grid{
    vector<string> vs;

    string column(size_t x){
        string s = "";
        for (size_t i = 0; i < vs.size(); i++)
            s += vs[i][x];
        return s;
    }
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
    }
    inline size_t size(){
        return vs.size();
    }
    inline void push_back(string s){
        vs.push_back(s);
    }
    size_t max_loops(){
        return vs.size() * vs[0].size();
    }
    size_t count(){
        size_t c = 0;
        for (size_t i = 0; i < vs.size(); i++)
            for (size_t j = 0; j < vs[i].size(); j++)
                if (vs[i][j] == 'X')
                    c++;
        return c;
    }
    string str(){
        string s = " ";
        for (size_t i = 0; i < vs[0].size(); i++)
            s = s + " " + to_string(i);
        for (size_t i = 0; i < vs.size(); i++){
            s = s + "\n" + to_string(i) + " ";
            for (size_t j = 0; j < vs[i].size(); j++)
                s = s + vs[i][j] + " ";
            }
        s += "\n";
        return s;
    }
    void print(){
        cout << str();
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

bool is_loopable(){
    string row = v[y], col = v.column(x);
    
    array<size_t, 2> dir = {(v[y][x] == '^') - (v[y][x] == 'v'), (v[y][x] == '>') - (v[y][x] == '<')}, pos = {x, y};

    if(v[y][x] == '^'){

    }
    return false;
}



bool update_target(bool f = true){
    if (v[y][x] != '^' && v[y][x] != '>' && v[y][x] != 'v' && v[y][x] != '<'){
        cout << "Character is not cursor -> \"" << v[y][x] << "\"\n"; 
        return false;
        }

    // size_t bx, by;

    if (v[y][x] == '^'){
        tx = x;
        ty = y - 1;
        if (!v.in_bounds(tx, ty))
            return false;
        if (!is_target_valid())
            v.set(x, y, '>');
    }

    if (v[y][x] == '>'){
        tx = x + 1;
        ty = y;
        if (!v.in_bounds(tx, ty))
            return false;
        if (!is_target_valid())
            v.set(x, y, 'v');
    }
    
    if (v[y][x] == 'v'){
        tx = x;
        ty = y + 1;
        if (!v.in_bounds(tx, ty))
            return false;
        if (!is_target_valid())
            v.set(x, y, '<');
    }

    if (v[y][x] == '<'){
        if (x == 0)
            return false;
        tx = x - 1;
        ty = y;
        if (!v.in_bounds(tx, ty))
            return false;
    }

    if (!is_target_valid() && f){
            v.set(x, y, '^');
            return update_target(false);
    }
    
    if (v[ty][tx] == 'X'){
        size_t ux = tx + (tx - x), uy = ty + (ty - y);
        if (v.in_bounds(ux, uy)){
            block_spots.push_back({ux, uy});
        }
    }

    return true;
}

void move(){
    v.set(tx, ty, v[y][x]);
    v.set(x, y, (prev_char != v[y][x]) ? '+':'X');
    x = tx;
    y = ty;
    prev_char = v[y][x];
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

    size_t max_loops = v.max_loops()*2;
    size_t i = 0;
    while (i < max_loops && update_target()){
        move();
        i++;
    }
    
    v.set(x, y, 'X');
    size_t sum = v.count();
    cout << "UNIQUE POSTIONS: " << sum << "\tLoops: " << i << endl;
    cout << "BLOCK SPOTS: " << block_spots.size() << endl;

    for (size_t i = 0; i < block_spots.size(); i++)
        v.set(block_spots[i][0], block_spots[i][1], '0');

    ofstream of("log.txt");
    of << v.str();
    of.close();

    return sum;
}
