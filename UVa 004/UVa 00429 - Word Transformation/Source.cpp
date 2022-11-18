#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <string>
#include <fstream>
using namespace std;

struct node {
	string name;
	int howlong = 0;
	vector<node*> adj;
	string color;
};

void connect(vector<node*>& map, node* newNode) {
	for (int i = 0; i < map.size(); i++) {
		if (map[i]->name.size() == newNode->name.size()) {
			int num = 0;
			for (int k = 0; k < newNode->name.size(); k++) {
				if (map[i]->name[k] != newNode->name[k])
					num++;
			}
			if (num == 1) {
				map[i]->adj.push_back(newNode);
				newNode->adj.push_back(map[i]);
			}
		}
	}
}

void showBFSmap(vector<node*>map) {
	for (int i = 0; i < map.size(); i++) {
		cout << map[i]->name << ":";
		for (int j = 0; j < map[i]->adj.size(); j++) {
			cout << " " << map[i]->adj[j]->name;
		}
		cout << endl;
	}
}

void BFS(vector<node*> map, node* start) {
	for (int i = 0; i < map.size(); i++) {
		map[i]->howlong = INT_MAX;
		map[i]->color = "white";
	}
	start->howlong = 0;
	start->color = "gray";
	queue<node*> q;
	q.push(start);
	while (!q.empty()) {
		node* front = q.front();
		q.pop();
		for (int i = 0; i < front->adj.size(); i++) {
			node* v = front->adj[i];
			if (v->color == "white") {
				v->color = "gray";
				v->howlong = front->howlong + 1;
				q.push(v);
			}
		}
		front->color = "black";
	}
}

int main() {
	ofstream out("out.txt");
	int casNum; string s;
	cin >> casNum;
	getline(cin, s);
	getline(cin, s);
	while (casNum--) {
		vector<node*> map;
		while (getline(cin, s)) {
			if (s == "*") break;
			node* newNode = new node;
			newNode->name = s;
			map.push_back(newNode);
			connect(map, map[map.size() - 1]);
		}
		//showBFSmap(map);
		string start, end;
		while (getline(cin,start)) {
			if (start == "") break;
			end = "";
			for (int j = 0; j < start.size(); j++) {
				if (start[j] == ' ') {
					for (int k = j + 1; k < start.size(); k++) {
						end += start[k];
					}
					for (int k = 0; k <= end.size(); k++) {
						start.pop_back();
					}
				}
			}
			for (int i = 0; i < map.size(); i++) {
				if (map[i]->name == start) {
					BFS(map, map[i]);
					break;
				}
			}
			for (int i = 0; i < map.size(); i++) {
				if (map[i]->name == end) {
					cout << start << " " << end << " " << map[i]->howlong << endl;
					break;
				}
			}
		}
		if(casNum) cout << endl;
	}
}