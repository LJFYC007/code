/***************************************************************
	File name: CF1458E.cpp
	Author: ljfcnyali
	Create time: 2021年01月04日 星期一 16时14分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, c[maxn], N, p[maxn];
map<int, map<int, bool> > Map;
map<int, int> Todo;
map<int, bool> tx, ty;
struct node 
{
    int id, x, y; 
    node ( int a = 0, int b = 0, int c = 0 ) { id = a; x = b; y = c; }
} a[maxn];
bool ans[maxn];

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i <= N; i += lowbit(i) ) c[i] += val; }

inline int get(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m); Map[0][0] = true;
    REP(i, 1, n) { int x, y; scanf("%d%d", &x, &y); Map[x][y] = true; a[i] = node(0, x, y); }
    REP(i, 1, m) { int x, y; scanf("%d%d", &x, &y); a[n + i] = node(i, x, y); }
    n += m; sort(a + 1, a + n + 1, [](node &a, node &b) { return a.y < b.y; });
    REP(i, 1, n) if ( !Todo.count(a[i].y) ) { Todo[a[i].y] = ++ N; p[N] = a[i].y; }
    REP(i, 1, n) a[i].y = Todo[a[i].y];
    sort(a + 1, a + n + 1, [](node &a, node &b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });

    int num = 0;
    REP(i, 1, n) if ( a[i].id == 0 ) 
    {
        int val = num - get(a[i].y);
        if ( a[i].x < p[a[i].y] + val && !ty[a[i].y] ) { ty[a[i].y] = true; add(a[i].y, 1); }
        if ( a[i].x > p[a[i].y] + val && !tx[a[i].x] ) { tx[a[i].x] = true; ++ num; }
    }
    else 
    {
        if ( Map[a[i].x][p[a[i].y]] ) ans[a[i].id] = true;
        else 
        {
            int val = num - get(a[i].y);
            if ( a[i].x == p[a[i].y] + val && !tx[a[i].x] && !ty[a[i].y] ) ans[a[i].id] = true;
        }
    }

    REP(i, 1, m) if ( ans[i] ) puts("LOSE"); else puts("WIN");
    return 0;
}
