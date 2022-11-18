#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <fstream>
using namespace std;
struct Node {
	int data;
	int d;
	int low;
	vector<Node*> next;
	int SCC;
	string color;
	int next_Scc;
	vector<Node*> prev;
};
struct node {
	vector<int> data;
	vector<node*> prev;
};
ofstream out("out.txt");
int tim = 0; int coun = 0;
stack<Node*> sta;
set<Node*> Set;
vector<int> SCCnum;
vector<bool> visited;

void strong_connect(vector<Node>& map, Node* u, vector<node>& map2) {
	tim++;
	u->d = tim;
	u->low = tim;
	sta.push(u);
	Set.insert(u);
	for (int i = 0; i < u->next.size(); i++) {
		Node* v = u->next[i];
		if (v->d == 0) {
			strong_connect(map, v, map2);
			u->low = min(u->low, v->low);
		}
		else if (Set.count(v)) {
			u->low = min(u->low, v->d);
		}
	}
	if (u->low == u->d) {
		//cout << coun + 1 << ": ";
		Node* tem = NULL;
		do {
			tem = sta.top();
			sta.pop();
			tem->SCC = coun;
			if (SCCnum.size() == coun) {
				SCCnum.push_back(0);
				visited.push_back(false);
			}
			SCCnum[coun]++;
			Set.erase(tem);
		} while (tem != u);
		coun++;
	}
}

void dfs(vector<Node>& map, vector<node>& map2) {
	for (int i = 1; i < map.size(); i++)
		map[i].d = 0;
	tim = 0;
	while (!sta.empty())
		sta.pop();
	Set.clear();
	for (int i = 1; i < map.size(); i++)
		if (map[i].d == 0)
			strong_connect(map, &map[i], map2);
}

void dfstwo(vector<Node>& map,vector<node>& map2) {
	for (int i = 0; i < coun; i++) {
		node newN;
		map2.push_back(newN);
	}
	for (int i = 1; i < map.size(); i++) {
		Node* u = &map[i];
		map2[u->SCC].data.push_back(u->data);
		for (int j = 0; j < u->next.size(); j++) {
			Node* v = u->next[j];
			if (v->SCC != u->SCC) {
				map2[v->SCC].prev.push_back(&map2[u->SCC]);
			}
		}
	}
	int count = 0;
	for (int i = 0; i < map2.size(); i++) {
		if (map2[i].prev.size() == 0)
			count++;
	}
	cout << count << endl;
}

int main() {
	int cas, n = 1;
	cin >> cas;
	while (cas--) {
		int People,line;
		cin >> People>>line;
		SCCnum.clear();
		visited.clear();
		coun = 0;
		vector<Node> map;
		vector<node> map2;
		for (int i = 0; i < People + 1; i++) {
			Node newNode;
			newNode.data = i;
			map.push_back(newNode);
		}
		int a, b;
		for (int i = 0; i < line; i++) {
			cin >> a >> b;
			map[b].prev.push_back(&map[a]);
			map[a].next.push_back(&map[b]);
		}
		dfs(map,map2);
		dfstwo(map,map2);
	}
}