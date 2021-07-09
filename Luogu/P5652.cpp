/***************************************************************
	File name: P5652.cpp
	Author: ljfcnyali
	Create time: 2019年11月13日 星期三 19时39分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, q, type, a[maxn], A, B, C, P, Q[maxn], head = 1, tail, p[maxn];
int Begin[maxn], Next[maxn], To[maxn], e, size[maxn], dfn[maxn], cnt;
unsigned int ans;

inline int rnd() { return A = (A * B + C) % P; }

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    dfn[u] = ++ cnt; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        DFS(v); size[u] += size[v];
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &q, &type);
    REP(i, 1, n) 
    {
        scanf("%d", &a[i]);
        if ( a[i] & 1 ) { Q[++ tail] = i; p[i] = i; } else p[i] = p[i - 1];
        while ( head < tail && Q[head + 1] < i - m ) ++ head;
        if ( a[i] & 1 && Q[head] < i - m ) add(Q[head], i);
    }
    REP(i, 1, n) if ( !dfn[i] ) DFS(i);
    if ( type == 1 ) scanf("%d%d%d%d", &A, &B, &C, &P);
    REP(o, 1, q)
    {
        int L, R;
        if ( type == 0 ) scanf("%d%d", &L, &R);
        else { L = rnd() % n + 1; R = rnd() % n + 1; if ( L > R ) swap(L, R); }
        R = p[R];
        if ( dfn[L] <= dfn[R] && dfn[R] <= dfn[L] + size[L] - 1 ) continue ;
        ans += o * o;
    }
    cout << ans << endl;
    return 0;
}
