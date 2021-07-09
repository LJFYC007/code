#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define int long long
#define str(a) strlen ( a ) 
#define pii pair<int, int>
 
const int maxn = 2e5 + 10;
 
int N, n, m, q, t, now, len[maxn];
pii a[maxn];
char ans[maxn][31], s[31];
 
inline void DFS(int n, int lst)
{
	if ( t == a[q].first ) return ; 
	if ( !lst ) 
	{
		++ t;
		while ( t == a[now].first ) 
		{
			int pos = a[now].second; len[pos] = n - 1;
			REP(i, 1, n - 1) ans[pos][i] = s[i];
			++ now;
		}
	}
	if ( n == N + 1 ) return ; 
	REP(i, s[lst + 1] - 'a' + 1, m)
	{
		s[n] = i + 'a' - 1;
		if ( i == s[lst + 1] - 'a' + 1 ) DFS(n + 1, lst + 1);
		else DFS(n + 1, 0);
	}
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &q); N = n;
    REP(i, 1, q) { scanf("%lld", &a[i].first); a[i].second = i; }
	sort(a + 1, a + q + 1); now = 1; REP(i, 1, m) { s[1] = 'a' + i - 1; DFS(2, 0); }
	REP(i, 1, q) { REP(j, 1, len[i]) printf("%c", ans[i][j]); puts(""); }
    return 0;
}
