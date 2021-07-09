/***************************************************************
	File name: HaHa
	Author: ljfcnyali
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
	srand(time(0));
	int n = 100000, q = 100000; printf("%d %d\n", n, q);
	REP(i, 0, n - 1) a[i] = i;
	random_shuffle(a, a + n);
	REP(i, 0, n - 1) printf("%d ", a[i]); puts("");
	REP(i, 1, q)
	{
		int l = rand() % (n - 1), r = rand() % (n - 1);
		if ( l > r ) swap(l, r);
		int x = r + rand() % (n - 1 - r) + 1;
		int y = r + rand() % (n - 1 - r) + 1;
		printf("%d %d %d %d\n", l, r, min(x, y), max(x, y));
	}
    return 0;
}
