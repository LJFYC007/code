/***************************************************************
	File name: CF547D.cpp
	Author: ljfcnyali
	Create time: 2021年01月22日 星期五 14时38分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int N = 2e5;

int n, m, deg[maxn], ans[maxn];
vector<pii> Edge[maxn];
bool vis[maxn];

inline void add(int u, int v, int i) { ++ deg[u]; ++ deg[v]; Edge[u].push_back(pii(v, i)); Edge[v].push_back(pii(u, i)); }

inline void DFS(int u)
{
    while ( !Edge[u].empty() ) 
    {
        auto v = Edge[u].back(); Edge[u].pop_back();
        if ( vis[v.second] ) continue ; 
        vis[v.second] = true; ans[v.second] = u;
        DFS(v.first); 
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); m = n;
    REP(i, 1, n) { int x, y; scanf("%d%d", &x, &y); add(x, y + N, i); }
    REP(i, 1, N + N) if ( deg[i] & 1 ) add(i, N + N + 1, ++ m);
    REP(i, 1, N) DFS(i);
    REP(i, 1, n) printf("%c", ans[i] <= N ? 'r' : 'b'); puts("");
    return 0;
}

