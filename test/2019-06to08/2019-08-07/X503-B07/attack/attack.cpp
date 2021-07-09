/***************************************************************
	File name: attack.cpp
	Author: ljfcnyali
	Create time: 2019年08月07日 星期三 10时32分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

int ***d, A, B, C, m, ***f, last, ***p;

struct node
{
    int la, ra, lb, rb, lc, rc, h;
} a[maxn];

inline void add(int x, int y, int z, int val)
{
    if ( x > A || y > B || z > C ) return ;
    f[x][y][z] += val;
}

inline bool check(int t)
{
    if ( last < t ) 
    {
        REP(i, last + 1, t)
        {
            add(a[i].la, a[i].lb, a[i].lc, a[i].h);
            add(a[i].ra, a[i].lb, a[i].lc, -a[i].h);
            add(a[i].la, a[i].rb, a[i].lc, -a[i].h);
            add(a[i].la, a[i].lb, a[i].rc, -a[i].h);
            add(a[i].ra, a[i].rb, a[i].lc, a[i].h);
            add(a[i].ra, a[i].lb, a[i].rc, a[i].h);
            add(a[i].la, a[i].rb, a[i].rc, a[i].h);
            add(a[i].ra, a[i].rb, a[i].rc, -a[i].h);
        }
    }
    else
    {
        REP(i, t + 1, last)
        {
            add(a[i].la, a[i].lb, a[i].lc, -a[i].h);
            add(a[i].ra, a[i].lb, a[i].lc, a[i].h);
            add(a[i].la, a[i].rb, a[i].lc, a[i].h);
            add(a[i].la, a[i].lb, a[i].rc, a[i].h);
            add(a[i].ra, a[i].rb, a[i].lc, -a[i].h);
            add(a[i].ra, a[i].lb, a[i].rc, -a[i].h);
            add(a[i].la, a[i].rb, a[i].rc, -a[i].h);
            add(a[i].ra, a[i].rb, a[i].rc, a[i].h);
        }
    }
    REP(i, 1, A) REP(j, 1, B) REP(k, 1, C) 
        p[i][j][k] = f[i][j][k] + p[i - 1][j][k] + p[i][j - 1][k] + p[i][j][k - 1] - p[i - 1][j - 1][k] - 
        p[i - 1][j][k - 1] - p[i][j - 1][k - 1] + p[i - 1][j - 1][k - 1];
    last = t;
    // printf("%d\n", t);
    // REP(i, 1, A) REP(j, 1, B) { REP(k, 1, C) printf("%d ", f[i][j][k]); puts(""); }
    // REP(i, 1, A) REP(j, 1, B) { REP(k, 1, C) printf("%d ", p[i][j][k]); puts(""); }
    REP(i, 1, A) REP(j, 1, B) REP(k, 1, C) if ( p[i][j][k] > d[i][j][k] ) return true;
    return false;
}

int main()
{
    freopen("attack.in", "r", stdin);
    freopen("attack.out", "w", stdout);
    scanf("%d%d%d%d", &A, &B, &C, &m);
    d = (new int**[A + 1]);
    f = (new int**[A + 1]);
    p = (new int**[A + 1]);
    REP(i, 0, A) 
    {
        d[i] = (new int*[B + 1]);
        f[i] = (new int*[B + 1]);
        p[i] = (new int*[B + 1]);
        REP(j, 0, B) 
        {
            d[i][j] = (new int[C + 1]);
            f[i][j] = (new int[C + 1]);
            p[i][j] = (new int[C + 1]);
        }
    }
    REP(i, 1, A) REP(j, 1, B) REP(k, 1, C) scanf("%d", &d[i][j][k]);
    REP(i, 1, m) 
    {
        scanf("%d%d%d%d%d%d%d", &a[i].la, &a[i].ra, &a[i].lb, &a[i].rb, &a[i].lc, &a[i].rc, &a[i].h);
        ++ a[i].ra; ++ a[i].rb; ++ a[i].rc;
    }
    int L = 1, R = m, ans = -1;
    while ( L <= R ) 
    {
        int Mid = L + R >> 1;
        if ( check(Mid) ) { ans = Mid; R = Mid - 1; }
        else L = Mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
