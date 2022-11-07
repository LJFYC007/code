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

const int maxn = 5e5 + 10;
const int INF = 2e18;

int n, m, T, dis[maxn], f[maxn], ans, Next[maxn], Mod;
char s[maxn];
struct node { int x, a, b; } ;
vector<node> a;

inline void Solve(int n)
{
	int j = 0;
	REP(i, 2, n)
	{
		while ( j && s[i] != s[j + 1] ) j = Next[j];
		if ( s[i] == s[j + 1] ) ++ j; Next[i] = j;
	}
	if ( !Next[n] ) return ;
	if ( Next[n] < n / 2 ) { a.push_back({Next[n], Next[n], 0}); Solve(Next[n]); return ; } 
	int x = Next[n] - Next[Next[n]];
	j = Next[n]; while ( j - x >= n / 2 ) j -= x; 
	a.push_back({x, j, (Next[n] - j) / x}); Solve(j);
}

inline void Update(int x)
{
	REP(i, 0, __gcd(x, Mod) - 1)
	{
		int Min = dis[i], pos = i;
		for ( int j = (i + x) % Mod; j != i; j = (j + x) % Mod ) 
			if ( dis[j] < Min ) { Min = dis[j]; pos = j; }
		int lst = pos;
		for ( int j = (pos + x) % Mod; j != pos; j = (j + x) % Mod )
		{
			dis[j] = min(dis[j], dis[lst] + x);
			lst = j;
		}
	}
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
		scanf("%lld%lld", &n, &m); scanf("%s", s + 1);
		if ( n > m ) { puts("0"); continue ; } 

		a.clear(); Solve(n);
		REP(i, 0, n - 1) dis[i] = INF; 
		Mod = dis[0] = n;

		for ( auto it : a ) 
		{
			node now = {it.x, n - it.a - it.x * it.b, it.b};
			REP(i, 0, Mod - 1) f[i] = dis[i], dis[i] = INF;
			REP(i, 0, Mod - 1) if ( f[i] != INF ) dis[f[i] % now.a] = min(dis[f[i] % now.a], f[i]);
			int lst = Mod; Mod = now.a; Update(lst);
			if ( !now.b ) continue ; 

			REP(i, 0, __gcd(Mod, now.x) - 1)
			{
				int x = now.x, Min = dis[i], pos = i; 
				for ( int j = (i + x) % Mod; j != i; j = (j + x) % Mod ) 
					if ( dis[j] < Min ) { Min = dis[j]; pos = j; }
				
				int lst = pos, id = 0; 
				deque<pii> Q; Q.push_front(pii(pos, 0));
				for ( int j = (pos + x) % Mod; j != pos; j = (j + x) % Mod )
				{
					++ id;
					if ( Q.front().second < id - now.b ) Q.pop_front();
					dis[j] = min(dis[j], dis[Q.front().first] - Q.front().second * x + id * x + now.a);
					while ( !Q.empty() && dis[Q.back().first] - Q.back().second * x > dis[j] - id * x ) Q.pop_back();
					Q.push_back(pii(j, id));
				}
			}
		}
		ans = 0; REP(i, 0, Mod - 1) if ( dis[i] <= m ) ans += (m - dis[i]) / Mod + 1;
		printf("%lld\n", ans);
	}
    return 0;
}
