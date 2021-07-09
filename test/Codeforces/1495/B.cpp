/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月10日 星期三 20时18分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, p[maxn], pre[maxn], suf[maxn], Min[maxn], Max[maxn], ans, np[maxn], ns[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &p[i]);
	int len = 1; pre[1] = Min[1] = np[1] = 1;
	REP(i, 2, n) 
	{
		pre[i] = pre[i - 1];
		if ( p[i] > p[i - 1] ) ++ pre[i]; else pre[i] = 1;
		if ( p[i] < p[i - 1] ) ++ len; else len = 1;
		Min[i] = max(Min[i - 1], max(pre[i], len));
		np[i] = len;
	}
	len = 1; suf[n] = Max[n] = ns[n] = 1;
	for ( int i = n - 1; i >= 1; -- i ) 
	{
		suf[i] = suf[i + 1];
		if ( p[i] > p[i + 1] ) ++ suf[i]; else suf[i] = 1;
		if ( p[i] < p[i + 1] ) ++ len; else len = 1;
		Max[i] = max(Max[i + 1], max(suf[i], len));
		ns[i] = len;
	}

	REP(i, 1, n)
		if ( pre[i] == suf[i] && (pre[i] & 1) && max(Min[i - pre[i] + 1], Max[i + suf[i] - 1]) < pre[i] ) 
			++ ans;
	printf("%d\n", ans);
    return 0;
}
