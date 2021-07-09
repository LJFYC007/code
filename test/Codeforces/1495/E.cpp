/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年03月16日 星期二 08时33分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long 
typedef long long LL;

const int maxn = 5e6 + 10;
const int maxm = 2e5 + 10;
const int Mod = 1e9 + 7;

int n, m, a[maxn], p[maxm], seed, base, num[3], c[maxn];
struct node { int l, r, val, num; } b[maxn];
bool t[maxn];

inline int rnd() { int ret = seed; seed = (seed * base + 233) % Mod; return ret; } 

inline int nxt(int x) { return x == n ? 1 : x + 1; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1, m)
	{
		int k, b, w; scanf("%lld%lld%lld%lld", &p[i], &k, &b, &w);
		seed = b; base = w; 
		REP(j, p[i - 1] + 1, p[i]) { t[j] = rnd() % 2; a[j] = rnd() % k + 1; }
	}

	if ( t[1] == t[n] ) { -- a[1]; ++ c[1]; } 
	int now = t[n]; m = 0;
	REP(i, 1, n)
	{
		if ( t[i] == now ) continue ; 
		int j = i, sum = a[i]; while ( nxt(j) != i && t[nxt(j)] == t[i] ) { j = nxt(j); sum += a[j]; } 
		b[++ m] = {i, j, sum}; now = t[j]; num[now] += sum;
		if ( j < i ) break ; i = j;
	}
	int op = num[0] < num[1] ? 0 : 1, sum = t[b[1].l] == op ? 0 : 1;
	if ( !m ) { b[++ m] = {1, n, 0}; REP(i, 1, n) b[m].val += a[i]; goto Next ; }

	REP(i, 1, m)
		if ( t[b[i].l] == op ) { sum += b[i].val; b[i].num += b[i].val; b[i].val = 0; } 
		else { b[i].num += min(sum, b[i].val); sum -= b[i].num; b[i].val -= b[i].num; } 
	REP(i, 1, m) { b[i].num += min(sum, b[i].val); sum -= min(sum, b[i].val); } 

Next : ; 
	int ans = 1;
	REP(i, 1, m) 
	{
		int x = b[i].l;
		while ( 1 ) 	
		{
			int t = min(b[i].num, a[x]); c[x] += t; b[i].num -= t;
			ans = ans * (((c[x] ^ x * x) + 1) % Mod) % Mod;
			if ( x == b[i].r ) break ; 
			x = nxt(x);
		}
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
