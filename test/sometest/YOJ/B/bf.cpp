/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 13时50分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn], b[maxn], c[maxn], d[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1, m) { scanf("%lld", &b[i]); d[i] = b[i]; } 
	REP(i, 1, n) scanf("%lld%lld", &a[i], &c[i]);
	REP(i, 1, n)
	{
		REP(j, 1, m) d[j] = b[j];
		int len = 0, now = i;
		while ( d[c[now]] >= a[now] ) 
		{
			d[c[now]] -= a[now]; ++ len;
			now = (now == n ? 1 : now + 1);
		}
		printf("%lld ", len);
	}
	puts("");
    return 0;
}
