/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月11日 星期四 16时59分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[maxn];

int main()
{
    freopen("input.txt", "w", stdout);
	int n = 10; printf("%d\n", n); srand(time(0));
	REP(i, 1, n) { a[i] = rand() % 10 + 1; printf("%d ", a[i]); }
	puts("");
	int q = 3; printf("%d\n", q);
	REP(i, 1, q) 
	{
		int x = rand() % n + 1;
		printf("%d %d\n", x, rand() % a[x]);
	}
    return 0;
}
