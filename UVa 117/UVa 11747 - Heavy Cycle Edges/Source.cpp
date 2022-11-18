#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

struct edge;
struct node {
	int rank;
	
	vector<edge*> adj;
	node* parent;
};
struct edge {
	node* toNode;
	node* fromNode;
	int weight;
};
struct cmp {
	bool operator()(const edge* a, const edge* b)const {
		return a->weight > b->weight;
	}
};

node* find_set(node* x) {
	if (x != x->parent)
		x->parent = find_set(x->parent);
	return x->parent;
}

priority_queue<edge*, vector<edge*>, cmp> qu;

void KRUSKAL(node* r, vector<node*>map,vector<edge*> &A) {
	
	for (int i = 0; i < map.size(); i++) {
		map[i]->parent = map[i];
		map[i]->rank = 0;
	}
	while (!qu.empty()) {
		edge* E = qu.top();
		qu.pop();
		if (find_set(E->fromNode) != find_set(E->toNode)) {
			
			node* x = find_set(E->fromNode), *y = find_set(E->toNode);
			if (x->rank > y->rank)
				y->parent = x;
			else
			{
				x->parent = y;
				if (x->rank == y->rank)
					y->rank++ ;
			}
		}
		else
			A.push_back(E);
	}
}
#include <climits>
#include <fstream>
int main() {
	int nN, eN;
	ofstream out("o.txt");
	while (cin >> nN >> eN) {
		if (!nN && !eN)
			break;
		while (!qu.empty())
			qu.pop();

		vector<node*> map;
		for (int i = 0; i < nN; i++) {
			node* nNN = new node;
			map.push_back(nNN);
		}
		int a, b, w;
		for (int i = 0; i < eN; i++) {
			cin >> a >> b >> w;
			edge* nE = new edge;
			nE->fromNode = map[a];
			nE->toNode = map[b];
			nE->weight = w;
			qu.push(nE);
			map[a]->adj.push_back(nE);
		}
		vector<edge*> Ans;
		KRUSKAL(map[0],map,Ans);
		if (Ans.size() == 0)
			cout << "forest\n";
		else {
			cout << Ans[0]->weight;
			for (int i = 1; i < Ans.size(); i++)
				cout << " " << Ans[i]->weight;
			cout << endl;
		}
	}
}