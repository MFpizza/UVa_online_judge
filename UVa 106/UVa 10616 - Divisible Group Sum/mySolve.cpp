#include <iostream>
#include <cstring>

using namespace std;

int main()//ppt�̫ᨺ�Ӥ@���}�C���ݮi�A���@���񪺬O�ƭȡA�o�̪��ĤG���O�������F�h�֭ӼƦr�A�]�N�O���U���O��Ҧ����i�ೣ��X��
{
	int N, Q, Case_ = 1;
	int data[200], mod[200];
	long long int ans[201][11];
	while (cin >> N >> Q && N&& Q)
	{
		cout << "SET " << Case_++ << ":" << endl;
		for (int i = 0; i < N; i++)
			cin >> data[i];
		for (int i = 0; i < Q; i++)
		{
			memset(ans, 0, sizeof(ans));
			int D, M;
			cin >> D >> M;
			for (int j = 0; j < N; j++)
				mod[j] = (((data[j] % D) + D) % D); //���t������l��

			ans[0][0] = 1;
			for (int j = 0; j < N; j++)
				for (int h = M; h > 0; h--)
					for (int k = 200; k >= mod[j]; k--)
						ans[k][h] += ans[k - mod[j]][h - 1];
			long long int sum = 0;
			for (int j = 0; j <= 200; j += D)
				sum += ans[j][M];
			cout << "QUERY " << i + 1 << ": " << sum << endl;
		}
	}
	return 0;
}