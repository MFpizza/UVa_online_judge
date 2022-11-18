#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
ofstream out("t.txt");
// P�������W���G���I�C�]�w��10�I�C
// CH���Y�]�W�����I�C�]�w���f�ɰw��V�ƦC�C�i�H���@�@��stack�C

struct Point { int x, y; };
Point* P, * ans;
// �V�qOA�e�n�V�qOB�C�j��s��ܱqOA��OB���f�ɰw����C�p��0�N��V�k�� �e�n=�~�n
int cross(Point o, Point a, Point b)
{
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// �p��C�ΥH��X�̧C�̥��䪺�I�C
bool compare_position(Point a, Point b)
{
	return (a.y < b.y) || (a.y == b.y && a.x < b.x);
}

int length2(Point a, Point b) //���I���|����
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
// �p��C�HP[0]�����I�����ױƧǡA���ץѤp�ƨ�j�]�Y�f�ɰw��V�^�C
// ���׬ۦP�ɡA�Z�����������I�����I�ƫe���C
bool compare_angle(Point a, Point b)
{
	// �[�J���׬ۦP�ɡA�Z�����ת��P�_�C
	int c = cross(P[0], a, b);
	return c > 0 || (c == 0 && (length2(P[0], a) < length2(P[0], b)));
}

void Graham_scan(int num)
{
	// ��y�̤p�� y�ۦPx�̥����I��� P[0]
	swap(P[0], *min_element(P, P + num-1, compare_position));

	// ��l�U�I�̬۹�p[0]���ױƧǡCO(NlogN)
	sort(P + 1, P + num-1, compare_angle);

	// �����⤤���I�@���_�I�A�}�l�]�СA�f�ɰw��V�CO(N)
	P[num-1] = P[0];    // ���{����K�B�z�]�̫ܳ�@�I�����p�C
	int m = 0;      // m ���Y�]���I�ƥ�
	for (int i = 0; i < num; ++i)
	{
		// �����W�����I
		while (m >= 2 && cross(ans[m - 2], ans[m - 1], P[i]) <= 0) m--;
		// �K�[�s���I
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