#include<algorithm>
#include<cstdio>
#include<iostream>
#include<map>
#include<sstream>
#include<vector>
using namespace std;

vector<char> elements;
vector<vector<char> > adj;
map<char, bool> vis;
bool ans;

bool valid(char e) {
	for (int i = 0; i < adj[e].size(); i++)
		if (vis[adj[e][i]])
			return false;
	return true;
}

void dfs(string path) {
	if (path.length() == elements.size()) {
		ans = true;
		cout << path[0];
		for (int i = 1; i < path.size(); i++)
			cout << ' ' << path[i];
		printf("\n");
		return;
	}

	for (int i = 0; i < elements.size(); i++) {
		if (!vis[elements[i]]) {
			if (valid(elements[i])) {
				vis[elements[i]] = true;
				dfs(path + elements[i]);
				vis[elements[i]] = false;
			}
		}
	}
}

int main() {
	int N;
	scanf("%d\n\n", &N);
	while(N--){
		string line;
		stringstream ss;
		ans = false;
		getline(cin, line);
		ss.clear();
		ss << line;
		elements.clear();
		while (ss >> line) elements.push_back(line[0]);
		sort(elements.begin(), elements.end());

		getline(cin, line);
		ss.clear();
		ss << line;
		adj.clear();
		adj.resize(91);
		while (ss >> line)
			adj[line[0]].push_back(line[2]);
		dfs("");
		if (!ans) printf("NO\n");
		if (N) cout << endl;
		if (!getline(cin, line)) break;
	}
}