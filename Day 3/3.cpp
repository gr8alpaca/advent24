#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
#include <regex>
#include <regex.h>
using namespace std;


int main(){

	ifstream f("3.txt");

	if (!f.is_open())
	{
		cerr << "Error opening the file!";
		return 1;
	}

    string s;
    getline(f, s, '\0');
    // s.c_str

	size_t sum = 0;

    regex expr ("mul\\s{0,1}\\((\\d{1,3}),(\\d{1,3})\\)");
    regex inv (".+(?:don't\\(\\).+do\\(\\))");

    string vs = regex_replace(s, inv, "$&");
    // while(regex_match(vs, inv)){
    //     cout << "REMOVING SEGMENT..." << endl;
    //     vs = regex_replace(s, inv, "");
    // }

    for(
        sregex_iterator i = sregex_iterator(vs.begin(), vs.end(), expr);
        i != sregex_iterator(); 
        ++i)
    {
        smatch m = *i;

        int pos = i->position();

        int dont = s.rfind("don't()", pos);
        int d = s.rfind("do()", pos);

        if (d >= 0 && dont >= 0 ){
            cout << dont << " (dont) <= " << d << " (do)" << " => " << (dont <= d ?"TRUE":"FALSE");
            cout << " | DONT: " << s.substr(dont, 7) << " DO: " << s.substr(d, 4) << " (do)" << endl;
        }

        if (dont <= d)
            sum += stoi(m[1]) * stoi(m[2]);
    }

    cout << "SIZE: " << s.size()<< " => " << vs.size() << endl;
    cout << "SUM => " << sum << endl;
    // smatch m;

    // regex_search(text, match, pattern)




	f.close();
	return sum;
}