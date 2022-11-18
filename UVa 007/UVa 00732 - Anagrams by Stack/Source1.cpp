#include <iostream>
#include <vector>
#include <stack>
using namespace std;
string a, b;
vector<bool> ans;
stack<char> s;

void dfs(int x, int y) {
	if (x == a.size() && y == b.size()) {
		cout << (ans[0] ? 'i' : 'o');
		for (int i = 1; i < ans.size(); i++) {
			cout << ' ' << (ans[i] ? 'i' : 'o');
		}
		cout << endl;
		return;
	}
	if (x < a.size()) {
		ans.push_back(1);
		s.push(a[x]);
		dfs(x + 1, y);
		s.pop();
		ans.pop_back();
	}
	if (!s.empty() && s.top() == b[y]) {
		ans.push_back(0);
		char ch = s.top();
		s.pop();
		dfs(x, y + 1);
		s.push(ch);
		ans.pop_back();
	}
}

int main() {
	while (cin >> a >> b) {
		ans.clear();
		cout << "[\n";
		if (a.size() == b.size())
			dfs(0, 0);
		cout << "]\n";
	}
}