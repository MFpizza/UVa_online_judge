#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include <stack>
#include <fstream>
//https://www.cnblogs.com/Paul-Guderian/p/7018900.html
int tim, coun, isolate, coun2;
struct node {
	int d, low, data;
	vector<node*> adj;
	node* parent;
	int BCC;
	bool isolate = false;
};

struct Bignode {
	vector<int> data;
	vector<Bignode*> adj;
};
stack<node*> stac;

void Biconnect(node* u) {
	tim++;
	u->d = u->low = tim;
	stac.push(u);
	if (u->adj.size() == 0)
		u->isolate = true;
	for (int i = 0; i < u->adj.size(); i++) {
		node* v = u->adj[i];
		if (v->d == 0) {
			v->parent = u;
			Biconnect(v);
			u->low = min(u->low, v->low);
		}
		else if (v != u->parent)
			u->low = min(v->d, u->low);
	}
	if (u->low == u->d)
	{
		node* tem;
		do {
			tem = stac.top();
			stac.pop();
			tem->BCC = coun;
		} while (tem != u);
		coun++;
	}
}

void dfs(vector<node>& map) {
	for (int i = 1; i < map.size(); i++) {
		map[i].d = 0;
		map[i].parent = NULL;
	}
	tim = 0;
	for (int i = 1; i < map.size(); i++) {
		if (map[i].d == 0) {
			Biconnect(&map[i]);
		}
	}
}

void dfstwo(vector<node>& map, vector<Bignode>& map2) {
	for (int i = 1; i < map.size(); i++) {
		map2[map[i].BCC].data.push_back(map[i].data);
		for (int j = 0; j < map[i].adj.size(); j++) {
			if (map[i].adj[j]->BCC != map[i].BCC) {
				map2[map[i].BCC].adj.push_back(&map2[map[i].adj[j]->BCC]);
			}
		}
	}
	if (map2.size() == 1)
		return;
	for (int i = 0; i < map2.size(); i++) {
		if (map2[i].adj.size() == 1)
			coun2++;
		else if (map2[i].adj.size() == 0)
			isolate++;
	}
}

int main() {
	ofstream out("o.txt");
	int nodenum, edgenum;
	while (cin >> nodenum >> edgenum) {
		if (nodenum == -1 && edgenum == -1) break;
		while (!stac.empty())
			stac.pop();
		coun = 0, isolate = 0, coun2 = 0;
		vector<node> map;
		vector<Bignode> map2;
		for (int i = 0; i < nodenum + 1; i++) {
			node n;
			n.data = i;
			map.push_back(n);
		}
		int a, b;
		while (edgenum--) {
			cin >> a >> b;
			map[a].adj.push_back(&map[b]);
			map[b].adj.push_back(&map[a]);
		}
		dfs(map);
		for (int i = 0; i < coun; i++) {
			Bignode n;
			map2.push_back(n);
		}
		dfstwo(map, map2);
		cout << (coun2 + 1 + 2 * isolate) / 2 << endl;
	}
}