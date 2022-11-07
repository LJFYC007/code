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
const int INF = 0x3f3f3f3f;

int n, m, a[maxn], b[maxn], f[maxn], g[maxn], l[maxn], p[maxn], ans[maxn];
bool vis[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]); 
	a[++ n] = INF;
	scanf("%d", &m); REP(i, 1, m) scanf("%d", &b[i]);
	sort(b + 1, b + m + 1);

	REP(i, 1, n + 1) f[i] = INF;
	REP(i, 1, n) if ( a[i] != -1 ) 
	{
		int L = 1, R = n, pos = 0;
		while ( L <= R ) 
		{
			int Mid = L + R >> 1;
			if ( f[Mid] < a[i] ) { pos = Mid; L = Mid + 1; } 
			else R = Mid - 1;
		}
		f[pos + 1] = a[i]; g[pos + 1] = i; l[i] = pos + 1; p[i] = g[pos];
	}
	else
	{
		int pos = n;
		for ( int j = m; j >= 1; -- j )
		{
			while ( f[pos] >= b[j] ) -- pos;
			f[pos + 1] = b[j]; g[pos + 1] = i;
		}
	}

	for ( int len = l[n], pos = n, val = a[n]; len >= 1; -- len ) if ( a[pos] != -1 ) 
	{
		if ( a[p[pos]] != -1 ) { pos = p[pos]; val = a[pos]; } 
		else
		{
			int t = lower_bound(b + 1, b + m + 1, val) - b - 1;
			vis[t] = true; pos = p[pos]; val = ans[pos] = b[t];
		}
	}
	else
	{
		for ( int i = pos - 1; i >= 1; -- i ) if ( a[i] != -1 && l[i] == len - 1 && a[i] < val ) 
		{
			pos = i; val = a[i]; 
			goto Next ;
		}
		for ( int i = pos - 1; i >= 1; -- i ) if ( a[i] == -1 ) 
		{
			int t = lower_bound(b + 1, b + m + 1, val) - b - 1;
			vis[t] = true; pos = i; val = ans[pos] = b[t]; 
			goto Next;
		}
		Next : ;
	}

	int pos = 1;
	REP(i, 1, n - 1) if ( a[i] != -1 ) ans[i] = a[i];
	else if ( !ans[i] ) 
	{
		while ( vis[pos] ) ++ pos;
		ans[i] = b[pos]; ++ pos;
	}
	REP(i, 1, n - 1) printf("%d ", ans[i]); puts("");
    return 0;
}
