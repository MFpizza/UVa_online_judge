#include <list>
#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	while (getline(cin, s)) {
		list<char> List;
		list<char>::iterator it = List.begin();
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '[')
				it = List.begin();
			else if (s[i] == ']')
				it = List.end();
			else
				List.insert(it, s[i]);
		}
		for (it = List.begin(); it != List.end(); ++it)
			cout << *it;
		cout << endl;
	}
}
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3139