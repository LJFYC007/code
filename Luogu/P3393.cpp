/***************************************************************
	File name: P3393.cpp
	Author: ljfcnyali
	Create time: 2019年06月11日 星期二 08时38分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 4000010;

LL Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
LL Begin1[maxn], Next1[maxn], To1[maxn], e1, W1[maxn];
LL n, m, k, s, p, q, num[maxn], dis[maxn];
bool vis[maxn];

inline void add(LL u, LL v, LL w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void add1(LL u, LL v, LL w)
{
    To1[++ e1] = v;
    Next1[e1] = Begin1[u];
    Begin1[u] = e1;
    W1[e1] = w;
}

inline void BFS()
{
    queue<LL> Q; Q.push(0);
    memset ( dis, 0x3f, sizeof (dis) );
    dis[0] = -1;
    while ( !Q.empty() )
    {
        LL u = Q.front(); Q.pop();
        vis[u] = false;
        for ( LL i = Begin[u]; i; i = Next[i] ) 
        {
            LL v = To[i];
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
    REP(i, 1, n)
    {
        if ( num[i] == -1 ) continue ;
        if ( dis[i] <= s ) num[i] = q;
        else num[i] = p;
    }
    num[1] = num[n] = 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld%lld", &n, &m, &k, &s);
    scanf("%lld%lld", &p, &q);
    REP(i, 1, k) { LL x; scanf("%lld", &x); num[x] = -1; add(0, x, 1); }
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v, 1); add(v, u, 1); }
    BFS();
    REP(u, 1, n) 
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( num[u] == -1 || num[v] == -1 ) continue ;
            add1(u, v, num[u] + num[v]);
            add1(v, u, num[u] + num[v]);
        }
    queue<LL> Q; Q.push(1);
    REP(i, 2, n) dis[i] = 21474836476666;
    dis[1] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        for ( int i = Begin1[u]; i; i = Next1[i] ) 
        {
            int v = To1[i];
            if ( dis[v] > dis[u] + W1[i] ) 
            {
                dis[v] = dis[u] + W1[i];
                if ( !vis[v] ) 
                {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
    printf("%lld\n", dis[n] / 2);
    return 0;
}
