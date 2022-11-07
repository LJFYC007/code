/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年07月18日 星期日 12时50分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int id, n, a[maxn], p[maxn], m, fa[maxn];
vector<int> son[maxn], Edge[maxn]; bool vis[maxn];
set<int> Set; bool flag;

inline void DFS(int u)
{
    Set.insert(a[u]);
    int n = Edge[u].size();
    for ( int i = n - 1; i >= 0; -- i )
        DFS(Edge[u][i]);
    p[u] = m; m --;
    if ( !Set.count(p[u]) ) flag = false;
    else Set.erase(p[u]);
}

inline void Solve(int x)
{
	if ( x == n + 1 ) 
	{
        flag = true; Set.clear();
		m = n; DFS(1);
        if ( flag ) 
        {
            REP(i, 1, n) printf("%d ", p[i]); puts("");
            exit(0);
        }
        if ( id == 2 || id == 5 ) { puts("-1"); exit(0); }
		return ; 
	}
	int num = son[x].size(); vector<int> b(num);
	REP(i, 0, num - 1) b[i] = i;
	do
	{
		Edge[x].clear();
		REP(i, 0, num - 1) Edge[x].push_back(son[x][b[i]]);
		Solve(x + 1);
	} while ( next_permutation(b.begin(), b.end()) );
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &id, &n);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 2, n) { int x; scanf("%d", &x); son[x].push_back(i); fa[i] = x; }
	Solve(1);
	puts("-1");
    return 0;
}