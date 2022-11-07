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
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10, ans;

int f[maxn], g[maxn], b[maxn], p[maxn], T, n, m, Begin[maxn], Next[maxn], To[maxn], e;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
	f[u] = g[u] = 0; vector<int> a;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS(v, u);
		a.push_back(g[v]);
	}
	if ( a.empty() ) { g[u] += b[u]; return ; } 
	sort(a.begin(), a.end());
	int sum1 = 0; for ( int i = 0; i + p[u] - 1 < a.size(); ++ i ) sum1 += a[i];
	int sum = 0; for ( int i = 0; i < a.size(); ++ i ) sum += a[i];
	int num = 0;
	if ( sum1 >= a.back() ) 
		num = sum / p[u] + (p[u] != 1 && sum % p[u] == 0);
	else num = sum1;
	
	num = min(num, b[u]);
	f[u] += num;
	g[u] += b[u] - num;
	if ( u == 1 ) cerr << f[u] << " " << g[u] << endl;
	int val = sum - num * p[u];
	if ( u == 1 ) cerr << num << " " << sum1 << " " << val << endl;
	if ( b[u] > num && sum1 < a.back() ) 
		for ( int i = 0; i < a.size(); ++ i ) 
			val -= min(b[u] - num, a[i] - sum1);
	f[u] += val;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- ) 
	{
		scanf("%lld", &n);
		e = 0; mem(Begin);
		REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
		REP(i, 1, n) scanf("%lld%lld", &b[i], &p[i]);
		ans = 0;
		REP(i, 1, n) ans += b[i];
		DFS(1, 0);
		printf("%lld\n", ans);
		//REP(i, 1, n) printf("%lld %lld\n", f[i], g[i]);
		//printf("%lld\n", f[1] + g[1]);
	}
    return 0;
}
