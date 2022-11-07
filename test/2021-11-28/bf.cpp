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
#define ull unsigned long long

const int maxn = 3e5 + 10;

int n, m, g[maxn], c[1010][1010]; ull a[maxn];
bool f[1010][1010];

inline int lowbit(int x) { return x & -x; } 
inline void add(int pos, int x, int val) { for ( int i = x; i <= 1000; i += lowbit(i) ) c[pos][i] += val; }
inline int ask(int pos, int x) { int ret = 0; for ( int i = x; i > 0; i -= lowbit(i) ) ret += c[pos][i]; return ret; }

inline void Solve(int i)
{
	g[i] = 0; int L = 1, R = 1000;
	while ( L <= R ) 
	{
		int Mid = (L + R) >> 1;
		if ( ask(i, Mid) == Mid ) { g[i] = Mid; L = Mid + 1; }
		else R = Mid - 1;
	}
}

int main()
{
    freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	while ( m -- ) 
	{
		int op, l, r, x; scanf("%d", &op);
		if ( op == 1 )
		{
			scanf("%d%d%d", &l, &r, &x);
			REP(i, l, r) if ( !f[i][x] ) { f[i][x] = true; add(i, x, 1); Solve(i); }
		}
		if ( op == 2 ) 
		{
			scanf("%d%d%d", &l, &r, &x);
			REP(i, l, r) if ( f[i][x] ) { f[i][x] = false; add(i, x, -1); Solve(i); }
		}
		if ( op == 3 ) 
		{
			scanf("%d%d", &l, &r); ull w; scanf("%llu", &w);
			int Min = 1010;
			REP(i, l, r) Min = min(Min, g[i]);
			REP(i, l, r) if ( g[i] == Min ) a[i] += w;
		}
		if ( op == 4 ) 
		{
			scanf("%d%d", &l, &r);
			ull ret = 0; REP(i, l, r) ret += a[i];
			printf("%llu\n", ret);
		}
	}
    return 0;
}
