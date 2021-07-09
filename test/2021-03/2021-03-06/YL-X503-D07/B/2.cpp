#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 2e5 + 10;
const int Mod = 1e9 + 7;

int n, x, p[maxn], b[maxn], c[maxn], d[maxn], ans, f[maxn], g[maxn];
int Begin[maxn], Next[maxn], To[maxn], e, deg[maxn];
bool vis[maxn];
queue<int> Q;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; } 

inline int sgn(int x) { return x & 1 ? -1 : 1; } 

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B1.out", "w", stdout);
#endif
	scanf("%lld%lld", &n, &x);
	REP(i, 1, n) { scanf("%lld", &d[i]); f[i] = 1; } 
	REP(i, 2, n) { scanf("%lld%lld%lld", &p[i], &b[i], &c[i]); } 

	REP(s, 0, (1 << n) - 1)
	{
		REP(i, 1, n) vis[i] = false; int ret = 1;	
		REP(i, 1, n) if ( (s >> i - 1) & 1 ) 
		{
			if ( i == 1 || vis[i] || vis[p[i]] ) goto Next ;
			vis[i] = vis[p[i]] = true; 
		}
		REP(i, 1, n) 
			if ( (s >> i - 1) & 1 ) ret = ret * (-b[i]) % Mod * c[i] % Mod;
			else if ( !vis[i] ) ret = ret * d[i] % Mod;
		ans = (ans + ret) % Mod;
		cout << s << " " << ret << endl;
Next : ; 
	}

	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
