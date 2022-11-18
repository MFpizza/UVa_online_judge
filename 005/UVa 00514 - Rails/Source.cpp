#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

int main() {
	int a;
	ofstream out("out.txt");
	while (cin >> a, a) {
		int* b=new int [a];
		while (cin >> b[0]) {
			if (b[0] == 0) break;
			for (int i = 1; i < a; i++)
				cin >> b[i];

			stack<int> sta;
			int c = 0;	
			for (int i = 0; i < a; i++) {
				sta.push(i+1);
				while (!sta.empty()) {
					if (b[c] == sta.top()) {
						sta.pop();
						c++;
					}
					else
						break;
				}
			}
			while (!sta.empty())
			{
				if (b[c] == sta.top()) {
					sta.pop();
					c++;
				}
				else
					break;
			}
			if (!sta.empty())
				cout << "No" << endl;
			else
				cout << "Yes" << endl;
		}
		cout << endl;
	}
}