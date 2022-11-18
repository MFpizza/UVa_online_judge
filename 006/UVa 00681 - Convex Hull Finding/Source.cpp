#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
ofstream out("t.txt");
// P為平面上散佈的點。設定為10點。
// CH為凸包上的頂點。設定為逆時針方向排列。可以視作一個stack。

struct Point { int x, y; };
Point* P, * ans;
// 向量OA叉積向量OB。大於零表示從OA到OB為逆時針旋轉。小於0代表向右轉 叉積=外積
int cross(Point o, Point a, Point b)
{
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// 小於。用以找出最低最左邊的點。
bool compare_position(Point a, Point b)
{
	return (a.y < b.y) || (a.y == b.y && a.x < b.x);
}

int length2(Point a, Point b) //兩點路徑平方
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
// 小於。以P[0]當中心點做角度排序，角度由小排到大（即逆時針方向）。
// 角度相同時，距離較離中心點較近的點排前面。
bool compare_angle(Point a, Point b)
{
	// 加入角度相同時，距離長度的判斷。
	int c = cross(P[0], a, b);
	return c > 0 || (c == 0 && (length2(P[0], a) < length2(P[0], b)));
}

void Graham_scan(int num)
{
	// 把y最小或 y相同x最左的點放到 P[0]
	swap(P[0], *min_element(P, P + num-1, compare_position));

	// 其餘各點依相對p[0]角度排序。O(NlogN)
	sort(P + 1, P + num-1, compare_angle);

	// 直接把中心點作為起點，開始包覆，逆時針方向。O(N)
	P[num-1] = P[0];    // 讓程式方便處理包至最後一點的情況。
	int m = 0;      // m 為凸包頂點數目
	for (int i = 0; i < num; ++i)
	{
		// 掃除凹陷的點
		while (m >= 2 && cross(ans[m - 2], ans[m - 1], P[i]) <= 0) m--;
		// 添加新的點
		ans[m++] = P[i];
	}
	out << m << endl;
	for (int i = 0; i < m; i++) {
		out << ans[i].x << " " << ans[i].y << endl;
	}
}

int main() {
	int cas;
	cin >> cas;
	cout << cas << endl;
	while (cas--) {
		int nodeNum;
		cin >> nodeNum;
		nodeNum++;
		P = new Point[nodeNum];
		ans = new Point[nodeNum];
		for (int i = 0; i < nodeNum-1; i++) {
			cin >> P[i].x >> P[i].y;
		}
		Graham_scan(nodeNum);
		if (cas)
		{
			cin >> nodeNum;
			cout << nodeNum<<endl;
		}
	}
}