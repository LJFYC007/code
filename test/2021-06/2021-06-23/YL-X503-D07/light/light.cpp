/***************************************************************
	File name: light.cpp
	Author: ljfcnyali
	Create time: 2021年06月23日 星期三 11时23分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, k, m, c[maxn], deg[2][maxn], num[2][maxn], B, ans;
vector<pii> Edge[2][maxn], E[2][maxn]; vector<int> a[2][maxn];
bool vis[maxn];

inline void Modify0(int x, int val)
{
	for ( auto it : E[0][x] ) 
		num[0][it.first] -= val * it.second;
}

inline void Modify1(int x, int val)
{
	for ( auto it : E[1][x] ) 
		num[1][it.first] += val * it.second;
}

int main()
{
    freopen("light.in", "r", stdin);
    freopen("light.out", "w", stdout);
	scanf("%d%d%d", &n, &k, &m); B = sqrt(n);
	REP(i, 1, n) scanf("%d", &c[i]);
	++ k; ++ n; c[n] = k;
	REP(i, 2, n) if ( c[i] != c[i - 1] ) { a[0][c[i - 1]].push_back(c[i]); a[1][c[i]].push_back(c[i - 1]); }

	REP(op, 0, 1) REP(i, 1, k)
	{
		sort(a[op][i].begin(), a[op][i].end());
		for ( auto it : a[op][i] ) ++ num[op][it];
		for ( auto it : a[op][i] ) if ( num[op][it] ) { Edge[op][i].push_back(pii(it, num[op][it])); num[op][it] = 0; ++ deg[op][i]; }
	}
	REP(op, 0, 1) REP(i, 1, k) if ( deg[op][i] > B ) 
	{
		num[op][i] = op == 0 ? deg[op][i] : 0;
		for ( auto it : Edge[op][i] ) E[op][it.first].push_back(pii(i, it.second));
	}
		
	while ( m -- ) 
	{
		int x; scanf("%d", &x);
		if ( !vis[x] ) 
		{
			vis[x] = true; Modify0(x, 1); Modify1(x, 1);
			if ( deg[0][x] <= B ) 
			{
				for ( auto it : Edge[0][x] ) if ( !vis[it.first] ) 
					ans += it.second;
			}
			else ans += num[0][x];

			if ( deg[1][x] <= B ) 
			{
				for ( auto it : Edge[1][x] ) if ( vis[it.first] ) 
					ans -= it.second;
			}
			else ans -= num[1][x];
		}
		else
		{
			vis[x] = false; Modify0(x, -1); Modify1(x, -1);
			if ( deg[0][x] <= B ) 
			{
				for ( auto it : Edge[0][x] ) if ( !vis[it.first] ) 
					ans -= it.second;
			}
			else ans -= num[0][x];

			if ( deg[1][x] <= B ) 
			{
				for ( auto it : Edge[1][x] ) if ( vis[it.first] ) 
					ans += it.second;
			}
			else ans += num[1][x];
		}

		printf("%d\n", ans);
	}
    return 0;
}
