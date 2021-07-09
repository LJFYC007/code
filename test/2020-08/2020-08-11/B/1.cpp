/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年08月11日 星期二 08时42分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define x first
#define y second
typedef long long LL;

const int maxn = 5e5 + 10;
const int Mod = 1e9 + 7;

int n, q, a[maxn], ans[maxn];
pii Q[maxn];
struct Matrix { int a[11][11]; } e, Tree[maxn << 2];
Matrix operator * (Matrix a, Matrix b)
{
    Matrix c; 
    REP(i, 0, 10) REP(j, 0, 10) c.a[i][j] = 0;
    REP(i, 0, 10) REP(k, 0, 10) if ( a.a[i][k] ) REP(j, 0, 10) c.a[i][j] = (c.a[i][j] + (LL)a.a[i][k] * b.a[k][j]) % Mod;
    return c;
};
char s[maxn];

inline void Build(int root, int l, int r)
{
    if ( l == r ) 
    {
        Tree[root].a[0][0] = 2; Tree[root].a[0][a[l]] = 1;
        REP(i, 1, 10) 
            if ( a[l] != i ) Tree[root].a[i][i] = 1;
            else Tree[root].a[i][0] = -1;
        return ;
    }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Tree[root] = Tree[lson] * Tree[rson];
}

inline Matrix Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root];
    int Mid = l + r >> 1; Matrix x = e;
    if ( L <= Mid ) x = x * Query(lson, l, Mid, L, R);
    if ( Mid < R ) x = x * Query(rson, Mid + 1, r, L, R);
    return x;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    REP(i, 0, 10) e.a[i][i] = 1;
    scanf("%s", s + 1); n = str(s + 1); 
    REP(i, 1, n) a[i] = s[i] - 'a' + 1;
    scanf("%d", &q); REP(i, 1, q) scanf("%d%d", &Q[i].x, &Q[i].y);
    Build(1, 1, n);
    Matrix x = Query(1, 1, n, 2, 2);
    REP(i, 1, q)
    {
        Matrix x = Query(1, 1, n, Q[i].x, Q[i].y);
        printf("%d\n", (x.a[0][0] - 1 + Mod) % Mod);
    }
    return 0;
}
