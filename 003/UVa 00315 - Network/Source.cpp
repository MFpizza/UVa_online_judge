#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

int tim;

struct node {
	int data;
	vector<node*> adj;
	int d, low, numC;
	node* parent;
	bool cut;
};

void CutPoint(node* u) {
	tim++;
	u->d = u->low = tim;
	for (int i = 0; i < u->adj.size(); i++) {
		node* v = u->adj[i];
		if (v->d == 0) {
			v->parent = u;
			u->numC += 1;
			CutPoint(v);
			u->low = min(u->low, v->low);
			if (u->parent != NULL)
				if (v->low >= u->d)
				{
					u->cut = true;
				}
		}
		else if (v != u->parent)
			u->low = min(v->d, u->low);
	}
}

void dfs(vector<node>& map) {
	for (int i = 1; i < map.size(); i++) {
		map[i].d = 0;
		map[i].numC = 0;
		map[i].cut = false;
		map[i].parent = NULL;
	}
	tim = 0;
	for (int i = 1; i < map.size(); i++) {
		if (map[i].d == 0)
		{
			CutPoint(&map[i]);
			if (map[i].numC > 1)
			{
				map[i].cut = true;
			}
		}
	}
}

int main() {
	ofstream out("4.txt");
	int nodeNum;
	while (cin >> nodeNum) {
		int coun = 0;
		if (nodeNum == 0) break;
		vector<node> map;
		for (int i = 0; i < nodeNum + 1; i++) {
			node nbe;
			nbe.data = i;
			map.push_back(nbe);
		}
		int x, y;
		char c;
		while (scanf("%d", &x),x) {
			while (scanf("%d%c", &y, &c) ) {
				map[x].adj.push_back(&map[y]);
				map[y].adj.push_back(&map[x]);
				if (c == '\n') break;
			}
		}
		dfs(map);
		for (int i = 1; i < map.size(); i++)
			if (map[i].cut == true)
				coun++;
		cout << coun << endl;
	}
}