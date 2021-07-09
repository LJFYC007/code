/***************************************************************
	File name: calc.cpp
	Author: ljfcnyali
	Create time: 2020年05月22日 星期五 21时30分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define y1 hhakioi__orzhh__hhcs
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;

vector<int> a[maxn], b[maxn], c[maxn];
vector<pii> p[maxn];
int r, w, n, m, block, ans[maxn];
struct node1 
{ 
    int x1, y1, x2, y2; 
    node1 ( int x = 0, int y = 0 ) { x1 = x2 = x; y1 = y2 = y; }
} S[maxn];
struct node2 { int op, x, y, v; } Q[maxn];

namespace Matrix 
{
    int block;
    vector<int> sum[maxn];

    inline void INIT() { block = sqrt(w); REP(i, 1, r) sum[i].resize(w + 1); }

    inline int lowbit(int x) { return x & -x; }

    inline int get(int x, int pos)
    {
        int ret = 0;
        for ( int i = pos; i > 0; i -= lowbit(i) ) ret += sum[x][i];
        return ret;
    }

    inline void add(int x, int pos, int val)
    {
        for ( int i = pos; i <= w; i += lowbit(i) ) sum[x][i] += val;
    }

    inline int Query(int x, int y)
    {
        return get(x, y);
    }

    inline void Modify(node1 x)
    {
        REP(i, x.x1, x.x2)
        {
            add(i, x.y1, 1);
            add(i, x.y2 + 1, -1);
        }
    }
}

signed main()
{
    freopen("calc.in", "r", stdin);
    freopen("calc.out", "w", stdout);
    scanf("%lld%lld", &r, &w);    
    if ( r > w ) 
    {
        REP(i, 1, w) a[i].resize(r + 1);
        REP(i, 1, r) REP(j, 1, w) scanf("%lld", &a[j][i]);
        scanf("%lld", &n);
        REP(i, 1, n) scanf("%lld%lld%lld%lld", &S[i].y1, &S[i].x1, &S[i].y2, &S[i].x2);
        swap(r, w);
    }
    else
    {
        REP(i, 1, r) a[i].resize(w + 1);
        REP(i, 1, r) REP(j, 1, w) scanf("%lld", &a[i][j]);
        scanf("%lld", &n);
        REP(i, 1, n) scanf("%lld%lld%lld%lld", &S[i].x1, &S[i].y1, &S[i].x2, &S[i].y2);
    }
    scanf("%lld", &m);
    block = sqrt(m);
    REP(i, 1, m)
    {
        scanf("%lld", &Q[i].op);
        if ( !Q[i].op ) scanf("%lld%lld", &Q[i].x, &Q[i].y);
        else scanf("%lld%lld%lld", &Q[i].x, &Q[i].y, &Q[i].v);
    }
    c[0].resize(w + 1); 
    REP(i, 1, r) 
    {
        b[i].resize(w + 1);
        c[i].resize(w + 1);
        REP(j, 1, w) 
        {
            b[i][j] = a[i][j];
            c[i][j] = c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1] + b[i][j];
        }
    }
    for ( int L = 1, R = block; L <= m; L += block, R = min(m, R + block) ) 
    {
        REP(i, 1, n) p[i].clear();
        REP(i, L, R)
        {
            if ( Q[i].op == 1 ) continue ;
            p[Q[i].x - 1].push_back(pii(i, -1));
            p[Q[i].y].push_back(pii(i, 1));
        }
        int sum = 0;
        REP(i, 1, n) 
        {
            sum += c[S[i].x2][S[i].y2] - c[S[i].x1 - 1][S[i].y2] - c[S[i].x2][S[i].y1 - 1] + c[S[i].x1 - 1][S[i].y1 - 1];
            for ( auto j : p[i] ) ans[j.first] += sum * j.second;
        }
        REP(i, L, R)
        {
            if ( Q[i].op == 0 ) continue ;
            b[Q[i].x][Q[i].y] = Q[i].v;
        }
        REP(i, 1, r) REP(j, 1, w) c[i][j] = c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1] + b[i][j];
    }

    REP(i, 1, n) p[i].clear();
    REP(i, 1, m) 
    {
        if ( Q[i].op == 1 ) continue ;
        p[Q[i].x - 1].push_back(pii(i, -1));
        p[Q[i].y].push_back(pii(i, 1));
    }
    REP(i, 1, r) REP(j, 1, w) b[i][j] = a[i][j];
    REP(i, 1, m)
    {
        if ( Q[i].op == 0 ) continue ;
        int x = Q[i].v;
        Q[i].v = Q[i].v - b[Q[i].x][Q[i].y];
        b[Q[i].x][Q[i].y] = x;
    }

    Matrix :: INIT();
    REP(i, 1, n)
    {
        Matrix :: Modify(S[i]);
        for ( auto o : p[i] ) 
        {
            int x = ((o.first - 1) / block) * block + 1, sum = 0;
            REP(j, x, o.first - 1)
            {
                if ( Q[j].op == 0 ) continue ;
                sum += Matrix :: Query(Q[j].x, Q[j].y) * Q[j].v;
            }
            ans[o.first] += sum * o.second;
        }
    }
    REP(i, 1, m) if ( Q[i].op == 0 ) printf("%lld\n", ans[i]);
    return 0;
}
