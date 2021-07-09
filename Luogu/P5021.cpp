/***************************************************************
	File name: P5021.cpp
	Author: ljfcnyali
	Create time: 2019年07月30日 星期二 14时27分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dis[maxn], ans, sum, Mid;
bool use[maxn], flag = true;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int cmp(int x, int y) { return dis[x] > dis[y]; }

inline void DFS(int u, int fa)
{
    if ( sum >= m ) return ;
    vector<int> a;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = W[i];
        DFS(v, u);
        if ( use[v] ) continue ;
        a.push_back(v);
    }
    sort(a.begin(), a.end(), cmp);
    if ( flag == true ) 
    {
        int L = 0, R = a.size() - 1;
        while ( L < R )
        {
            while ( use[a[L]] && L < R ) ++ L;
            while ( L < R && dis[a[L]] + dis[a[R]] < Mid ) -- R;
            if ( L >= R ) break ;
            ++ sum; use[a[L]] = use[a[R]] = true;
            ++ L; -- R;
        }
        REP(i, 0, a.size() - 1) if ( !use[a[i]] ) { dis[u] += dis[a[i]]; break ; }
        if ( dis[u] >= Mid ) { use[u] = true; ++ sum; }
        return ;
    }
    int R = a.size() - 1, L, x = 0;
    while ( R >= 0 ) 
    {
        while ( R >= 0 && (use[a[R]] || dis[a[x]] + dis[a[R]] < Mid) ) -- R;
        L = R - 1;
        while ( L >= 0 && (use[a[L]] || dis[a[L]] + dis[a[R]] < Mid) ) -- L;
        if ( L >= 0 ) { ++ sum; use[a[L]] = use[a[R]] = true; }
        while ( use[a[x]] && x < R ) ++ x;
        -- R;
    }
    REP(i, 0, a.size() - 1) if ( !use[a[i]] ) { dis[u] += dis[a[i]]; break ; }
    if ( dis[u] >= Mid ) { use[u] = true; ++ sum; }
}

inline bool Check()
{
    sum = 0; mem(dis); mem(use);
    DFS(1, 0); 
    return sum >= m;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    int L = 0, R = 0;
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); R += w; if ( u != 1 ) flag = false; }
    while ( L <= R ) 
    {
        Mid = (L + R) >> 1;
        if ( Check() ) { ans = Mid; L = Mid + 1; }
        else R = Mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}
