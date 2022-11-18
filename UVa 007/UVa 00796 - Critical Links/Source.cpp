#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <fstream>
using namespace std;

struct node {
	int d, low, data;
	vector<node*> adj;
	bool bridge;
	node* parent;
};
struct brid {
	bool operator<(const brid c)const {
		if (b == c.b)return a > c.a;
		return b > c.b;
	}
	int a;
	int b;
};

int tim;
priority_queue<brid> bridg;
void bridge(node* u) {
	tim++;
	u->d = u->low = tim;
	for (int i = 0; i < u->adj.size(); i++) {
		if (u->adj[i]->d == 0) {
			u->adj[i]->parent = u;
			bridge(u->adj[i]);
			u->low = min(u->adj[i]->low, u->low);
			if (u->adj[i]->low > u->d) {
				brid a;
				a.a = u->data;
				a.b = u->adj[i]->data;
				if (a.b > a.a) {
					int tem = a.a;
					a.a = a.b;
					a.b = tem;
				}
				bridg.push(a);
			}
		}
		else if (u->adj[i] != u->parent) {
			u->low = min(u->adj[i]->d, u->low);
		}
	}
}

void dfs(vector<node>& map) {
	for (int i = 0; i < map.size(); i++) {
		map[i].d = 0;
		map[i].parent = NULL;
	}
	tim = 0;
	for (int i = 0; i < map.size(); i++)
		if (map[i].d == 0)
			bridge(&map[i]);
}

int main() {
	int nodenum;
	ofstream out("o.txt");
	while (cin >> nodenum) {
		if (nodenum == -1) break;
		while (!bridg.empty())
			bridg.pop();
		vector<node> map;
		for (int i = 0; i < nodenum; i++) {
			node n;
			n.data = i;
			map.push_back(n);
		}
		int a, b,c;
		char ch;
		string s;
		for (int i = 0; i < nodenum; i++) {
			cin >> a >> ch>>c>>ch;
			for (int k = 0; k < c; k++) {
				cin >> b;
				map[a].adj.push_back(&map[b]);
				map[b].adj.push_back(&map[a]);
			}
		}
		dfs(map);
		cout << bridg.size() << " critical links\n";
		while(!bridg.empty()){
			brid a = bridg.top();
			bridg.pop();
			cout << a.b << " - " << a.a << endl;
		}
		cout << endl;
		getline(cin, s);
	}
}