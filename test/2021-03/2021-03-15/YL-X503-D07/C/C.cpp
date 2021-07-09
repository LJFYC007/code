#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
 
const int maxn = 1e5 + 10;
const int Mod = 998244353;
 
int T, n, c[maxn], m, fac[maxn], inv[maxn], tag, ans;
struct node { int num, x; } a[maxn];
unordered_map<int, int> Map[2];
 
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = 1ll * r * a % Mod; a = 1ll * a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : 1ll * fac[n] * inv[m] % Mod * inv[n - m] % Mod; }
 
inline void DFS(int x, int op, vector<int> p, int sum)
{
    if ( x == n + 1 ) 
	{
		if ( tag == 1 ) reverse(p.begin(), p.end());
		int num = 0; for ( auto it : p ) num = (num * 233 + it) % Mod;
		if ( tag == 0 ) Map[op][num] += sum; 
		else 
		{
			int o = p.empty() ? 0 : op ^ 1;
			ans = (ans + 1ll * Map[o][num] * sum) % Mod;
		}
		return ; 
	}
    REP(i, 0, a[x].num) 
    {
        vector<int> q = p; reverse(q.begin(), q.end());
        int t = a[x].num - i; while ( t && q.size() && q.back() == a[x].x ) { q.pop_back(); -- t; } 
        if ( q.size() && t ) goto Next;
        reverse(q.begin(), q.end());
        if ( !t ) DFS(x + 1, q.size() ? op : 0, q, 1ll * sum * C(a[x].num, i) % Mod);
        else { REP(j, 1, t) q.push_back(a[x].x); DFS(x + 1, op ^ 1, q, 1ll * sum * C(a[x].num, i) % Mod); } 
Next : ;
        p.push_back(a[x].x);
    }
}
 
inline void Solve() { vector<int> p; DFS(1, 0, p, 1); }
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = 1ll * inv[i + 1] * (i + 1) % Mod;
    scanf("%d", &T);
    while ( T -- ) 
    {
        int N; scanf("%d", &N); REP(i, 1, N) scanf("%d", &c[i]);
		m = 0;  
		for ( int l = 1, r; l <= N; l = r + 1 )  
		{
			r = l; while ( r < N && c[r + 1] == c[r] ) ++ r;
			a[++ m] = {r - l + 1, c[l]};
		}
        n = m / 2; tag = 0; Solve();
        ans = 0; tag = 1; for ( int i = m; i > n; -- i ) a[m - i + 1] = a[i]; n = m - n; Solve();
		Map[0].clear(); Map[1].clear();
        printf("%d\n", ans);
    }
    return 0;
}
