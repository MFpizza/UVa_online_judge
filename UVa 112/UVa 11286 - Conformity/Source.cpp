#include <iostream>
#include <sstream>
#include <map>
using namespace std;
int main() {
	int count;
	while (cin >> count, count) {
		map<string, int> m;
		for (int i = 0; i < count; i++) { 
			int a[5];
			for (int j = 0; j < 5; j++)
				cin >> a[j];
			for (int k = 0; k < 5; k++) //��Ҫ�����ҧ@�ƦC
				for (int j = 0; j < 4; j++)
					if (a[j] > a[j + 1])
					{
						int tem = a[j];
						a[j] = a[j + 1];
						a[j + 1] = tem;
					}
			stringstream ss;
			for (int k = 0; k <5; k++) //�˹L���নstring ��imap
				ss << a[k];

			string input; 
			ss >> input;
			m[input]++;
		}
		int max = m.begin()->second,count=0; //�M��̦h�H�諸�Ҫ��̰��H����Ҫ��`��ܤH��(�i�঳�P�˦h�H ���P�Ҫ��i�� �Ҧ��Ҫ���ܤH�ƭn�[�_��)
		for (map<string, int>::iterator it = m.begin()++; it != m.end(); it++) {
			if (max < it->second) {
				max = it->second;
				count = max;
			}
			else if (max == it->second)
				count += it->second;
		}
		cout << count << endl; //�̰����諸�Ҧ���ܤH��
	}
}