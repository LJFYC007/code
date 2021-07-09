/***************************************************************
	File name: P3084.cpp
	Author: ljfcnyali
	Create time: 2019年07月03日 星期三 15时13分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, tot, dis[maxn], sum, cnt;
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
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { add(i, i - 1, 0); add(i - 1, i, 1); }
    REP(i, 1, m)
    {
        int u, v; scanf("%d%d", &u, &v);
        add(u - 1, v, 1); add(v, u - 1, -1);
    }
    memset(dis, 0x3f, sizeof(dis));
    deque<int> Q; Q.push_front(0); dis[0] = 0;
    while ( !Q.empty() ) 
    {
        if ( ++ tot >= 50000000 ) { printf("-1\n"); return 0; } 
        int u = Q.front(); Q.pop_front();
        if ( dis[u] * cnt > sum ) { Q.push_back(u); continue ; }
        sum -= dis[u]; -- cnt;
        vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] ) 
                {
                    vis[v] = true;
                    if ( dis[v] >= Q.front() ) Q.push_back(v);
                    else Q.push_front(v);
                    ++ cnt; sum += dis[v];
                }
            }
        }
        vis[u] = false;
    }
    printf("%d\n", dis[n]);
    return 0;
}
