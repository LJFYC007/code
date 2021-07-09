/***************************************************************
	File name: road.cpp
	Author: ljfcnyali
	Create time: 2019年07月31日 星期三 20时17分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn], C[maxn];
int n, m, k, ans, dis1[maxn], dis2[maxn], use[maxn][maxn][21];
bool vis[maxn];

inline void add(int u, int v, int w, int c) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; C[e] = c; }

inline void Spfa()
{
    queue<int> Q; Q.push(n);
    memset(dis1, 0x3f, sizeof(dis1)); dis1[n] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis1[v] > dis1[u] + C[i] ) 
            {
                dis1[v] = dis1[u] + C[i];
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }     
    mem(vis); Q.push(n);
    memset(dis2, 0x3f, sizeof(dis2)); dis2[n] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis2[v] > dis2[u] + W[i] ) 
            {
                dis2[v] = dis2[u] + W[i];
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    } 
}

inline void DFS(int u, int sum, int cost)
{
    if ( (cost + dis1[u] > k) || (sum + dis2[u] >= ans) ) return ;
    if ( u == n ) { if ( cost == k ) ans = sum; return ; } 
    // if ( use[u][cost][num] < sum ) return ;
    // use[u][cost][num] = sum;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ;
        vis[v] = true;
        DFS(v, sum + W[i], cost + C[i]);
        vis[v] = false;
    }
}

int main()
{
    // freopen("road.in", "r", stdin);
    // freopen("road.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, m) { int u, v, w, c; scanf("%d%d%d%d", &u, &v, &w, &c); add(u, v, w, c); add(v, u, w, c); ans += w; }
    Spfa();
    mem(vis); memset(use, 0x3f, sizeof(use)); vis[1] = true;
    DFS(1, 0, 0);
    printf("%d\n", ans);
    return 0;
}
