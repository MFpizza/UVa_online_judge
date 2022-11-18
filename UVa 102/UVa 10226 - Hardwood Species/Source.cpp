#include <iostream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

int main() {
	int count;
	cin >> count;
	string s;
	getline(cin, s);
	getline(cin, s);
	while (count--) {
		map<string, int> tree;
		int treeCount = 0;
		while (getline(cin, s)) {
			if (s == "")
				break;
			tree[s]++;
			treeCount++;
		}
		for (map<string, int>::iterator it = tree.begin(); it != tree.end(); it++)
			cout << it->first << " " << fixed << setprecision(4) << (double)(it->second) / treeCount * 100 << endl;
		if (count) cout << endl;
	}
}