/***************************************************************
	File name: ARC102F.cpp
	Author: ljfcnyali
	Create time: 2021年06月18日 星期五 15时40分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;

int n, a[maxn], c[maxn], m;
bool b[maxn], pre[maxn], suf[maxn], f[maxn], g[maxn];

inline bool Solve(int l, int r)
{
	m = 0; REP(i, l, r) if ( !b[i] ) c[++ m] = a[i];
	int Min = n + 1, Max = 0;
	REP(i, 1, m) { Min = min(Min, c[i]); Max = max(Max, c[i]); }
	if ( Min < l || Max > r ) return false;

	REP(i, 1, m)
	{
		int x = c[i]; f[i] = pre[x];
		while ( x >= l && !pre[x] ) pre[x --] = true;
	}
	for ( int i = m; i >= 1; -- i ) 
	{
		int x = c[i]; g[i] = suf[x];
		while ( x <= r && !suf[x] ) suf[x ++] = true;
	}

	// REP(i, 1, m) cout << c[i] << " "; cout << endl;
	// REP(i, 1, m) cout << f[i] << " "; cout << endl;
	// REP(i, 1, m) cout << g[i] << " "; cout << endl;

	REP(i, 1, m) if ( f[i] && g[i] ) return false;
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) { scanf("%d", &a[i]); b[i] = a[i] == i; }
	
	int now = 1;
	REP(i, 1, n - 1) if ( b[i] == b[i + 1] ) 
	{
		if ( !Solve(now, i) ) { puts("No"); return 0; } 
		now = i + 1;
	}
	if ( !Solve(now, n) ) { puts("No"); return 0; } 
	puts("Yes");
    return 0;
}
