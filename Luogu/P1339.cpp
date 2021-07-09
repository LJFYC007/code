/***************************************************************
	File name: P1339.cpp
	Author: ljfcnyali
	Create time: 2019年06月16日 星期日 10时11分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, dis[maxn], s, t;
bool vis[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &s, &t);
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    queue<int> Q; Q.push(s); 
    REP(i, 1, n) dis[i] = 0x3f3f3f3f; dis[s] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop(); vis[u] = false;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] ) 
                {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
    printf("%d\n", dis[t]);
    return 0;
}
