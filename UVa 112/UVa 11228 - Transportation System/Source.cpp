#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <queue>
#include <math.h>
using namespace std;

#include <fstream>
ofstream out("i.txt");
struct node;
struct edge {
	node* toNode;
	double howLong;
};

struct node {
	int d;
	int x, y;
	vector<edge*> adj;
	edge* parent;
};
set<node*>allN;
node* findMinimum(vector<node*>map) {
	int tem = INT_MAX;
	node* ptr = NULL;
	for (int i = 0; i < map.size(); i++) {
		if (map[i]->d < tem && allN.count(map[i])) {
			tem = map[i]->d;
			ptr = map[i];
		}
	}
	return ptr;
}


void MST(node* v, vector<node*>map, int R) {
	double road = 0, Rail = 0;
	int state = 1;
	v->d = 0;
	while (!allN.empty()) {
		node* u = findMinimum(map);
		allN.erase(u);
		for (int i = 0; i < u->adj.size(); i++) {
			if (allN.count(u->adj[i]->toNode) && u->adj[i]->toNode->d > u->adj[i]->howLong) {
				u->adj[i]->toNode->d = u->adj[i]->howLong;
				u->adj[i]->toNode->parent = u->adj[i];
			}
		}
	}
	for (int i = 0; i < map.size(); i++) {
		if (map[i]->parent != NULL)
			if (map[i]->parent->howLong > R) {
				state++;
				Rail += map[i]->parent->howLong;
			}
			else
				road += map[i]->parent->howLong;
	}
	road=round(road);
	Rail = round(Rail);
	cout << state << " " << road << " " << Rail << endl;
}
void buildMap(vector<node*>& map) {
	for (int i = 0; i < map.size(); i++) {
		for (int k = 0; k < map.size(); k++) {
			if (i != k) {
				edge* nE = new edge;
				nE->howLong = sqrt(pow(map[i]->x - map[k]->x, 2) + pow(map[i]->y - map[k]->y, 2));
				nE->toNode = map[k];
				map[i]->adj.push_back(nE);
			}
		}
	}
}

int main() {
	int cas;
	
	int ca = 1;
	cin >> cas;
	while (cas--) {

		allN.clear();
		int n, R;
		cin >> n >> R;
		vector<node*> map;
		for (int i = 0; i < n; i++) {
			node* nN = new node;
			cin >> nN->x >> nN->y;
			nN->d = INT_MAX;
			nN->parent = NULL;
			map.push_back(nN);
			allN.insert(nN);
		}
		buildMap(map);
		cout << "Case #" << ca++ << ": ";
		MST(map[0], map, R);
	}
}