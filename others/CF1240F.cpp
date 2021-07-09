/***************************************************************
	File name: CF1240F.cpp
	Author: ljfcnyali
	Create time: 2021年04月30日 星期五 19时06分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3210;

int n, m, k, tot, id[maxn], num[maxn];
int ans[maxn], match[maxn]; bool vis[maxn], use[maxn];
vector<int> Edge[maxn][maxn];

inline bool DFS(int u)
{
	if ( vis[u] ) return false; vis[u] = true;
	REP(v, 1, tot) if ( !Edge[u][v].empty() && (!match[v] || DFS(match[v])) )
	{
		match[u] = v; match[v] = u;
		return true;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &k);
	REP(i, 1, n) { scanf("%d", &ans[i]); use[i] = true; }
	REP(i, 1, n + n) id[i] = ++ tot;
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v); v += n;
		if ( num[id[u]] == k ) { id[u] = ++ tot; use[tot] = true; } ++ num[id[u]];
		if ( num[id[v]] == k ) id[v] = ++ tot; ++ num[id[v]];
		Edge[id[u]][id[v]].push_back(i);
	}
	REP(i, 1, tot) while ( use[i] && num[i] < k ) 
	{
		++ num[i];
		REP(j, 1, tot) if ( !use[j] && num[j] < k ) { ++ num[j]; Edge[i][j].push_back(m + 1); goto Next1 ; } 
		++ tot; ++ num[tot]; Edge[i][tot].push_back(m + 1);
Next1 : ;
	}
	bool flag = false;
	REP(i, 1, tot) while ( !use[i] && num[i] < k ) 
	{
		++ num[i];
		if ( !flag || num[tot] == k ) { ++ tot; use[tot] = flag = true; }
		++ num[tot]; Edge[tot][i].push_back(m + 1);
	}
	REP(i, 1, tot) 
	{
		int sum = 0;
		REP(j, 1, tot) sum += Edge[i][j].size() + Edge[j][i].size();
		if ( sum != k ) 
		{
			cout << i << " " << use[i] << " " << sum << endl;
			return 0;
		}
	}
	REP(o, 1, k)
	{
		mem(match);
		REP(i, 1, tot) if ( use[i] ) { mem(vis); DFS(i); }
		REP(i, 1, tot) if ( use[i] && match[i] ) { ans[Edge[i][match[i]].back()] = o; Edge[i][match[i]].pop_back(); }
	}

	REP(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}
