#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
using namespace std;
ofstream out("o.txt");
class Graph_FlowNetWorks {
private:
	int num_vertex;
	std::vector<std::vector<int>> AdjMatrix;
public:
	void outputMatrix() {
		for (int i = 0; i < num_vertex; i++) {
			for (int j = 0; j < num_vertex; j++) {
				cout << AdjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	Graph_FlowNetWorks() :num_vertex(0) {};
	Graph_FlowNetWorks(int n);
	void AddEdge(int from, int to, int capacity);
	void FordFulkerson(int source, int termination);
	bool BFSfindExistingPath(vector<vector<int>> graphResidual, int* predecessor, int source, int termination);
	int MinCapacity(vector<vector<int>> graphResidual, int* predecessor, int termination);
	void reset() {
		for (int i = 0; i < num_vertex; i++) {
			AdjMatrix[i].clear();
			AdjMatrix[i].resize(num_vertex);
		}
	}
};
Graph_FlowNetWorks::Graph_FlowNetWorks(int n) :num_vertex(n) {
	// constructor
	AdjMatrix.resize(num_vertex);
	for (int i = 0; i < num_vertex; i++)
		AdjMatrix[i].resize(num_vertex);
}

bool Graph_FlowNetWorks::BFSfindExistingPath(vector<vector<int>> graph, int* predecessor, int s, int t) {
	int* visited = new int[num_vertex];

	for (int i = 0; i < num_vertex; i++) {
		visited[i] = 0;     // 0 表示還沒有被找到
		predecessor[i] = -1;
	}

	queue<int> queue;
	// BFS 從 s 開始, 也可以規定s一律訂成vertex(0)
	queue.push(s);
	visited[s] = 1;
	while (!queue.empty()) {
		int exploring = queue.front();
		for (int j = 0; j < num_vertex; j++) {
			if (graph[exploring][j] != 0 && visited[j] == 0) {
				queue.push(j);
				visited[j] = 1;
				predecessor[j] = exploring;
			}
		}
		queue.pop();
	}
	return (visited[t] == 1);   // 若t有被visited, 表示有path從s到t
								// 也可以用 if (predecessor[t] != -1) 判斷
}

int Graph_FlowNetWorks::MinCapacity(vector<vector<int>> graph, int* predecessor, int t) {
	int min = INT_MAX;      

	// 用predecessor[idx] 和 idx 表示一條edge
	// 找到在從s到t的path上, capacity最小的值, 存入min
	for (int idx = t; predecessor[idx] != -1; idx = predecessor[idx]) {
		if (graph[predecessor[idx]][idx] != 0 && graph[predecessor[idx]][idx] < min) {
			min = graph[predecessor[idx]][idx];
		}
	}
	return min;
}

void Graph_FlowNetWorks::FordFulkerson(int source, int termination) {

	// residual networks的初始狀態等於AdjMatrix, 見圖五(a)
	vector<vector<int>> graphResidual(AdjMatrix);
	int maxflow = 0;
	int* predecessor = new int[num_vertex];
	// BFS finds augmenting path,
	while (BFSfindExistingPath(graphResidual, predecessor, source, termination)) {
		int mincapacity = MinCapacity(graphResidual, predecessor, termination);
		maxflow = maxflow + mincapacity;
		for (int Y = termination; Y != source; Y = predecessor[Y]) {
			// 更新 residual graph
			int X = predecessor[Y];
			graphResidual[X][Y] -= mincapacity;
			graphResidual[Y][X] += mincapacity;
		}
	}
	cout << maxflow;
}
void Graph_FlowNetWorks::AddEdge(int from, int to, int capacity) {
	AdjMatrix[from][to] += capacity;
}
int main() {
	int numb,te=1;
	while (cin >> numb, numb) {
		cout << "Network " << te++ << "\nThe bandwidth is ";
		Graph_FlowNetWorks g11(numb+1);
		int s, e, line;
		cin >> s >> e >> line;
		for (int i = 0; i < line; i++) {
			int a, b,w;
			cin >> a >> b >> w;
			g11.AddEdge(a, b, w);
			g11.AddEdge(b, a, w);
		}
		//g11.outputMatrix();
		g11.FordFulkerson(s, e);
		cout << ".\n\n";
	}
	return 0;
}