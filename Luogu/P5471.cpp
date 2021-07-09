/***************************************************************
    File name: P5471.cpp
    Author: ljfcnyali
    Create time: 2019年07月19日 星期五 21时12分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( register int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r

const int maxn = 70010;
const int maxm = 150010;

struct node1
{
    int l, r;
    vector<int> a;
} Tree[maxn << 5];

struct node2 {
    int x, y, id;
    bool operator < (const node2 &a) const { return x < a.x || (x == a.x && y < a.y); }
} a[maxn];

struct node3
{
    int p, t, l, r, d, u;
    bool operator < (const node3 &a) const { return p < a.p; }
} p[maxm];

struct node4
{
    int pos, dis;
} p1, p2;

int n, m, w, h, dis[maxn], h1[maxm], cnt, h2[maxn];
bool vis[maxn];

namespace Heap
{
    int len;
    node4 a[maxn << 5];

    inline void Insert(node4 x)
    {
        a[++ len] = x;        
        int k = len;
        while ( k > 1 && a[k].dis < a[k >> 1].dis )
        {
            swap(a[k], a[k >> 1]); k >>= 1;
        }
    }

    inline node4 top() { return a[1]; }

    inline void Delete()
    {
        a[1] = a[len --]; int k = 1;
        while ( ((k << 1) <= len && a[k].dis > a[k << 1].dis) || ((k << 1) < len && a[k].dis > a[k << 1 | 1].dis) )
        {
            int m = k << 1;
            if ( m < len && a[m].dis > a[m + 1].dis ) ++ m;
            swap(a[k], a[m]); k = m;
        }
    }
}

inline int cmp(int x, int y)
{
    return a[x].y < a[y].y;
}

inline int Query(int root, int l, int r, int x)
{
    if ( !root ) 
    {
        root = ++ cnt; 
        int num = lower_bound(h2 + 1, h2 + n + 1, l) - h2;
        while ( h2[num] <= r && num <= n ) Tree[root].a.push_back(num ++);
        sort(Tree[root].a.begin(), Tree[root].a.end(), cmp);
    }
    if ( p[x].l <= l && r <= p[x].r ) 
    {
        int L = 0, R = Tree[root].a.size() - 1, num = -1;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            if ( a[Tree[root].a[Mid]].y >= p[x].d ) { num = Mid; R = Mid - 1; }
            else L = Mid + 1;
        }
        if ( num == -1 ) return root;
        int val = dis[p[x].p] + p[x].t;
        while ( num < Tree[root].a.size() && a[Tree[root].a[num]].y <= p[x].u ) 
        {
            int v = a[Tree[root].a[num]].id;
            if ( dis[v] > val ) 
            {
                dis[v] = val;
                if ( !vis[v] ) 
                {
                    p2.pos = v; p2.dis = dis[v];
                    Heap :: Insert(p2);
                }
            }
            ++ num;
        }
        return root;
    }
    int Mid = l + r >> 1;
    if ( p[x].l <= Mid ) ls(root) = Query(ls(root), l, Mid, x);
    if ( Mid < p[x].r ) rs(root) = Query(rs(root), Mid + 1, r, x);
    return root;
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("jump23.in", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int root = 0;
    read(n); read(m); read(w); read(h);
    REP(i, 1, n) { read(a[i].x); read(a[i].y); a[i].id = i; }
    sort(a + 1, a + n + 1);
    REP(i, 1, m) { read(p[i].p); read(p[i].t); read(p[i].l); read(p[i].r); read(p[i].d); read(p[i].u); }
    sort(p + 1, p + m + 1);
    REP(i, 1, m) h1[i] = p[i].p;
    REP(i, 1, n) h2[i] = a[i].x;
    p1.pos = 1; p1.dis = 0; Heap :: Insert(p1);
    memset(dis, 0x3f, sizeof(dis)); dis[1] = 0;
    REP(i, 2, n)
    {
        while ( vis[Heap :: top().pos] ) Heap :: Delete();
        p1 = Heap :: top(); Heap :: Delete(); vis[p1.pos] = true;
        int x = lower_bound(h1 + 1, h1 + m + 1, p1.pos) - h1;
        if ( x > m ) continue ;
        while ( h1[x] == p1.pos && x <= m ) 
        {
            root = Query(root, 1, w, x);
            ++ x;
        }
    }
    REP(i, 2, n) printf("%d\n", dis[i]);
    return 0;
}
