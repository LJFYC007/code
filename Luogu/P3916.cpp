/***************************************************************
	File name: P3916.cpp
	Author: ljfcnyali
	Create time: 2019年06月11日 星期二 09时11分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int ans[maxn], n, m;

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void BFS(int s)
{
    queue<int> Q; Q.push(s);
    ans[s] = s;
    while ( !Q.empty() )
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( ans[v] ) continue ;
            ans[v] = s;
            Q.push(v);
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(v, u); }
    for ( int i = n; i >= 1; -- i )
    {
        if ( ans[i] ) continue ;
        BFS(i);
    }
    REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}
