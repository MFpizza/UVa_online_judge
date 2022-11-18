#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int row, col;

struct node {
	string color;
	int d;
	int col;
	int row;
};

void bfs(vector<vector<node*>>& Map, node* ptr) {
	queue<node*> q;
	ptr->d = 0;
	q.push(ptr);
	while (!q.empty()) {
		node* front = q.front();
		q.pop();
		if (front->col + 1 < col && Map[front->row][front->col + 1]->color == "white") {
			Map[front->row][front->col + 1]->color = "gray";
			Map[front->row][front->col + 1]->d = front->d + 1;
			q.push(Map[front->row][front->col + 1]);
		}
		if (front->col - 1 >= 0 && Map[front->row][front->col - 1]->color == "white") {
			Map[front->row][front->col - 1]->color = "gray";
			Map[front->row][front->col - 1]->d = front->d + 1;
			q.push(Map[front->row][front->col - 1]);
		}
		if (front->row + 1 < row && Map[front->row + 1][front->col]->color == "white") {
			Map[front->row + 1][front->col]->color = "gray";
			Map[front->row + 1][front->col]->d = front->d + 1;
			q.push(Map[front->row + 1][front->col]);
		}
		if (front->row - 1 >= 0 && Map[front->row - 1][front->col]->color == "white") {
			Map[front->row - 1][front->col]->color = "gray";
			Map[front->row - 1][front->col]->d = front->d + 1;
			q.push(Map[front->row - 1][front->col]);
		}
		front->color = "black";
	}
}

int main() {

	while (cin >> row >> col) {
		if (row == 0 && col == 0) break;
		vector<vector<node*>>Map;
		for (int i = 0; i < row; i++) {
			vector<node*> newRow;
			for (int j = 0; j < col; j++) {
				node* newN = new node;
				newN->color = "white";
				newN->col = j;
				newN->row = i;
				newN->d = INT_MAX;
				newRow.push_back(newN);
			}
			Map.push_back(newRow);
		}
		int BoobRowNum;
		cin >> BoobRowNum;
		for (int i = 0; i < BoobRowNum; i++) {
			int row1, BombNum, locate;
			char ch;
			cin >> row1 >> BombNum;
			for (int i = 0; i < BombNum; i++) {
				cin >> locate;
				Map[row1][locate]->color = "gray";
			}
		}
		int startRow, startCol, endR, endC;
		cin >> startRow >> startCol;
		cin >> endR >> endC;
		bfs(Map, Map[startRow][startCol]);
		cout << Map[endR][endC]->d << endl;
	}
}