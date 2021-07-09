/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月23日 星期四 08时43分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;

int Begin[maxn], To[maxn], Next[maxn], e = 1;
int t, n, m, degree1[maxn], degree2[maxn];
bool vis[maxn];
vector<int> ans;

inline void add(int u, int v)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
}

inline void DFS(int u)
{
	for ( int &i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i], c = t == 1 ? (i / 2) : (i - 1);
		if ( vis[c] ) continue ; vis[c] = true;
		int p = i % 2;
		DFS(v);
		if ( t == 1 ) ans.push_back(p == 1 ? -c : c);
		else ans.push_back(c);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &t, &n, &m);
	REP(i, 1, m)
	{
		int u, v; scanf("%d%d", &u, &v);
		add(u, v);
		if ( t == 1 ) { add(v, u); ++ degree1[u]; ++ degree1[v]; }
		else { ++ degree1[u]; ++ degree2[v]; }
	}
	REP(i, 1, n) 
		if ( t == 1 && degree1[i] % 2 != 0 ) { printf("NO\n"); return 0; }
		else if ( t == 2 && degree1[i] != degree2[i] ) { printf("NO\n"); return 0; }
	REP(i, 1, n) if ( Begin[i] ) { DFS(i); break ; } 
	if ( ans.size() != m ) { printf("NO\n"); return 0; }
	printf("YES\n");
	for ( int i = ans.size() - 1; i >= 0; -- i ) printf("%d ", ans[i]);
    return 0;
}
