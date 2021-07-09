/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年01月24日 星期日 09时42分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 40;
const int maxm = 14348907 + 10;
const LL INF = 1e18;

int n, m, a[maxn], p[1 << 15], n1, n2;
LL q[1 << 15], h[1 << 15], b[maxn];
struct node { int x, y; LL w; short op; } f1[maxm], f2[maxm], f3[maxm / 3], f4[maxm / 3], f5[maxm / 3];
bool operator < (const node &a, const node &b) { return a.w < b.w || (a.w == b.w && a.op < b.op); }
pii g[maxn][2];

inline void print()
{
    puts("Yes");
    REP(i, 1, n) printf("%lld ", b[i]); puts("");
    REP(i, 1, n) 
    {
        REP(x, 1, n) REP(y, 1, n) if ( b[x] + b[y] == a[i] ) { printf("%d %d\n", x, y); goto Finish; }
Finish : ;
    }
}

inline int get(int s, int i)
{
    REP(j, i + 1, n) if ( (s >> j - 1) & 1 ) return j;
    return n + 1;
}

inline void DFS1(int x, node f1[], int &n1) 
{
    if ( x == n - m + 1 ) { n1 = 1; f1[n1] = {0, 0, 0, 0}; return ; } 
    DFS1(x + 1, f1, n1);
    REP(i, 1, n1) 
    { 
        f3[i] = f1[i];
        f4[i] = f1[i]; f4[i].x |= (1 << x - 1); ++ f4[i].op; f4[i].w += a[m + x]; 
        f5[i] = f1[i]; f5[i].y |= (1 << x - 1); -- f5[i].op; f5[i].w -= a[m + x];
    }
    int now1 = 1, now2 = 1, now3 = 1, N = 0; 
    while ( now1 <= n1 || now2 <= n1 || now3 <= n1 ) 
    {
        node t = {0, 0, INF, 0}; int pos = 0;
        if ( now1 <= n1 && f3[now1] < t ) { t = f3[now1]; pos = 1; }
        if ( now2 <= n1 && f4[now2] < t ) { t = f4[now2]; pos = 2; }
        if ( now3 <= n1 && f5[now3] < t ) { t = f5[now3]; pos = 3; }
        f1[++ N] = t;
        if ( pos == 1 ) ++ now1; if ( pos == 2 ) ++ now2; if ( pos == 3 ) ++ now3;
    }
    n1 = N;
}

inline void DFS2(int x, node f1[], int &n1) 
{
    if ( x == m + 1 ) { n1 = 1; f1[n1] = {0, 0, 0, 0}; return ; } 
    DFS2(x + 1, f1, n1);
    REP(i, 1, n1) 
    { 
        f3[i] = f1[i];
        f4[i] = f1[i]; f4[i].x |= (1 << x - 1); ++ f4[i].op; f4[i].w += a[x]; 
        f5[i] = f1[i]; f5[i].y |= (1 << x - 1); -- f5[i].op; f5[i].w -= a[x];
    }
    int now1 = 1, now2 = 1, now3 = 1, N = 0; 
    while ( now1 <= n1 || now2 <= n1 || now3 <= n1 ) 
    {
        node t = {0, 0, INF, 0}; int pos = 0;
        if ( now1 <= n1 && f3[now1] < t ) { t = f3[now1]; pos = 1; }
        if ( now2 <= n1 && f4[now2] < t ) { t = f4[now2]; pos = 2; }
        if ( now3 <= n1 && f5[now3] < t ) { t = f5[now3]; pos = 3; }
        f1[++ N] = t;
        if ( pos == 1 ) ++ now1; if ( pos == 2 ) ++ now2; if ( pos == 3 ) ++ now3;
    }
    n1 = N;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = 15;
    REP(i, 0, (1 << n) - 1) REP(j, 1, n) if ( (i >> j - 1) & 1 ) ++ p[i];
    scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
    m = (n + 1) / 2;
    REP(i, 0, (1 << n - m) - 1) REP(j, 1, n - m) if ( (i >> j - 1) & 1 ) q[i] += a[m + j];
    REP(i, 0, (1 << m) - 1) REP(j, 1, m) if ( (i >> j - 1) & 1 ) h[i] += a[j];
    memset(g, -1, sizeof(g));

    REP(i, 0, (1 << n - m) - 1)
    {
        for ( int j = i; ; j = i & (j - 1) ) 
        {
            LL sum = q[i ^ j] - q[j]; int num = p[i ^ j] - p[j];
            g[num + m][(sum % 2 + 2) % 2] = pii(i ^ j, j);
            if ( !j ) break ; 
        }
    }
    REP(i, 1, (1 << m) - 1)
    {
        for ( int j = i; ; j = i & (j - 1) )
        {
            LL sum = h[i ^ j] - h[j], x = -1; int num = p[i ^ j] - p[j];
            if ( g[m - num + 1][(sum % 2 + 2) % 2].x != -1 )
            {
                pii y = g[m - num + 1][(sum % 2 + 2) % 2]; x = (sum + q[y.x] - q[y.y]) / 2;
                int S = ((y.x | y.y) << m) | i, s = (y.x << m) | (i ^ j), t = (y.y << m) | j;
                int l = get(s, 0), r = get(t, 0);
                REP(o, 1, n)
                {
                    b[l] = x; x = a[l] - x; l = get(s, l);
                    if ( l == n + 1 ) break ;
                    b[r] = x; x = a[r] - x; r = get(t, r);
                }
                REP(o, 1, n) if ( !((S >> o - 1) & 1) ) b[o] = a[o] - x;
                print(); return 0;
            }
            if ( !j ) break ; 
        }
    }
    DFS1(1, f1, n1); DFS2(1, f2, n2);

    int now1 = n1;
    REP(now2, 1, n2)
    {
        while ( now1 > 0 && (f1[now1].w > -f2[now2].w || (f1[now1].w == -f2[now2].w && f1[now1].op > -f2[now2].op)) ) -- now1;
        if ( now1 > 0 && f2[now2].x == 0 && f2[now2].y == 0 ) -- now1;
        if ( now1 && f1[now1].op == -f2[now2].op && f1[now1].w == -f2[now2].w ) 
        {
            int S = ((f1[now1].x | f1[now1].y) << m) | (f2[now2].x | f2[now2].y); LL x = 0;
            int s = (f1[now1].x << m) | f2[now2].x, t = (f1[now1].y << m) | f2[now2].y;
            int l = get(s, 0), r = get(t, 0);
            REP(o, 1, n)
            {
                b[l] = x; x = a[l] - x; l = get(s, l);
                b[r] = x; x = a[r] - x; r = get(t, r);
                if ( l == n + 1 ) break ; 
            }
            REP(o, 1, n) if ( !((S >> o - 1) & 1) ) b[o] = a[o] - x;
            print(); return 0;
        }
    }
    puts("No");
    return 0;
}
