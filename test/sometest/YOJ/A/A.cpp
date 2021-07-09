/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 13时32分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn], b[maxn], sum;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m)
	{
		int x, y; scanf("%d%d", &x, &y);
		++ a[x]; ++ b[y];
	}
	REP(i, 1, n) sum += max(0, a[i] - 2);
	REP(i, 1, n) sum += max(0, b[i] - 2);
	printf("%d\n", sum);
    return 0;
}
