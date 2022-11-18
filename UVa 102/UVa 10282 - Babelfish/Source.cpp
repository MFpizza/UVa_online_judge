#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	map<string, string> m;
	string s = "1";
	while (getline(cin, s)) {
		if (s == "")
			break;
		string v;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == ' ') {
				for (int j = i+1; j < s.size(); j++) 
					v.push_back(s[j]);
				s.erase(s.begin() + i, s.end());
				break;
			}
		}
		m[v] = s;
	}
	while (cin >> s) {
		if (m.count(s) == 0)
			cout << "eh" << endl;
		else
			cout << m[s] << endl;
	}
}