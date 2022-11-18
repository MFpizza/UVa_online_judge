#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct ans {
	ans(int a, int b) {
		x = a; y = b;
	}
	int x, y;
	bool operator<(const ans b)const {
		if (y == b.y) return x > b.x;
		return y < b.y;
	}
};

priority_queue<ans> que;
int tim,coun;
#include <fstream>
ofstream out("4.txt");
struct node {
	int data;
	vector<node*> adj;
	int d, low, numC;
	node* parent;
	bool cut;
	string color;
	int cuta;
};

void dfsC(vector<node>& map, node* ignore);

void CutPoint(vector<node>& map,node* u) {
	tim++;
	u->d = u->low = tim;
	for (int i = 0; i < u->adj.size(); i++) {
		node* v = u->adj[i];
		if (v->d == 0) {
			v->parent = u;
			u->numC++;
			CutPoint(map,v);
			u->low = min(u->low, v->low);
			if (u->parent != NULL)
				if (v->low >= u->d)
				{
					u->cut = true;
					u->cuta++;
					if (u->cuta == 1) {
						dfsC(map, u);
					}
				}
		}
		else if (v != u->parent)
			u->low = min(v->d, u->low);
	}
}

void dfs(vector<node>& map) {
	for (int i = 0; i < map.size(); i++) {
		map[i].d = 0;
		map[i].cuta = 0;
		map[i].numC = 0;
		map[i].cut = false;
		map[i].parent = NULL;
	}
	tim = 0;
	for (int i = 0; i < map.size(); i++) {
		if (map[i].d == 0)
		{
			CutPoint(map,&map[i]);
			if (map[i].numC > 1)
			{
				map[i].cut = true;
				map[i].cuta++;
				if (map[i].cuta == 1) {
					dfsC(map, &map[i]);
				}
			}
		}
	}
}

void dfs_visit(node* u) {
	u->color = "gray";
	for (int i = 0; i < u->adj.size(); i++) {
		if (u->adj[i]->color == "white")
			dfs_visit(u->adj[i]);
	}
	u->color = "black";
}

void dfsC(vector<node> &map,node* ignore) {
	for (int i = 0; i < map.size(); i++)
		map[i].color = "white";
	coun = 0;
	ignore->color = "black";
	for (int i = 0; i < map.size(); i++)
		if (map[i].color == "white") {
			coun++;
			dfs_visit(&map[i]);
		}
	ans a(ignore->data, coun);
	que.push(a);
}

int main() {
	int nodeNum, cas;
	while (cin >> nodeNum >> cas) {
		int cas2 = cas;
		if (nodeNum == 0 && cas == 0)break;
		while (!que.empty())
			que.pop();
		vector<node> vec;
		for (int i = 0; i < nodeNum; i++) {
			node newNode;
			newNode.data = i;
			vec.push_back(newNode);
		}
		int a, b;
		while (cin >> a >> b) {
			if (a == -1 && b == -1) break;
			vec[a].adj.push_back(&vec[b]);
			vec[b].adj.push_back(&vec[a]);
		}
		dfs(vec);
		cas -= que.size();
		if (cas) {
			for (int i = 0; i < vec.size(); i++)
				if (vec[i].cut == false) {
					//dfsC(vec, &vec[i]);
					ans a(vec[i].data, 1);
					que.push(a);
					cas--;
					if (cas == 0)break;
				}
		}
		while (cas2--) {
			ans a = que.top();
			que.pop();
			cout << a.x <<" "<< a.y << endl;
		}
		cout << endl;
	}
}