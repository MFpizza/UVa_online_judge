#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
using namespace std;

struct node {
	int data;
	int d, low;
	vector<node*> adj;
	int numC;
	node* parent;
	bool cut;
};

struct stackElement {
	node* u, * v;
};
set<node*>Set;
vector<vector<node*>> Biconponent;
stack<stackElement> Stack;

int tim,coun;
void Biconnected(node* u) {
	u->low = u->d = ++tim;
	for (int i = 0; i < u->adj.size(); i++) {
		if (u->adj[i]->d == 0) {
			u->numC++;
			u->adj[i]->parent = u;
			stackElement n;
			n.u = u; n.v = u->adj[i];
			Stack.push(n);
			Biconnected(u->adj[i]);
			u->low = min(u->low, u->adj[i]->low);
			if (u->parent != NULL)
				if (u->adj[i]->low >= u->d)
					u->cut = true;
			if (u->adj[i]->low >= u->d) {
				Set.clear();
				vector<node*> newComponent;
				node* x, * y;
				do {
					stackElement n = Stack.top();
					x = n.u; y = n.v;
					if (!Set.count(x)) {
						newComponent.push_back(x);
						Set.insert(x);
					}
						
					if (!Set.count(y)) {
						newComponent.push_back(y);
						Set.insert(y);
					}
						
					Stack.pop();
				} while (x != u || y != u->adj[i]);
				Biconponent.push_back(newComponent);
			}
		}
		else if (u->adj[i]->d < u->d && u->adj[i] != u->parent) {
			stackElement n;
			n.u = u; n.v = u->adj[i];
			Stack.push(n);
			u->low = min(u->low, u->adj[i]->d);
		}
	}
}

void dfs(vector<node*>map) {
	for (int i = 1; i < map.size(); i++) {
		map[i]->d = 0;
		map[i]->numC = 0;
		map[i]->parent = NULL;
		map[i]->cut = false;
	}
	coun = 0;
	tim = 0;
	while (!Stack.empty())
		Stack.pop();
	for (int i = 1; i < map.size(); i++) {
		if (map[i]->d == 0) {
			Biconnected(map[i]);
			if (map[i]->numC > 1)
				map[i]->cut = true;
		}
	}
}
void solve() {
	long long int ans1=0, ans2=1;
	for (int i = 0; i < Biconponent.size(); i++) {
		int CutNUm = 0;
		for (int j = 0; j < Biconponent[i].size(); j++) {
			if (Biconponent[i][j]->cut)
				CutNUm++;
		}
		if (CutNUm == 1) {
			ans1++;
			ans2 *= (long long int)(Biconponent[i].size() - CutNUm);
		}
	}
	if (Biconponent.size() == 1) {
		ans1 = 2;
		ans2 = Biconponent[0].size() * (Biconponent[0].size() - 1) / 2;
	}
	cout << ans1 << " " << ans2 << endl;
}

int main() {
	int count = 1;
	int cas;
	while (cin >> cas,cas) {
		vector<node*> map;
		Biconponent.clear();
		int a, b;
		while (cas--) {
			cin >> a >> b;
			int ma = max(a, b);
			if (ma >= map.size()) {
				for (int i = map.size(); i <= ma; i++) {
					node* n = new node;
					n->data = i;
					map.push_back(n);
				}
			}
			map[a]->adj.push_back(map[b]);
			map[b]->adj.push_back(map[a]);
		}
		dfs(map);
		cout << "Case " << count++ << ": ";
		solve();
	}
}