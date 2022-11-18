#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits>
using namespace std;
int num;
vector<vector<int>> capacity;

bool bfs(vector<vector<int>> residual,int* predecessor, int source, int termination) {
	bool* visit = new bool[num];
	for (int i = 0; i < num; i++) {
		visit[i] = false;
		predecessor[i] = -1;
	}
	queue<int> q;
	visit[source] = true;
	q.push(source);
	while (!q.empty()) {
		int front = q.front();
		q.pop();
		for (int i = 0; i < num; i++) {
			if (residual[front][i] != 0 && visit[i] == false)
			{
				q.push(i);
				visit[i] = true;
				predecessor[i] = front;
			}
		}
	}
	return visit[termination];
}

void ffAlgorithm(int source, int termination) {
	vector<vector<int>> residual(capacity); //��residual = capacity 
	int maxflow = 0;
	int* predecessor = new int[num]; //�̭��񪺬O�C�Ӧ�m���e�@�Ӧ�m
	while (bfs(residual, predecessor, source,termination)) { //bfs��X���|�|�� dfs�٧�
		int min = INT_MAX; //��X�o�����|�W���̤p��
		for (int i = termination; i != source; i = predecessor[i]) {
			if (residual[predecessor[i]][i] && residual[predecessor[i]][i] < min)
				min = residual[predecessor[i]][i];
		}
		maxflow += min;
		for (int i = termination; i != source; i = predecessor[i]) {
			residual[predecessor[i]][i] -= min; // capacity�S�� ���q�L��flow�h�F min �ҥH residual ���ƭȷ|��min �]�� residual.c = c(u,v)-f(u,v)
			residual[i][predecessor[i]] += min;// flow�ܦh�F �ҥH residual �ƭȷ|�h min �]�� residual.c = f(u,v) 
		}
	}
	cout << maxflow;
}

int main() {
	int te = 1;
	while (cin >> num,num) {
		cout << "Network " << te++ << "\nThe bandwidth is ";
		num++;
		for (int i = 0; i < capacity.size(); i++)
			capacity[i].clear();
		capacity.clear();

		capacity.resize(num);
		for (int i = 0; i < num; i++) {
			capacity[i].resize(num);
		}
		int s, e, line;
		cin >> s >> e >> line;
		int a, b, capa;
		while (line--) {
			cin >> a >> b >> capa;
			capacity[a][b] += capa;
			capacity[b][a] += capa;
		}
		ffAlgorithm(s, e);
		cout << ".\n\n";
	}
}