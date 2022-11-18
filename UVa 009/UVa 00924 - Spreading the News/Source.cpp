#include <vector>
#include <queue>
#include <iostream>
#include <string>
using namespace std;

struct node {
	int d;
	string color;
	vector<node*> adj;
};

void Bfs(vector<node*> map, node* ptr) {
	for (int i = 0; i < map.size(); i++) {
		map[i]->d = 0;
		map[i]->color = "white";
	}
	queue<node*> q;
	ptr->d = 1;
	ptr->color = "gray";
	q.push(ptr);
	vector<int> day;
	day.push_back(0);
	while (!q.empty()) {
		node* front = q.front();
		q.pop();
		for (int i = 0; i < front->adj.size(); i++) {
			node* v = front->adj[i];
			if (v->color == "white") {
				v->color = "gray";
				v->d = front->d + 1;
				if (v->d > day.size()) day.push_back(0);
				day[front->d]++;
				q.push(v);
			}
		}
		front->color = "black";
	}
	int Ma = 0, Da = 0;
	for (int i = 0; i < day.size(); i++) {
		if (day[i] > Ma) {
			Ma = day[i];
			Da = i;
		}
	}
	if (Ma == 0) cout << '0' << endl;
	else
		cout << Ma << " " << Da << endl;
}

int main() {
	int group;
	cin >> group;
	vector<node*> map;
	for (int i = 0; i < group; i++) {
		node* newN = new node;
		map.push_back(newN);
	}
	for (int i = 0; i < map.size(); i++) {
		int friend1, friendNum;
		cin >> friendNum;
		for (int l = 0; l < friendNum; l++) {
			cin >> friend1;
			map[i]->adj.push_back(map[friend1]);
		}
	}
	int cas;
	cin >> cas;
	while (cas--) {
		int firstMan;
		cin >> firstMan;
		Bfs(map, map[firstMan]);
	}
}