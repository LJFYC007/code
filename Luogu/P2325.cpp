/***************************************************************
	File name: P2325.cpp
	Author: ljfcnyali
	Create time: 2019年06月24日 星期一 14时30分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2010;

int Begin[maxn], Next[maxn], To[maxn], e;
int n, m, city[maxn], cnt, p[maxn], Stack[maxn], sum;

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void DFS(int u, int fa)
{
    int s = sum;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        if ( sum - s >= m ) 
        {
            city[++ cnt] = u;
            while ( sum > s ) p[Stack[sum --]] = cnt;
        }
    }
    Stack[++ sum] = u;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    if ( !cnt ) city[++ cnt] = 1;
    while ( sum ) p[Stack[sum --]] = cnt;
    printf("%d\n", cnt);
    REP(i, 1, n) printf("%d ", p[i]); puts("");
    REP(i, 1, cnt) printf("%d ", city[i]);
    return 0;
}
