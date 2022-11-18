#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main() {
	int cas, t = 1;
	cin >> cas;
	ofstream out("t.txt");
	while (cas--) {
		int rol, cul, price;
		cin >> rol >> cul >> price;
		vector<vector<int>>arr(rol + 1, vector<int>(cul + 1, 0));
		for (int i = 0; i < rol; i++)
			for (int j = 0; j < cul; j++)
				cin >> arr[i + 1][j + 1];

		vector<vector<int>>sum(rol + 1, vector<int>(cul + 1, 0));
		for (int i = 1; i <= rol; i++)
			for (int j = 1; j <= cul; j++)
				sum[i][j] = arr[i][j] - sum[i - 1][j - 1]
				+ sum[i - 1][j] + sum[i][j - 1];
		/*
		for (int i = 0; i < sum.size(); i++) {
			for (int j = 0; j < sum[i].size(); j++)
				cout << sum[i][j] << ' ';
			cout << endl;
		}*/

		int area = 0, price2 = 0;
		for (int i = 1; i <= rol; i++)
			for (int j = 1; j <= cul; j++)
				for (int k = i; k <= rol; k++)
					for (int l = j; l <= cul; l++) {
						int area2 = (k - i + 1) * (l - j + 1);
						int temp = sum[k][l] - sum[i - 1][l] - sum[k][j - 1] + sum[i - 1][j - 1];
						if (((area2 >= area)) && (sum[k][l] - sum[i - 1][l] - sum[k][j - 1] + sum[i - 1][j - 1] <= price))
						{
							if (area2 > area)
							{
								area = area2;
								price2 = temp;
							}
							else
								price2 = min(price2, temp);
						}
					}
		cout << "Case #" << t++ << ": " << area << " " << price2 << endl;
	}
}