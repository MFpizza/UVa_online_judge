#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;
struct edge {
	int fromNode, toNode, weight;
};
struct node {
	long long int d;

};
bool bellman(vector<node*> map, vector<edge*> Edge) {
	map[0]->d = 0;
	for (int i = 1; i <= map.size() - 1; i++)
		for (int i = 0; i < Edge.size(); i++)
			if (map[Edge[i]->toNode]->d > map[Edge[i]->fromNode]->d + Edge[i]->weight)
				map[Edge[i]->toNode]->d = map[Edge[i]->fromNode]->d + Edge[i]->weight;

	for (int i = 0; i < Edge.size(); i++)
		if (map[Edge[i]->toNode]->d > map[Edge[i]->fromNode]->d + Edge[i]->weight)
			return false;
	return true;
}
int main() {
	int cas;
	cin >> cas;
	while (cas--) {
		vector<node*> map; vector<edge*> Edge;
		int nN, mN;
		cin >> nN >> mN;
		for (int i = 0; i < nN; i++) {
			node* nN = new node;
			nN->d = INT_MAX;
			map.push_back(nN);
		}
		for (int i = 0; i < mN; i++) {
			edge* eD = new edge;
			cin >> eD->fromNode >> eD->toNode >> eD->weight;
			Edge.push_back(eD);
		}
		if (bellman(map, Edge)) cout << "not possible\n";
		else cout << "possible\n";
	}
}