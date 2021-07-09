/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月14日 星期日 08时36分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
// const int M = (1 << 3) + 1;
const int M = (1 << 20) + 1;

int main()
{
    freopen("input.txt", "w", stdout);
	int n = 200000, q = 200000; printf("%d %d\n", n, q);
	// int n = 10, q = 10; printf("%d %d\n", n, q);
	srand(time(0));
	REP(i, 1, n) printf("%d ", rand() % M); puts("");
	REP(i, 1, q)
	{
		int op = rand() % 3 + 1, l = rand() % n + 1, r = rand() % n + 1;
		if ( l > r ) swap(l, r);
		if ( op <= 2 ) printf("%d %d %d %d\n", op, l, r, rand() % M);
		else printf("%d %d %d\n", op, l, r);
	}
    return 0;
}
