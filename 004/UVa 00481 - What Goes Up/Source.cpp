#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int CeilIndex(vector<int> &A, int tail[], int low, int high, int key)
{
	while (high - low > 1)
	{
		int mid = (high + low) / 2;
		if (A[tail[mid]] >= key)
			high = mid;
		else
			low = mid;
	}

	return high;
}


void LongestIncreasingSubsequence(vector<int> &A,int n)
{
	if (n == 0)
		return;

	int* tail = new int[n + 1]();
	int* prev = new int[n + 1]();

	int length = 1;
	tail[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (A[i] < A[tail[1]])
			tail[1] = i;
		else if (A[i] > A[tail[length]])
		{
			prev[i] = tail[length];
			tail[++length] = i;
		}
		else
		{
			int position = CeilIndex(A, tail, 1, length, A[i]);
			prev[i] = tail[position - 1];
			tail[position] = i;
		}
	}
	vector<int>ans;
	cout << length << endl<<"-\n";
	for (int i = tail[length]; i > 0; i = prev[i])
		ans.push_back(A[i]);
	for (int i = ans.size() - 1; i >= 0; i--)
		cout << ans[i] << endl;
}

#include <fstream>
int main() {
	int num;
	vector<int> A;
	A.push_back(0);
	ifstream in("a.txt");
	while (cin >> num) {
		A.push_back(num);
	}
	LongestIncreasingSubsequence(A, A.size()-1);
}