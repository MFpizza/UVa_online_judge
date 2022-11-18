#include <vector>
#include <iostream>
#include <stack>
#include<set>
#include <algorithm>
#include <fstream>
using namespace std;
ofstream out("out.txt");
struct Node {
	int d, data, low;
	vector<Node*> adj;
	int scc;
};
set<Node*> Set;
stack<Node*> Stack;
int tim,coun;

void Scc(Node* u) {
	tim++;
	u->d = u->low = tim;
	Stack.push(u);
	Set.insert(u);
	for (int i = 0; i < u->adj.size(); i++) {
		Node* v = u->adj[i];
		if (v->d == 0) {
			Scc(v);
			u->low = min(v->low, u->low);
		}
		else if (Set.count(v)) {
			u->low = min(u->low, v->d);
		}
	}
	if (u->low == u->d) {
		Node* tem = NULL;
		do {
			tem = Stack.top();
			Stack.pop();
			tem->scc = coun;
			Set.erase(tem);
		} while (tem != u);
		coun++;
	}
}

void dfs(vector<Node>& map) {
	for (int i = 1; i < map.size(); i++)
		map[i].d = 0;
	tim = 0;
	for (int i = 1; i < map.size(); i++) {
		if (map[i].d == 0) {
			Scc(&map[i]);
		}
	}
}

int main() {
	int cityNum, roadNum;
	while (cin >> cityNum >> roadNum) {
		if (!cityNum && !roadNum) break;

		coun = 0;
		Set.clear();
		while (!Stack.empty())
			Stack.pop();

		vector<Node> map;
		for (int i = 0; i < cityNum + 1; i++) {
			Node n;
			n.data = i;
			map.push_back(n);
		}

		int cityA, cityB, type;
		while (roadNum--) {
			cin >> cityA >> cityB >> type;
			if (type == 2)
				map[cityB].adj.push_back(&map[cityA]);
			map[cityA].adj.push_back(&map[cityB]);
		}
		dfs(map);
		if (coun == 1)
			cout << coun << endl;
		else
			cout << "0" << endl;
		//cout << coun << endl;
	}
}