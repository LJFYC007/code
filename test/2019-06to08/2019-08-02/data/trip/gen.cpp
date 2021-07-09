#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>

using namespace std;

random_device rd;

char file[30];

int rand(int l, int r) { return l + rd() % (r - l + 1); }

int main()
{

	//for(int I = 4; I <= 10; ++I)
	for(int I = 0; I <= 0; ++I)
	{
		sprintf(file, "trip%d.in", I);
		freopen(file, "w", stdout);
		int n = 2000;
		for(int i = 1; i <= n; ++i)
		{
			int opt = rand(1, 6);
			if(opt == 1) cout << 'L';
			if(opt == 2) cout << 'R';
			if(opt > 2) cout << 'B';
		}
		cout << endl;
		cout << rand(1, n) << ' ' << rand(1, n) << endl;
	}

	return 0;
}
