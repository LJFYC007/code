/***************************************************************
	File name: AGC043C.cpp
	Author: ljfcnyali
	Create time: 2021年07月09日 星期五 11时32分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;
const int Mod = 998244353;
const int INF = (int)(1e18) % Mod;

int n, m, a[3][maxn], b[3][maxn], ans, id[maxn];
vector<int> Edge[maxn]; bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(o, 0, 2)
	{
		scanf("%lld", &m); mem(Edge); mem(id);
		REP(j, 1, m) 
		{ 
			int x, y; scanf("%lld%lld", &x, &y);
			if ( x > y ) swap(x, y);
			Edge[x].push_back(y);
		}
		for ( int i = n; i >= 1; -- i ) 
		{
			for ( auto v : Edge[i] ) vis[id[v]] = true;
			while ( vis[id[i]] ) ++ id[i];
			a[o][id[i]] = (a[o][id[i]] + power(INF, i)) % Mod;
			// ++ a[o][id[i]]; b[o][id[i]] += i;
			for ( auto v : Edge[i] ) vis[id[v]] = false;
		}
	}
	REP(i, 0, n) 
	{
		if ( !a[0][i] ) break ; 
		REP(j, 0, n) 
		{
			if ( !a[1][j] ) break ; 
			REP(k, 0, n)
			{
				if ( !a[2][k] ) break ; 
				if ( (i ^ j ^ k) == 0 ) 
				{
					int ret = 1;
					ret = ret * a[0][i] % Mod;
					ret = ret * a[1][j] % Mod;
					ret = ret * a[2][k] % Mod;
					ans = (ans + ret) % Mod;
				}
			}
		}
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
