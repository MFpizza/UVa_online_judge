#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ofstream out("out.txt");
	string s;
	int count = 1;
	while (cin >> s) {
		if (s == "end")
			break;
		vector<stack<char>> vec;
		for (int i = 0; i < s.size(); i++) {
			char ch = s[i];
			bool newStac = true;
			for (int j = 0; j < vec.size(); j++) {
				char compare = vec[j].top();
				if (ch < compare || ch == compare) {
					vec[j].push(ch);
					newStac = false;
					break;
				}
			}
			if (newStac)
			{
				stack<char> stac;
				stac.push(ch);
				vec.push_back(stac);
			}
		}
		cout << "Case " << count++ << ": " << vec.size() << endl;
	}
}