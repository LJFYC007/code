/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年06月19日 星期六 08时33分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
    freopen("input.txt", "w", stdout);
	int n = 100000, m = 1000000; srand(time(0));
	printf("%d\n", n); REP(i, 1, n) printf("%d ", rand() % 1000 + 1); puts("");
	printf("%d\n", m); 
	REP(i, 1, m) 
	{
		int l = rand() % n + 1, r = rand() % n + 1;
		if ( l > r ) swap(l, r);
		printf("%d %d %d\n", l, r, rand() % (n - (r - l + 1) + 1) + 1);
	}

    return 0;
}
