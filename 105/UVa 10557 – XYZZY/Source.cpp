#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <set>
using namespace std;

struct node {
	int d, energy, breadth;
	vector<node*> adj;
	set<node*> canArrive;
};
void bfs(node* u) {
	queue<node*> q;
	q.push(u);
	while (!q.empty()) {
		node* front = q.front();
		q.pop();

		if (u->canArrive.count(front))
			continue;
		else
			u->canArrive.insert(front);

		for (int i = 0; i < front->adj.size(); i++)
			q.push(front->adj[i]);
	}
}
bool SortestPath(vector<node*> map) { //找大的 最小路徑
	map[1]->d = 100; //題目第一個點要100能量
	map[1]->breadth = 0; //用來判斷正圈
	queue<node*> q;
	q.push(map[1]);

	node* f = NULL;
	while (!q.empty()) {
		f = q.front();
		q.pop();

		if (f == map[map.size() - 1])
			return true;
		else if (f->breadth > map.size() - 2) { //超過了話代表超過是正迴圈
			if (f->canArrive.count(map[map.size() - 1])) //正圈有沒有到最後一個點 有就回傳true
				return true;
			else //沒有就不用再判斷
				f->d = INT_MAX;
			continue;
		}

		for (int i = 0; i < f->adj.size(); i++) {
			if (f->adj[i]->d < f->d + f->adj[i]->energy && f->d + f->adj[i]->energy > 0) { //如果走過去後的總能量大於上個點的能量嘉進這個點的能量 而且大於零
				f->adj[i]->d = f->d + f->adj[i]->energy;
				f->adj[i]->breadth = f->breadth + 1; //增加寬度
				q.push(f->adj[i]);
			}
		}
	}
	return map[map.size() - 1]->d > 0;

}
#include <fstream>
int main() {
	ofstream out("t.txt");
	int num;
	while (cin >> num) {
		if (num == -1) return 0;
		vector<node*> map;
		for (int i = 0; i < num + 1; i++) {
			node* nN = new node;
			nN->d = INT_MIN;
			nN->breadth = INT_MAX;
			nN->canArrive.clear();
			map.push_back(nN);
		}
		int doorNum;
		for (int i = 0; i < num; i++) {
			cin >> map[i + 1]->energy >> doorNum;
			int dor;
			for (int j = 0; j < doorNum; j++) {
				cin >> dor;
				map[i + 1]->adj.push_back(map[dor]);
			}
		}

		for (int i = 1; i < map.size(); i++)
			bfs(map[i]); //判斷這個點能夠走到哪些點 用於碰到正圈判斷能否到最後一個點

		if (SortestPath(map)) 
			cout << "winnable\n";
		else 
			cout << "hopeless\n";
	}
}