#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <fstream>
#include<set>
using namespace std;
int R, C, M, N, odd, even;
struct point {
	int x, y;
	int canVisitNum;
	bool canRun;
	bool visited;
	bool pool;
};

vector<point*> finPoint(vector<vector<point>>& map, int x, int y) {
	vector<point*> retur;
	set<point*> Set;
	int a1 = x - M, a2 = x + M, b1 = y - N, b2 = y + N;
	if (a1 >= 0 && a1 < R && b1>=0 && b1 < C && map[a1][b1].pool==false && !(Set.count(&map[a1][b1]))) {
		Set.insert(&map[a1][b1]);
		retur.push_back(&map[a1][b1]);
	}
	if (a1 >= 0 && a1 < R && b2>=0 && b2 < C && map[a1][b2].pool == false && !(Set.count(&map[a1][b2]))) {
		Set.insert(&map[a1][b2]);
		retur.push_back(&map[a1][b2]);
	}
	if (a2 >= 0 && a2 < R && b1>=0 && b1 < C && map[a2][b1].pool == false && !(Set.count(&map[a2][b1]))) {
	
		Set.insert(&map[a2][b1]);
		retur.push_back(&map[a2][b1]);
	}
	if (a2 >= 0 && a2 < R && b2>=0 && b2 < C && map[a2][b2].pool == false && !(Set.count(&map[a2][b2]))) {
		
		Set.insert(&map[a2][b2]);
		retur.push_back(&map[a2][b2]);
	}
	a1 = x - N, a2 = x + N, b1 = y - M, b2 = y + M;
	if (a1 >= 0 && a1 < R && b1 >= 0 && b1 < C && map[a1][b1].pool == false && !(Set.count(&map[a1][b1]))) {
		Set.insert(&map[a1][b1]);
		retur.push_back(&map[a1][b1]);
	}
	if (a1 >= 0 && a1 < R && b2 >= 0 && b2 < C && map[a1][b2].pool == false && !(Set.count(&map[a1][b2]))) {
		Set.insert(&map[a1][b2]);
		retur.push_back(&map[a1][b2]);
	}
	if (a2 >= 0 && a2 < R && b1 >= 0 && b1 < C && map[a2][b1].pool == false && !(Set.count(&map[a2][b1]))) {

		Set.insert(&map[a2][b1]);
		retur.push_back(&map[a2][b1]);
	}
	if (a2 >= 0 && a2 < R && b2 >= 0 && b2 < C && map[a2][b2].pool == false && !(Set.count(&map[a2][b2]))) {

		Set.insert(&map[a2][b2]);
		retur.push_back(&map[a2][b2]);
	}
	return retur;
}

void dfs(vector<vector<point>> &map, int x, int y) {
	map[x][y].visited = true;
	vector<point*> adj = finPoint(map, x, y);
	map[x][y].canVisitNum = adj.size();
	if (adj.size() % 2 == 0) even++;
	else odd++;
	for (int i = 0; i < adj.size(); i++) {
		if (adj[i]->visited == false) {
			dfs(map, adj[i]->x, adj[i]->y);
		}
	}
}

int main() {
	int cas, coun = 1;
	ofstream out("o.txt");
	cin >> cas;
	while (cas--) {
		odd = even = 0;
		cin >> R >> C >> M >> N;
		vector<vector<point>> map;
		map.resize(R);
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				point n;
				n.canRun = n.visited = n.pool = false;
				n.canVisitNum = 0;
				n.x = i; n.y = j;
				map[i].push_back(n);
			}
		}
		int waterNum;
		cin >> waterNum;
		for (int i = 0; i < waterNum; i++) {
			int a, b;
			cin >> a >> b;
			map[a][b].pool = true;
		}
		dfs(map, 0, 0);
		cout <<"Case "<< coun++ << ": " << even << " " << odd << endl;
	}
}