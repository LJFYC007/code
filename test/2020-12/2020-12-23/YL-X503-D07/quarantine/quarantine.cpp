/***************************************************************
	File name: quarantine.cpp
	Author: ljfcnyali
	Create time: 2020年12月23日 星期三 19时59分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 19491001;

int n, k, q;
struct Matrix
{
    int a[25][25];
    Matrix operator * (Matrix b) 
    {
        Matrix c;
        REP(i, 1, k) REP(j, 1, k) { c.a[i][j] = 0; REP(o, 1, k) c.a[i][j] += a[i][o] * b.a[o][j]; c.a[i][j] %= Mod; }
        return c;
    }
} a[maxn], Tree[maxn], E, b, t;
char s1[maxn], s2[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root] = a[l]; return ; } 
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Tree[root] = Tree[lson] * Tree[rson];
}

inline void Modify(int root, int l, int r, int pos, int x, int y)
{
    if ( l == r ) { Tree[root].a[x][y] = Tree[root].a[x][y] > 0 ? 0 : rand() % Mod; return ; }
    int Mid = l + r >> 1; 
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, x, y);
    else Modify(rson, Mid + 1, r, pos, x, y);
    Tree[root] = Tree[lson] * Tree[rson];
}

inline void Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) { b = b * Tree[root]; return ; }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Query(lson, l, Mid, L, R);
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
}

inline int Solve(Matrix a)
{
    bool use[25]; mem(use); int ans = 0;
    REP(i, 1, k)
    {
        int pos = -1;
        REP(j, 1, k) if ( !use[j] && a.a[j][i] ) { pos = j; break ; } 
        if ( pos == -1 ) continue ;
        swap(use[pos], use[i]); use[i] = true;
        REP(j, 1, k) { swap(a.a[pos][j], a.a[i][j]); }
        int tmp = power(a.a[i][i], Mod - 2);
        REP(j, 1, k) if ( i != j ) 
        {
            int val = a.a[j][i] * tmp % Mod;
            REP(o, 1, k) a.a[j][o] = (a.a[j][o] - val * a.a[i][o]) % Mod;
        }
    }
    map<vector<int>, bool> Map;
    vector<int> p; Map[p] = true;
    REP(i, 1, k)
    {
        vector<int> p;
        REP(j, 1, k) if ( a.a[i][j] ) p.push_back(j);
        if ( !Map.count(p) ) { ++ ans; Map[p] = true; } 
    }
    return ans;
}

signed main()
{
    freopen("quarantine.in", "r", stdin);
    freopen("quarantine.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &k, &q);
    REP(i, 1, n - 1) REP(x, 1, k) REP(y, 1, k) { scanf("%1lld", &a[i].a[x][y]); if ( a[i].a[x][y] ) a[i].a[x][y] = rand() % Mod; }
    REP(i, 1, k) E.a[i][i] = 1;
    Build(1, 1, n - 1);
    while ( q -- ) 
    {
        getchar(); char c = getchar();        
        if ( c == 'T' ) { int i, u, v; scanf("%lld%lld%lld", &i, &u, &v); Modify(1, 1, n - 1, i, u, v); continue ; }
        int l, r; scanf("%lld%lld%s%s", &l, &r, s1 + 1, s2 + 1);
        b = E; Query(1, 1, n - 1, l, r - 1);
        int num = 0; mem(t.a);
        REP(i, 1, k) if ( s1[i] == '1' ) 
        {
            int m = 0; ++ num;
            REP(j, 1, k) if ( s2[j] == '1' ) t.a[num][++ m] = b.a[i][j];
        }

        printf("%lld\n", Solve(t)); 
    }
    return 0;
}
