#include <iostream>
#include <queue>
#include <climits>
using namespace std;

int row, col;
struct node {
	bool operator<(const node& b)const {
		return b.lon < lon;
	}
	int d;
	string color;
	int lon;
	int row, col;
};
struct cmp {
	bool operator()(const node* a, const node* b)const {
		return b->lon < a->lon;
	}
};
priority_queue<node*, vector<node*>, cmp> q;

priority_queue<node> resetQ(vector<vector<node>>map) {
	priority_queue<node> newQ;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j].color == "w") {
				newQ.push(map[i][j]);
			}
		}
	}
	return newQ;
}
void showMap(vector<vector<node*>>map);

void shortedPathAlgorithm(vector<vector<node*>>& Map) {
	Map[0][0]->lon = Map[0][0]->d;
	q.push(Map[0][0]);
	int total = row * col;
	while (total--) {
		node* front=NULL;
		while (!q.empty()) {
			front = q.top();
			q.pop();
			if (front->color == "w") break;
			//q = resetQ(Map);
		}
		if (front == NULL || (front->row == row - 1 && front->col == col - 1))
			return;
		Map[front->row][front->col]->color = "b";
		//node* tem = &Map[front.row][front.col + 1];
		if (front->col + 1 < col && Map[front->row][front->col + 1]->lon > front->lon + Map[front->row][front->col + 1]->d) {
			Map[front->row][front->col + 1]->lon = front->lon + Map[front->row][front->col + 1]->d;
			q.push(Map[front->row][front->col + 1]);
			//showMap(Map);
		}
		//tem = &Map[front.row][front.col -1];
		if (front->col - 1 >= 0 && Map[front->row][front->col - 1]->lon > front->lon + Map[front->row][front->col - 1]->d) {
			Map[front->row][front->col - 1]->lon = front->lon + Map[front->row][front->col - 1]->d;
			q.push(Map[front->row][front->col - 1]);
			//showMap(Map);
		}
		//tem = &Map[front.row+1][front.col ];
		if (front->row + 1 < row && Map[front->row + 1][front->col]->lon > front->lon + Map[front->row + 1][front->col]->d) {
			Map[front->row + 1][front->col]->lon = front->lon + Map[front->row + 1][front->col]->d;
			q.push(Map[front->row + 1][front->col]);
			//showMap(Map);
		}
		//tem = &Map[front.row-1][front.col];
		if (front->row - 1 >= 0 && Map[front->row - 1][front->col]->lon > front->lon + Map[front->row - 1][front->col]->d) {
			Map[front->row - 1][front->col]->lon = front->lon + Map[front->row - 1][front->col]->d;
			q.push(Map[front->row - 1][front->col]);
			//showMap(Map);
		}
		
	}
	
}
#include <iomanip>
void showMap(vector<vector<node*>>map) {
	cout << "---------------------------------------------------\n";
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			cout << setw(12) << map[i][j]->lon << " ";
		}
		cout << endl;
	}
}
#include <fstream>
int main() {
	int cas;
	ofstream out("p.txt");
	cin >> cas;
	while (cas--) {
		while (!q.empty()) {
			q.pop();
		}
		cin >> row >> col;
		vector<vector<node*>> map;
		for (int i = 0; i < row; i++) {
			vector<node*> newC;
			int num;
			for (int j = 0; j < col; j++) {
				cin >> num;
				node* newN=new node;
				newN->d = num;
				newN->color = "w";
				newN->lon = INT_MAX;
				newN->row = i;
				newN->col = j;
				//q.push(&newN);
				newC.push_back(newN);
			}
			map.push_back(newC);
		}
		//showMap(map);
		while (!q.empty())
			q.pop();
		shortedPathAlgorithm(map);
		
		cout << map[row - 1][col - 1]->lon << endl;
	}
}