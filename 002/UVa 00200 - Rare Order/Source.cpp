#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <time.h>
using namespace std;
list<char> List;

struct node {
	bool use;
	char ch;
	vector<node*> adj;
	string color;
};

void dfs_visit(node* u) {
	u->color = "gray";
	for (int i = 0; i < u->adj.size(); i++) {
		if (u->adj[i]->color == "white" && u->adj[i]->use)
			dfs_visit(u->adj[i]);
	}
	u->color = "black";
	List.push_front(u->ch);
}

void dfs(vector<node>& map)
{
	for (int i = 0; i < map.size(); i++)
		map[i].color = "white";
	for (int i = 0; i < map.size(); i++)
		if (map[i].color == "white" && map[i].use)
			dfs_visit(&map[i]);
}
int main() {
	ofstream out("o.txt");
	string a;
	List.clear();
	vector<node> map;
	for (int i = 0; i < 26; i++) {
		node n;
		n.use = false;
		n.ch = 'A' + i;
		map.push_back(n);
	}
	string s;
	bool oneSentence = true;
	while (cin >> a) {
		while (cin >> s) {
			if (s == "#") break;
			if (oneSentence) oneSentence = false;
			int siz = min(a.size(), s.size());
			int i = 0;
			while (i < siz) {
				if (a[i] == s[i]) {
					i++;
					map[s[i] - 'A'].use = true;
				}
				else {
					map[a[i] - 'A'].adj.push_back(&map[s[i] - 'A']);
					map[a[i] - 'A'].use = true;
					map[s[i] - 'A'].use = true;
					break;
				}
			}
			a = s;
		}
	}
	if (oneSentence) {
		map[a[0] - 'A'].use = true;
	}
	dfs(map);
	list<char>::iterator it = List.begin();
	while (it != List.end())
	{
		cout << *it;
		it++;
	}
	cout << endl;
}