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
	Graph_FlowNetWorks() :num_vertex(0) {};
	Graph_FlowNetWorks(int n);
	void AddEdge(int from, int to, int capacity);
	void FordFulkerson(int source, int termination, int temp);
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
	int min = 15;      // 確保min會更新, 假設graph上的capacity都小於15

	// 用predecessor[idx] 和 idx 表示一條edge
	// 找到在從s到t的path上, capacity最小的值, 存入min
	for (int idx = t; predecessor[idx] != -1; idx = predecessor[idx]) {
		if (graph[predecessor[idx]][idx] != 0 && graph[predecessor[idx]][idx] < min) {
			min = graph[predecessor[idx]][idx];
		}
	}
	return min;
}

void Graph_FlowNetWorks::FordFulkerson(int source, int termination, int temp) {

	// residual networks的初始狀態等於AdjMatrix, 見圖五(a)
	vector<vector<int>> graphResidual(AdjMatrix);
	int maxflow = 0;
	int* predecessor = new int[num_vertex];
	char ans[10] = { '_','_','_' ,'_' ,'_' ,'_' ,'_' ,'_' ,'_' ,'_' };
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
	if (maxflow < temp)
		cout << "!\n";
	else {
		for (int i = 27; i < 37; i++) {
			char a='_';
			for (int j = 1; j < 27; j++) {
				if (graphResidual[i][j] == 1)
				{
					a = j - 1 + 'A';
					break;
				}
			}
			cout << a;
		}
		cout << endl;
	}
}
void Graph_FlowNetWorks::AddEdge(int from, int to, int capacity) {
	AdjMatrix[from][to] = capacity;
}
//0=start 1-26=A-Z 27-36=0-9 37=end
int main() {
	string s;
	Graph_FlowNetWorks g11(38);
	for (int i = 27; i < 37; i++)
		g11.AddEdge(i, 37, 1);
	int tem = 0;
	while (getline(cin, s)) {

		if (s == "" || s[0] == EOF) {
			g11.FordFulkerson(0, 37, tem);    // 指定source為vertex(0), termination為vertex(37)
			if (s[0] == EOF)
				break;
			g11.reset();
			for (int i = 27; i < 37; i++)
				g11.AddEdge(i, 37, 1);
			tem = 0;

		}
		else {
			g11.AddEdge(0, s[0] - 'A' + 1, s[1] - '0');
			tem += s[1] - '0';
			for (int i = 3; i < s.size() - 1; i++) {
				g11.AddEdge(s[0] - 'A' + 1, s[i] - '0' + 27, 1);
			}
		}
	}
	g11.FordFulkerson(0, 37, tem);
	return 0;
}