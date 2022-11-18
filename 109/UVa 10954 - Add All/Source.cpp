#include <queue>
#include <iostream>
using namespace std;

int main() {
	int num;
	while (cin >> num,num) {
		priority_queue<int,vector<int>,greater<int>> que;
		int num2;
		for (int i = 0; i < num; i++)
		{
			cin >> num2;
			que.push(num2);
		}
		int all = 0;
		while (!que.empty()) {
			int a = que.top(); que.pop();
			int b = que.top(); que.pop();
			all += (a + b);
			if(!que.empty())
				que.push((a + b));
		}
		cout << all << endl;
	}
}
//https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1895