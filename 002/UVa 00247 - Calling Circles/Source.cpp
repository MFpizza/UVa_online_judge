#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
using namespace std;
ofstream out("out.txt");
struct SccPoint {
	vector<string> name;
};
struct node {
	int d, low;
	vector<node*> adj;
	string name;
};
int tim,coun;
stack<node*> stac;
set<node*> sett;
vector<SccPoint> SccV;
void Scc(node* u) {
	tim++;
	u->low = u->d = tim;
	stac.push(u);
	sett.insert(u);
	for (int i = 0; i < u->adj.size(); i++) {
		node* v = u->adj[i];
		if (v->d == 0) {
			Scc(v);
			u->low = min(u->low, v->low);
		}
		else if (sett.count(v)) {
			u->low = min(v->d, u->low);
		}
	}
	if (u->low == u->d) {
		node* tem=NULL;
		do {
			tem = stac.top();
			stac.pop();
			sett.erase(tem);
			if (SccV.size() == coun) {
				SccPoint nP;
				SccV.push_back(nP);
			}
			SccV[coun].name.push_back(tem->name);
		} while (tem != u);
		coun++;
	}
}

void dfs(vector<node>& map) {
	for (int i = 0; i < map.size(); i++)
		map[i].d = 0;
	tim = 0;
	coun = 0;
	for (int i = 0; i < map.size(); i++)
		if (map[i].d == 0)
			Scc(&map[i]);
}

int main() {
	int people, call,co=1;
	while (cin >> people >> call,people,call) {
		while (!stac.empty())
			stac.pop();
		sett.clear();
		SccV.clear();
		vector<node> vec;
		for (int i = 0; i < people; i++) {
			node n;
			vec.push_back(n);
		}
		map<string, int> ma;
		string a, b;
		for (int i = 0; i < call; i++) {
			cin >> a >> b;
			if (ma.find(a) == ma.end()) {
				vec[ma.size()].name = a;
				ma[a] = ma.size();
			}
			if (ma.find(b) == ma.end()) {
				vec[ma.size()].name = b;
				ma[b] = ma.size();
			}
			vec[ma[a]].adj.push_back(&vec[ma[b]]);
		}
		dfs(vec);
		cout << "Calling circles for data set " << co++ << ":\n";
		for (int i = SccV.size() - 1; i >= 0;i--) {
			cout << SccV[i].name[SccV[i].name.size()-1];
			for (int j = SccV[i].name.size() - 2; j >= 0;j--) {
				cout <<", "<< SccV[i].name[j];
			}
			cout << "\n";
		}

	}
}