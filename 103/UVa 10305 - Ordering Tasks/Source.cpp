#include <iostream>
#include <vector>
#include <list>
#include <fstream>
using namespace std;
struct node {
	int data;
	vector<node*> adj;
	string color;
};
list<int> List;
void dfsVisit(node* u) {
	u->color = "gray";
	for (int i = 0; i < u->adj.size(); i++) {
		if (u->adj[i]->color == "white")
			dfsVisit(u->adj[i]);
	}
	u->color = "black";
	List.push_front(u->data);
}
void dfs(vector<node*> map) {
	for (int i = 1; i < map.size(); i++)
		map[i]->color = "white";
	for (int i = 0; i < map.size(); i++)
		if (map[i]->color == "white")
			dfsVisit(map[i]);
}
int main() {
	ofstream out("ou.txt");
	int a, b;
	while (cin >> a >> b) {
		if (a == 0 && b == 0) break;
		List.clear();
		vector<node*> map;
		for (int i = 0; i < a + 1; i++)
		{
			node* n = new node;
			n->data = i;
			map.push_back(n);
		}
		int c, d;
		while (b--) {
			cin >> c >> d;
			map[c]->adj.push_back(map[d]);
		}
		dfs(map);
		for (auto it = List.begin(); it != List.end(); ++it) {
			if (it != List.begin()) cout << ' ';
			cout << *it;
		}
		cout << endl;
	}
}