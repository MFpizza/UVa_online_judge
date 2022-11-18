#include <iostream>
#include <vector>
#include<string>
#include <queue>
#include <climits>
using namespace std;
struct edge {
	int toNode;
	int time;
};

struct node {
	bool operator<(const node* b)const {
		return b->d < d;
	}
	vector<edge*> ed;
	int d;
	string color;
	int nodeNum;
};
struct cmp {
	bool operator()(const node* a, const node* b)const {
		return a->d > b->d;
	}
};

vector<node*> map;
priority_queue<node*, vector<node*>, cmp> q;

void dij(int s) {
	map[s]->d = 0;
	q.push(map[s]);
	while (1) {
		node* front = NULL;
		while (!q.empty()) {
			front = q.top();
			q.pop();
			if (front->color == "w") break;
		}
		if (front == NULL ) return;
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
	ofstream out("ot.txt");
	int cas;
	cin >> cas;
	string s;
	getline(cin, s);
	while (cas--) {
		getline(cin, s);
		map.clear();
		while (!q.empty())
			q.pop();
		int nodenum, endPoint, timer, edgeNum;
		cin >> nodenum >> endPoint >> timer >> edgeNum;
		for (int i = 0; i < nodenum; i++) {
			node* nN = new node;
			nN->d = INT_MAX;
			nN->color = "w";
			nN->nodeNum = i + 1;
			map.push_back(nN);
		}
		for (int i = 0; i < edgeNum; i++) {
			int a, b, weight;
			cin >> a >> b >> weight;
			edge* nE = new edge;
			nE->time = weight;
			nE->toNode = a - 1;
			map[b - 1]->ed.push_back(nE);
		}
		dij(endPoint-1);
		int total = 0;
		for (int i = 0; i < map.size(); i++) {
			if (map[i]->d <= timer)
				total++;
		}
		cout << total << endl;
		if(cas) cout << endl;
	}
}