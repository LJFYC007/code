/***************************************************************
	File name: P2294.cpp
	Author: ljfcnyali
	Create time: 2020年06月19日 星期五 10时10分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e4 + 10;

int T, n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], cnt[maxn], dis[maxn];
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m); ++ n;
        e = 0; mem(Begin); mem(vis); mem(cnt);
        memset(dis, 0x3f, sizeof(dis)); dis[1] = 0;
        REP(i, 1, m)
        {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            ++ u; ++ v;
            add(v, u - 1, -w);
            add(u - 1, v, w);
        }
        queue<int> Q; Q.push(1); vis[1] = true; 
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop();
            ++ cnt[u]; if ( cnt[u] > n ) { puts("false"); goto Next ; }
            for ( int i = Begin[u]; i; i = Next[i] )
            {
                int v = To[i];
                if ( dis[v] > dis[u] + W[i] ) 
                {
                    dis[v] = dis[u] + W[i];
                    if ( !vis[v] ) { vis[v] = true; Q.push(v); }
                }
            }
            vis[u] = false;
        }
        puts("true");
Next : ; 
    }
    return 0;
}
