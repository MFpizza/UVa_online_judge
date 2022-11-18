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
bool SortestPath(vector<node*> map) { //��j�� �̤p���|
	map[1]->d = 100; //�D�زĤ@���I�n100��q
	map[1]->breadth = 0; //�ΨӧP�_����
	queue<node*> q;
	q.push(map[1]);

	node* f = NULL;
	while (!q.empty()) {
		f = q.front();
		q.pop();

		if (f == map[map.size() - 1])
			return true;
		else if (f->breadth > map.size() - 2) { //�W�L�F�ܥN��W�L�O���j��
			if (f->canArrive.count(map[map.size() - 1])) //���馳�S����̫�@���I ���N�^��true
				return true;
			else //�S���N���ΦA�P�_
				f->d = INT_MAX;
			continue;
		}

		for (int i = 0; i < f->adj.size(); i++) {
			if (f->adj[i]->d < f->d + f->adj[i]->energy && f->d + f->adj[i]->energy > 0) { //�p�G���L�h�᪺�`��q�j��W���I����q�Ŷi�o���I����q �ӥB�j��s
				f->adj[i]->d = f->d + f->adj[i]->energy;
				f->adj[i]->breadth = f->breadth + 1; //�W�[�e��
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
			bfs(map[i]); //�P�_�o���I�����������I �Ω�I�쥿��P�_��_��̫�@���I

		if (SortestPath(map)) 
			cout << "winnable\n";
		else 
			cout << "hopeless\n";
	}
}