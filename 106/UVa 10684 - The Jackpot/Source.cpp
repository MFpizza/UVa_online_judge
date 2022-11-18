#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
ofstream out("o.txt");
void findMaxSubArray(vector<int>vec) {
	vector<int> localMax(vec.size());
	localMax[1] = vec[1];
	for (int i = 2; i < vec.size(); i++)
		localMax[i] = max(localMax[i - 1] + vec[i], vec[i]);
	int max=vec[1];
	for (int i = 2; i < vec.size(); i++)
		if (max < localMax[i])
			max = localMax[i];
	if (max <= 0)
		cout << "Losing streak.\n";
	else
		cout << "The maximum winning streak is "<<max<<"."<< endl;
}

int main() {
	int num;
	while (cin >> num) {
		if (num == 0) break;
		vector<int>vec;
		vec.push_back(0);
		int num2;
		for (int i = 0; i < num; i++) {
			cin >> num2;
			vec.push_back(num2);
		}
		findMaxSubArray(vec);
	}
}