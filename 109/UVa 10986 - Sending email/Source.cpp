#include <queue>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct edge {
	int toNode;
	int time;
};

struct node {
	/*node() {
		color = "w";
		d = INT_MAX;
		ed.clear();
	}
	*/
	bool operator<(const node* b)const {
		return b->d < d;
	}
	vector<edge*> ed;
	int d;
	string color;
};
struct cmp {
	bool operator()(const node* a, const node* b)const {
		return a->d > b->d;
	}
};

vector<node*> map;
priority_queue<node*, vector<node*>, cmp> q;
#include <iomanip>
void showMap() {
	cout << "---------------------------------------------------\n";
	for (int i = 0; i < map.size(); i++) {
		cout << i<<": " << map[i]->d << endl;
	}
}

void dij(int s, int e) {
	map[s]->d = 0;
	q.push(map[s]);
	while (1) {
		node* front = NULL;
		while (!q.empty()) {
			front = q.top();
			q.pop();
			if (front->color == "w") break;
		}
		if (front == NULL || (front == map[e])) return;
		front->color = "b";
		for (int i = 0; i < front->ed.size(); i++) {
			if (map[front->ed[i]->toNode]->color == "w")
				if (map[front->ed[i]->toNode]->d > front->ed[i]->time + front->d) {
					map[front->ed[i]->toNode]->d = front->ed[i]->time + front->d;
					q.push(map[front->ed[i]->toNode]);
					//showMap();
				}
		}
	}
}

#include <fstream>
int main() {
	ofstream out("o.txt");
	int cas;
	cin >> cas;
	for (int i = 1; i <= cas; i++) {
		int ServerNum, EdgeNum, start, end;
		cin >> ServerNum >> EdgeNum >> start >> end;
		map.clear();
		while (!q.empty())
			q.pop();
		//map.resize(ServerNum);
		for (int i = 0; i < ServerNum; i++) {
			node* nN = new node;
			nN->d = INT_MAX;
			nN->color = "w";
			map.push_back(nN);
		}
		for (int j = 0; j < EdgeNum; j++) {
			int a, b, ti;
			cin >> a >> b >> ti;
			edge* nE = new edge;
			edge* nE2 = new edge;
			nE2->time = nE->time = ti;
			nE->toNode = b;
			nE2->toNode = a;
			map[a]->ed.push_back(nE);
			map[b]->ed.push_back(nE2);
		}
		dij(start, end);
		cout << "Case #" << i << ": ";
		if (map[end]->d == INT_MAX) cout << "unreachable\n";
		else cout << map[end]->d << endl;
	}
}