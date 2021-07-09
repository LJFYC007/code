#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 4e6 + 10;

int n, m, p[maxn], Mod, sa[maxn], len[2], x[maxn], y[maxn], c[maxn], tot, M;
char s[maxn], t[2][maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) scanf("%d", &p[i]);
	scanf("%d", &Mod);
	t[0][1] = 'b'; t[1][1] = 'a'; len[0] = len[1] = 1;
	int op = 1;
	REP(i, 2, n)
	{
		REP(j, 1, len[op]) s[j] = t[op][j];
		REP(j, 1, len[op ^ 1]) s[len[op] + j] = t[op ^ 1][j];
		op ^= 1; len[op] += len[op ^ 1];
		REP(j, 1, len[op]) t[op][j] = s[j];
	}
	n = len[op];
	
	M = 128;
	REP(i, 1, n) { x[i] = s[i]; ++ c[x[i]]; }
	REP(i, 1, M) c[i] += c[i - 1];
	for ( int i = n; i >= 1; -- i ) sa[c[x[i]] --] = i;

	for ( int k = 1; k <= n; k <<= 1 ) 
	{
		tot = 0; REP(i, n - k + 1, n) y[++ tot] = i;
		REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;
		REP(i, 0, M) c[i] = 0;		
		REP(i, 1, n) ++ c[x[i]]; REP(i, 1, M) c[i] += c[i - 1];
		for ( int i = n; i >= 1; -- i ) sa[c[x[y[i]]] --] = y[i];

		swap(x, y); 
		tot = x[sa[1]] = 1;
		REP(i, 2, n) 
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? tot : ++ tot;	
		M = tot;
	}

	REP(i, 1, m) printf("%d ", sa[p[i]] % Mod); puts("");
	return 0;
}
