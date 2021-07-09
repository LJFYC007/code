/***************************************************************
	File name: P4568.cpp
	Author: ljfcnyali
	Create time: 2019年07月04日 星期四 14时25分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dis[maxn], n, m, k, s, t, ans;
int a[maxn], b[maxn], c[maxn];
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
    scanf("%d%d%d", &n, &m, &k);
    scanf("%d%d", &s, &t);
    ++ s; ++ t;
    REP(i, 1, m) scanf("%d%d%d", &a[i], &b[i], &c[i]);
    for ( int i = m; i >= 1; -- i )
    {
        int u = a[i], v = b[i], w = c[i];
        ++ u; ++ v;
        add(u, v, w); add(v, u, w);
        REP(j, 1, k)
        {
            int N = j * n;
            add(N + u, N + v, w); add(N + v, N + u, w);
            add(N - n + u, N + v, 0); add(N - n + v, N + u, 0);
        }
    }
    deque<int> Q; Q.push_front(s); memset(dis, 0x3f, sizeof(dis)); dis[s] = 0;
    int sum = 0, cnt = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop_front();
        if ( dis[u] * cnt > sum ) { Q.push_back(u); continue ; }
        sum -= dis[u]; -- cnt;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] )
                {
                    vis[v] = true;
                    if ( dis[v] < dis[Q.front()] ) Q.push_front(v);
                    else Q.push_back(v);
                    sum += dis[v]; ++ cnt;
                }
            }
        }
        vis[u] = false;
    }
    ans = INF;
    REP(i, 0, k) ans = min(ans, dis[i * n + t]);
    printf("%d\n", ans);
    return 0;
}
