/***************************************************************
	File name: P1629.cpp
	Author: ljfcnyali
	Create time: 2019年06月11日 星期二 09时59分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

int Begin[maxn][2], Next[maxn][2], To[maxn][2], e[2], W[maxn][2];
int dis[maxn], n, m, ans;
bool vis[maxn];

inline void add(int u, int v, int w, int num)
{
    To[++ e[num]][num] = v;
    Next[e[num]][num] = Begin[u][num];
    Begin[u][num] = e[num];
    W[e[num]][num] = w;
}

inline void BFS(int num)
{
    queue<int> Q; Q.push(1);
    memset ( dis, 0x3f, sizeof (dis) );
    dis[1] = 0;
    mem(vis);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        for ( int i = Begin[u][num]; i; i = Next[i][num] ) 
        {
            int v = To[i][num];
            if ( dis[v] > dis[u] + W[i][num] ) 
            {
                dis[v] = dis[u] + W[i][num];
                if ( !vis[v] )
                {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
    REP(i, 2, n) ans += dis[i];
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w, 0); add(v, u, w, 1); }
    BFS(0); 
    BFS(1);
    printf("%d\n", ans);
    return 0;
}
