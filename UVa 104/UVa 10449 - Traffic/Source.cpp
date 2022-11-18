#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
using namespace std;

struct edge {
	int From, To;
	long long int Weight;
};
struct node {
	long long int d;
	vector<node*>adj;
	bool inCycle, visit;
	int city;
};
void dfs(node* u) {
	u->inCycle = true;
	for (int i = 0; i < u->adj.size(); i++)
		if (u->adj[i]->inCycle == false)
			dfs(u->adj[i]);
}
void dfs2(node* u) {
	u->visit = true;
	for (int i = 0; i < u->adj.size(); i++)
		if (u->adj[i]->visit == false)
			dfs2(u->adj[i]);
}

void bellman(vector<node*> map, vector<edge*> E) {
	map[1]->d = 0;
	for (int i = 1; i <= map.size() - 1; i++)
		for (int i = 0; i < E.size(); i++)
			if (map[E[i]->To]->d > map[E[i]->From]->d + E[i]->Weight)
				map[E[i]->To]->d = map[E[i]->From]->d + E[i]->Weight;
	for (int i = 0; i < E.size(); i++)
		if (map[E[i]->To]->d > map[E[i]->From]->d + E[i]->Weight) {
			map[E[i]->To]->inCycle = true;
			map[E[i]->From]->inCycle = true;
		}
	for (int i = 1; i < map.size(); i++) {
		if (map[i]->inCycle) {
			dfs(map[i]);
		}
	}
}

int main() {
	ofstream out("out.txt");
	int num = 1, tota;
	while (cin >> tota) {
		if (tota == -1) return 0;
		vector<edge*> Edge;
		vector<node*> map;
		for (int i = 0; i < tota + 1; i++) {
			node* nN = new node;
			map.push_back(nN);
		}
		for (int i = 1; i <= tota; i++) {
			cin >> map[i]->city;
			map[i]->visit = false;
			map[i]->inCycle = false;
			map[i]->d = INT_MAX;
		}
		int EdNum;
		cin >> EdNum;
		for (int i = 0; i < EdNum; i++) {
			edge* nE = new edge;
			cin >> nE->From >> nE->To;
			map[nE->From]->adj.push_back(map[nE->To]);
			long long int number = map[nE->To]->city - map[nE->From]->city;
			long long int tem = number;
			number = tem * tem * tem;
			nE->Weight = number;
			Edge.push_back(nE);
		}
		bellman(map, Edge);
		dfs2(map[1]);
		
		cout << "Set #" << num++ << endl;
		int outPutNum, ca;
		cin >> outPutNum;
		for (int i = 0; i < outPutNum; i++) {
			cin >> ca;
			if (map[ca]->inCycle || map[ca]->d == INT_MAX || map[ca]->d < 3 || map[ca]->visit == false)
				cout << "?\n";
			else cout << map[ca]->d << endl;
		}
	}
}