/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年02月17日 星期三 09时14分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], ans, p[maxn];

int main()
{
    freopen("sort.in", "r", stdin);
    freopen("sort1.out", "w", stdout);
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d", &a[i]); p[i] = i; }
	do
	{
		int x = a[p[1]];
		REP(i, 2 ,n) x %= a[p[i]];
		ans = max(ans, x);
	} while ( next_permutation(p + 1, p + n + 1) );
	printf("%d\n", ans);
    return 0;
}
