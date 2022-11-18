#include <iostream>
#include <stack>
#include <vector>
using namespace std;
string a, b;
vector<bool> v;
stack<char> s;
void dfs(int x, int y) {
	if (x == a.size() && y == b.size()) {
		cout << (v[0] ? 'i' : 'o');
		for (int i = 1; i < v.size(); ++i) {
			cout << ' ' << (v[i] ? 'i' : 'o');
		}
		cout << endl;
		return;
	}
	// push
	if (x < a.size()) {
		v.push_back(1);
		s.push(a[x]);
		dfs(x + 1, y);
		v.pop_back();
		s.pop();
	}
	// pop if possible
	if (!s.empty() && s.top() == b[y]) {
		v.push_back(0);
		char c = s.top();
		s.pop();
		dfs(x, y + 1);
		s.push(c);
		v.pop_back();
	}
}

int main() {
	while (cin >> a >> b)
	{
		v.clear();
		cout << "[" << endl;
		string c = a, d = b;
		if (a.size() == b.size()) 
			dfs(0, 0);
		cout << "]" << endl;
	}
}