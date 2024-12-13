#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
#include <regex>
#include <regex.h>
#include <map>
#include <cassert>
#include "vec2.h"
using namespace std;

struct claw{
    vec2<int64_t> a;
    vec2<int64_t> b;
    vec2<int64_t> prize;
    vector<vec2<int64_t>> solutions;

    // Lowest-cost solution Index
    int idx;
    
    int64_t cost = 0;
    claw(vec2<int64_t> i, vec2<int64_t> j, vec2<int64_t> p){a = i; b = j;prize = p;}
    inline string str(){return "A: " + a.str() + " | B: " + b.str() + " | Prize: " + prize.str();}
};

template<size_t I, size_t J>
struct matrix{
    int64_t m[I][J];
    // int64_t m[2][3] = {{0,0,0},{0,0,0}};

    matrix (int64_t width) : m(){}


    matrix(array<array<int64_t, J>, I> a){
        for (size_t i = 0; i < I; i++)
            for (size_t j = 0; j < J; j++)
                m[i][j] = a[i][j];
    }

    

    matrix(claw &c){
        m[0][0] = c.a.x;
        m[0][1] = c.a.y;
        m[0][2] = c.prize.x;
        m[1][0] = c.b.x;
        m[1][1] = c.b.y;
        m[1][2] = c.prize.y;
    }

    matrix(){
        for (size_t i = 0; i < I; i++)
            for (size_t j = 0; j < J; j++)
                m[i][j] = 0;
    }

    string str(){
        string s = "";
        for (int i = 0; i < 2; i++){
            s+= "\n| ";
            for (int j = 0; j < 3; j++)
                s+= to_string(m[i][j]) + " ";
            s+= " |";
        }
        return s;
    }

    inline void operator=(array<array<int64_t, J>, I> a){
        for (size_t i = 0; i < I; i++)
            for (size_t j = 0; j < J; j++)
                m[i][j] = a[i][j];
    }

};


string printv(vector<claw> v){
    string s = "";
    for (size_t i =0; i < v.size(); i++)
        s += v[i].str() + "\n";
    return s;
}


vec2<int64_t> parse_ln(string s){
    return vec2<int64_t>(stoi(s.substr(s.find_first_of('X')+2, s.find_first_of(',') - s.find_first_of('X')+2)), stoi(s.substr(s.find_last_of('Y') + 2)));
}

const int64_t COST_A = 3;
const int64_t COST_B = 1;

int64_t cost(int64_t a, int64_t b){return a * COST_A + b * COST_B;}
int64_t cost(vec2<int64_t> v){return cost(v.x, v.y);}


// PART 1 SOLUTION => 25751
void find_solutions(claw &c){
    const int64_t max_a_presses = min(c.prize.x/ c.a.x, c.prize.y/c.a.y) + 1;
    const int64_t max_b_presses = min(c.prize.x/ c.b.x, c.prize.y/c.b.y) + 1;

    for (int64_t a_press = 0; a_press < max_a_presses; a_press++){

        for (int64_t b_press = 0; b_press < max_b_presses; b_press++){

            vec2<int64_t> claw_position(c.a.x * a_press + c.b.x * b_press, c.a.y * a_press + c.b.y * b_press);
            // if (claw_position.x > c.prize.x || claw_position.y > c.prize.y)
            //     break;
            if (claw_position == c.prize) 
                c.solutions.push_back(vec2<int64_t>(a_press, b_press));
            
        }
    }
    // cout << c.str() + "\tSOLTIONS =>";
    // for (size_t i = 0; i < c.solutions.size(); i++)
    //     cout << " " + c.solutions[i].str();
    // cout << endl;
}

void select_solution(claw &c){
    c.idx = 0;
    for (size_t i = 1; i < c.solutions.size(); i++)
        if (cost(c.solutions[i]) < cost(c.solutions[c.idx]))
            c.idx = i;
    c.cost = c.solutions[c.idx].x * COST_A + c.solutions[c.idx].y * COST_B;
    cout << c.str() + " | SOLUTION: " + c.solutions[c.idx].str() + " COST: " << c.cost << endl;
}

int main(){

    ifstream f("test.txt");
    
	if (!f.is_open()){
		cerr << "Error opening the file!";
		return 1;
	}


    string s;
    vector<string> lines;
    vector<claw> c;
    while(getline(f, s))
        lines.push_back(s);

    for (size_t i = 0; i < lines.size(); i+=4)
        c.push_back(claw(parse_ln(lines[i]), parse_ln(lines[i+1]), parse_ln(lines[i+2])));
    

    // size_t sum = 0;
    for (claw cl : c){
        // matrix m(cl);
        // cout << m.str() << endl;
        

        // find_solutions(cl);
        // if (cl.solutions.size() > 0)
        //     select_solution(cl);
        // sum += size_t(cl.cost);
        }
    // matrix<5, 1> mats({{1},{1},{1},{1},{1}}); 


    // cout << "\nGRAND TOTAL => " << sum << mats.str() << endl;
    
    return 0;
}
