#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
#include <regex>
#include <regex.h>
using namespace std;


int ctoi(char c){
    return int(c - '0');
}

struct vec2{
    int x = 0;
    int y = 0;

    vec2(){}
    
    vec2(array<int, 2> a){
        x = a[0]; y = a[1];
    }
    
    vec2(int input_x, int input_y){
        x = input_x; y = input_y;
    }

    inline int& operator[](int y){
        return (y == 0) ? x:y;
    }
    inline vec2 operator+(vec2 vec){
        return vec2(vec.x + x, vec.y + y);
    }
    inline bool operator==(vec2 vec){
        return vec.x == x && vec.y == y;
    }
};

struct map{
    vector<vector<int>> a;

    inline vector<int>& operator[](int y){
        return a[y];
    }
    inline int& operator[](vec2 vec){
        return a[vec.y][vec.x];
    }

    inline void push_back(vector<int> i){
        a.push_back(i);
    }

    inline size_t size(){
        return a.size();
    }
    inline bool in_bounds(vec2 vec){
        return vec.y < int(a.size()) && vec.x < int(a[vec.y].size());
    }
    inline string str(){
        string s = "";
        for (size_t i = 0; i < a.size(); i++){
            for (size_t j = 0; j < a[i].size(); j++)
                s += to_string(a[i][j]) + " ";
            s += "\n";    
            }
        return s;
    }

} v;



void save_log(string path, string txt){
    ofstream of(path);
    of << txt;
    of.close();
}

void unique(vector<vec2> &vec){
    for (size_t i = 0; i < vec.size(); i++)
        for (size_t j = 0; j < vec.size(); i++)
            if (i < j && vec[i] == vec[j])
                vec.erase(vec.begin() + j);
}

void paths(vec2 coord, vector<vec2> &vec){
    if (v[coord] == 9){
        bool is_unique = true;
        // for (size_t i = 0; i < vec.size(); i++)
        //     if (vec[i] == coord)
        //         is_unique = false;
        
        if (is_unique)
            vec.push_back(coord);
        return;
        }

    const vec2 DIRECTIONS[4] = {vec2(1, 0), vec2(0, 1), vec2(-1, 0), vec2(0, -1)};

    for (int i = 0; i < 4; i++){
        vec2 pt = coord + DIRECTIONS[i];
        if (v.in_bounds(pt) && v[pt] - v[coord] == 1)
            paths(coord + DIRECTIONS[i], vec);
    }
}


int score(){
    int s = 0;
    for (int y = 0; y < int(v.size()); y++)
        for (int x = 0; x < int(v[y].size()); x++){
            
            vector<vec2> path_ends;
            vec2 coord = vec2(x, y);
            if (v[coord] == 0)
                paths(coord, path_ends);
            cout << "COORD => " << x << ", " << y << " | COUNT => " << path_ends.size() << endl;
            s += path_ends.size();
        }
    return s;
}


int main(){
    ifstream f("10.txt");
    
	if (!f.is_open()){
		cerr << "Error opening the file!";
		return 1;
	}

    string s;
    while(getline(f, s)){
        vector<int> row;
        for (size_t i = 0; i < s.length(); i++)
            row.push_back(ctoi(s[i]));
        v.push_back(row);
    }

    cout << v.str() << endl;

    int sum = score();
    
    cout << "SCORE => " << sum << endl;

    return 0;
}
