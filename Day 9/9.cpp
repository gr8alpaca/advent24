#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
#include <regex>
#include <regex.h>
using namespace std;

const int EMPTY = -1;

struct mem{
    vector<int> a;

    inline int operator[](int i){
        return a[i];
    }

    inline void push_back(int i){
        a.push_back(i);
    }

    inline size_t size(){
        return a.size();
    }

    inline string str(){
        string s = "";
        for (size_t i = 0; i < a.size(); i++)
            s += ((a[i] != EMPTY) ? to_string(a[i]):".") + "|";
        return s;
    }

    inline void swap(int i, int j){
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    inline int find(int e){
        for (int i = 0; i < int(a.size()); i++)
            if (a[i] == e)
                return i;
        return -1;
    }

    inline int rfind(int e){
        for (int i = a.size() - 1; 0 <= i; i--)
            if (a[i] == e)
                return i;
        return -1;
    }

    inline int rfind_v(){
        for (int i = a.size() - 1; 0 <= i; i--)
            if (a[i] != EMPTY)
                return i;
        return -1;
    }

    inline int block_size(int i){
        int k = 0;
        while(i + k < int(a.size()) && a[i + k] == a[i])
            k++;
        return k;
    }

    inline int rbsize(int i){
        int s = 1;
        while(0 < (i-s) && a[i-s] == a[i])
            s++;
        return s;
    }

    inline void swap_block(int i, int j, int s){
        string b1 = "";
        string b2 = "";
        for (int k = 0; k < s; k++){
            b1 += to_string(a[i+k]);
            b2 += to_string(a[j+k]);
        }

        cout << "BLOCKSWAP " << b1 << " <-> " << b2 << " @ " << i << " & " << j-s+1  << " SIZE: " << s << endl;
        for (int k = 0; k < s; k++)
            swap(i + k, j + k);
        }

    inline int find_empty_block(int s){
        for (int i = 0; i < int(a.size()); i++){
            bool is_size = true;
            for(int j = 0; j < s; j++){
                if (a[i + j] != EMPTY)
                    is_size = false;

                }
                if (is_size)
                    return i;
            }
        return -1;
    }



    inline bool find_empty_index(int &i){
        i = find(EMPTY);
        if (i == rfind(EMPTY)){
            i = -1;
            return false;
        }
        return true;
    }

    inline size_t checksum(){
        size_t s = 0;
        for (size_t i = 0; i < a.size(); i++)
            s += (a[i] == EMPTY) ? 0:(i * size_t(a[i]));
        return s;
    }


} v;

void save_log(string path, string txt){
    ofstream of(path);
    of << txt;
    of.close();
}


int ctoi(char c){
    return int(c - '0');
}


int main(){
    ifstream f("9.txt");
    
	if (!f.is_open()){
		cerr << "Error opening the file!";
		return 1;
	}

    int id = 0;
    bool is_free = false;
    char c;

    while(f.get(c)){
        for(int i = 0; i < ctoi(c); i++ )
            v.push_back((is_free) ? EMPTY:id);
        id+= is_free;
        is_free = !is_free;
    }
    

	f.close();

    int i = v.size();
    while (0 < i){
        i--;

        if (v[i] == EMPTY)
            continue;

        int s = v.rbsize(i);
        i = i-s+1;
        int idx = v.find_empty_block(s);
        if (0 <= idx && idx < i)
            v.swap_block(idx, i, s);

    }
    



    save_log("log.txt", v.str());
    

    cout << "CHECKSUM => " << v.checksum() << endl;


    return 0;
}
