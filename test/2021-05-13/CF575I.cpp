/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int maxm = 10010;

int a[maxm][maxm], b[maxm], n, q, ans[maxn];
struct node { int dir, x, y, len; } Q[maxn];

inline int lowbit(int x) { return x & -x; } 
inline void add(int *c, int pos, int val) { for ( int i = pos; i <= n + n; i += lowbit(i) ) c[i] += val; }
inline int query(int *c, int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i]; return ret; } 
inline void modify(int l, int r, int L, int R)
{
    if ( l > r || L > R ) return ;
    for ( int i = l; i <= n + n; i += lowbit(i) ) 
       add(a[i], L, 1), add(a[i], R + 1, -1);
    for ( int i = r + 1; i <= n + n; i += lowbit(i) ) 
       add(a[i], L, -1), add(a[i], R + 1, 1);
}
inline int ask(int posx, int posy)
{
    int ret = 0;
    for ( int i = posx; i > 0; i -= lowbit(i) ) ret += query(a[i], posy);
    return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &q); 
    REP(i, 1, q)
    {
        int op; scanf("%d", &op); 
        if ( op == 1 ) scanf("%d%d%d%d", &Q[i].dir, &Q[i].x, &Q[i].y, &Q[i].len);
        else { Q[i].dir = 5; scanf("%d%d", &Q[i].x, &Q[i].y); }
        if ( Q[i].dir == 2 ) assert(Q[i].y > Q[i].len);
        if ( Q[i].dir == 3 ) assert(Q[i].x > Q[i].len);
        if ( Q[i].dir == 4 ) assert(Q[i].x > Q[i].len && Q[i].y > Q[i].len);
    }

    mem(b);
    REP(i, 1, q) if ( Q[i].dir == 1 ) { add(b, Q[i].x + Q[i].y, 1); add(b, Q[i].x + Q[i].y + Q[i].len + 1, -1); }
    else if ( Q[i].dir == 4 ) { add(b, Q[i].x + Q[i].y - Q[i].len, 1); add(b, Q[i].x + Q[i].y + 1, -1); }
    else if ( Q[i].dir == 5 ) ans[i] += query(b, Q[i].x + Q[i].y);
    mem(b);
    REP(i, 1, q) if ( Q[i].dir == 2 ) { add(b, Q[i].x - Q[i].y + n, 1); add(b, Q[i].x - Q[i].y + n + Q[i].len + 1, -1); }
    else if ( Q[i].dir == 3 ) { add(b, Q[i].x - Q[i].y + n - Q[i].len, 1); add(b, Q[i].x - Q[i].y + n + 1, -1); }
    else if ( Q[i].dir == 5 ) ans[i] += query(b, Q[i].x - Q[i].y + n);

    mem(a);
    REP(i, 1, q) if ( Q[i].dir == 1 ) { modify(Q[i].x + Q[i].y, Q[i].x + Q[i].y + Q[i].len, 1, Q[i].x - 1); }
    else if ( Q[i].dir == 4 ) { modify(Q[i].x + Q[i].y - Q[i].len, Q[i].x + Q[i].y, Q[i].x + 1, n); }
    else if ( Q[i].dir == 5 ) ans[i] -= ask(Q[i].x + Q[i].y, Q[i].x);
    mem(a);
    REP(i, 1, q) if ( Q[i].dir == 1 ) { modify(Q[i].x + Q[i].y, Q[i].x + Q[i].y + Q[i].len, 1, Q[i].y - 1); }
    else if ( Q[i].dir == 4 ) { modify(Q[i].x + Q[i].y - Q[i].len, Q[i].x + Q[i].y, Q[i].y + 1, n); }
    else if ( Q[i].dir == 5 ) ans[i] -= ask(Q[i].x + Q[i].y, Q[i].y);

    mem(a);
    REP(i, 1, q) if ( Q[i].dir == 2 ) { modify(Q[i].x - Q[i].y + n, Q[i].x - Q[i].y + n + Q[i].len, 1, Q[i].x - 1); }
    else if ( Q[i].dir == 3 ) { modify(Q[i].x - Q[i].y + n - Q[i].len, Q[i].x - Q[i].y + n, Q[i].x + 1, n); }
    else if ( Q[i].dir == 5 ) ans[i] -= ask(Q[i].x - Q[i].y + n, Q[i].x);
    mem(a);
    REP(i, 1, q) if ( Q[i].dir == 2 ) { modify(Q[i].x - Q[i].y + n, Q[i].x - Q[i].y + n + Q[i].len, Q[i].y + 1, n); }
    else if ( Q[i].dir == 3 ) { modify(Q[i].x - Q[i].y + n - Q[i].len, Q[i].x - Q[i].y + n, 1, Q[i].y - 1); }
    else if ( Q[i].dir == 5 ) ans[i] -= ask(Q[i].x - Q[i].y + n, Q[i].y);

    REP(i, 1, q) if ( Q[i].dir == 5 ) printf("%d\n", ans[i]);
    return 0;
}
