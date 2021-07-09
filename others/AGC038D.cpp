/***************************************************************
	File name: AGC038D.cpp
	Author: ljfcnyali
	Create time: 2021年07月02日 星期五 09时46分39秒
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

int n, m, q, cnt, num, col[maxn], f[maxn];
pii a[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &q);
	REP(i, 1, n) f[i] = i;
	num = n;
	if ( m < n - 1 ) { puts("No"); return 0; } 
	REP(i, 1, q)
	{
		int u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
		++ u; ++ v;
		if ( !w ) 
		{ 
			int fx = find(u), fy = find(v);
			if ( fx != fy ) { f[fx] = fy; -- num; }
		}
		else a[++ cnt] = pii(u, v);
	}
	REP(i, 1, cnt) if ( find(a[i].first) == find(a[i].second) ) { puts("No"); exit(0); }
	m -= n - num;
	if ( !cnt && (m < num - 1 || m > num * (num - 1) / 2) ) { puts("No"); return 0; } 
	if ( cnt && (m < num || m > num * (num - 1) / 2) ) { puts("No"); return 0; } 
	puts("Yes");
    return 0;
}
