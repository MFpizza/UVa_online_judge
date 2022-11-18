#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <queue>
using namespace std;

struct edge {
	int toNode;
	int fromNode;
	long long int howLong;
	bool used;
};

struct node {
	bool used;
	int data;
	int d;
	vector<edge*> adj;
	node* parent;
};

struct cmp {
	bool operator()(const node* a, const node* b)const {
		return a->d > b->d;
	}
};

node* findMinimum(vector<node*> map) {
	node* Nreturn = NULL;
	int temp = INT_MAX;
	for (int i = 0; i < map.size(); i++) {
		if (map[i]->d < temp && map[i]->used == false) {
			temp = map[i]->d;
			Nreturn = map[i];
		}
	}
	return Nreturn;
}

bool allUsed(vector<node*>map) {
	bool R = false;
	for (int i = 0; i < map.size(); i++) {
		if (map[i]->used == false) {
			R = true;
		}
	}
	return R;
}

set<node*> allNode;
void MST(node* v, vector<node*>map) {
	v->d = 0;
	while (allUsed(map)) {
		node* u = findMinimum(map);

		for (int i = 0; i < u->adj.size(); i++)
			if (map[u->adj[i]->toNode] == u->parent)
				u->adj[i]->used = true;

		u->used = true;
		for (int i = 0; i < u->adj.size(); i++) {
			if (map[u->adj[i]->toNode]->used == false && map[u->adj[i]->toNode]->d > u->adj[i]->howLong) {
				map[u->adj[i]->toNode]->d = u->adj[i]->howLong;
				map[u->adj[i]->toNode]->parent = u;
			}
		}
	}
}
#include <fstream>
int main() {
	int n, m;
	ofstream out("i.txt");
	while (cin >> m >> n) {
		if (m == 0 && n == 0)
			break;
		allNode.clear();
		vector<node*> map;
		for (int i = 0; i < m; i++) {
			node* nN = new node;
			nN->d = INT_MAX;
			nN->parent = NULL;
			nN->used = false;
			nN->data = i;
			map.push_back(nN);
			allNode.insert(nN);
		}
		vector<edge*>allEdge;
		int a, b;
		long long int c;
		for (int i = 0; i < n; i++) {
			edge* nE = new edge;
			cin >> a >> b >> c;
			nE->howLong = c;
			nE->fromNode = a;
			nE->used = false;
			nE->toNode = b;
			map[a]->adj.push_back(nE);
			allEdge.push_back(nE);
			edge* nE2 = new edge;
			nE2->howLong = c;
			nE2->fromNode = b;
			nE2->toNode = a;
			nE2->used = false;
			map[b]->adj.push_back(nE2);
			allEdge.push_back(nE2);
		}
		MST(map[0], map);
		long long int tem = 0;
		for (int i = 0; i < allEdge.size(); i += 2)
			if (allEdge[i]->used == false && allEdge[i + 1]->used == false)
				tem += allEdge[i]->howLong;

		cout << tem << endl;
		map.clear();
	}
}