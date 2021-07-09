#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f;

int n, m, x[maxn], y[maxn], c[maxn], sa[maxn], rk[maxn], h[maxn], tot;
char s[maxn];

inline double Solve(int L, int R)
{
	if ( L > R ) return 0;
	if ( L == R ) return n - sa[L] + 1;
	int Min = INF, pos;
	REP(i, L + 1, R) if ( h[i] < Min ) { Min = h[i]; pos = i - 1; }
	double a = Solve(L, pos), b = Solve(pos + 1, R), c = h[pos + 1];
	double x = (b - c) / (a + b - c - c);
	return x * (a - c) + c;
}

int main()
{
	freopen("second.in", "r", stdin);
	freopen("second.out", "w", stdout);
	scanf("%s", s + 1); n = str(s + 1);
	m = 122;
    REP(i, 1, n) { x[i] = s[i]; ++ c[x[i]]; }
    REP(i, 1, m) c[i] += c[i - 1];
    for ( int i = n; i >= 1; -- i ) sa[c[x[i]] --] = i;
    for ( int k = 1; k < n; k <<= 1 )
    {
        mem(c); tot = 0;
        REP(i, n - k + 1, n) y[++ tot] = i;
        REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;
        REP(i, 1, n) ++ c[x[i]]; REP(i, 1, m) c[i] += c[i - 1];
        for ( int i = n; i >= 1; -- i ) sa[c[x[y[i]]] -- ] = y[i];
        REP(i, 1, n) y[i] = x[i];
        x[sa[1]] = 1; tot = 1;
        REP(i, 2, n) x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? tot : ++ tot;
        m = tot;
    }
	REP(i, 1, n) rk[sa[i]] = i;
	for ( int i = 1, k = 0; i <= n; ++ i )
	{
		if ( k ) -- k;
		while ( s[i + k] == s[sa[rk[i] - 1] + k] ) ++ k;
		h[rk[i]] = k;
	}
	printf("%.6lf\n", Solve(1, n));
	return 0;
}
