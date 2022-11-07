#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e9;

int n;
pii a[maxn], b[maxn];

inline pii operator + (pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
inline pii operator - (pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
inline int Getlen(pii x) { return x.x * x.x + x.y * x.y; }

inline void Get(pii &a, pii b)
{
    for ( int i = 30; i >= 0; -- i ) 
    {
        pii t = pii(b.x * (1 << i), b.y * (1 << i));
        if ( t.x > INF || t.y > INF || t.x < -INF | t.y < -INF ) continue ;
        if ( Getlen(a - t) < Getlen(a) ) a = a - t;
    }
}

inline pii Solve(pii a, pii b)
{
    if ( Getlen(a) == 0 || Getlen(b) == 0 ) return a + b;
    if ( Getlen(a) < Getlen(b) ) swap(a, b);
    Get(a, b);
    b = pii(-b.x, -b.y); Get(a, b);
    b = pii(b.y, -b.x); Get(a, b);
    b = pii(-b.x, -b.y); Get(a, b);
    return Solve(a, b);
}

signed main()
{
    freopen("3.in", "r", stdin);
    freopen("3.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld%lld", &a[i].x, &a[i].y);
    if ( n == 1 ) { puts("0"); return 0; }
    REP(i, 1, n - 1) b[i] = a[i + 1] - a[i]; 
    REP(i, 2, n - 1) b[i] = Solve(b[i - 1], b[i]);
    int s = b[n - 1].x, t = b[n - 1].y;
    REP(i, 2, n) b[i] = a[i] - a[1];  
    int Minx = 0, Maxx = 0, Miny = 0, Maxy = 0;
    if ( !t ) swap(s, t);
    REP(i, 2, n)
    {
        int x1 = (s * b[i].x + t * b[i].y) / (s * s + t * t);
        int y1 = (b[i].x - x1 * s) / t;
        Minx = min(Minx, x1); Maxx = max(Maxx, x1);
        Miny = min(Miny, y1); Maxy = max(Maxy, y1);
    }
    int ans = max(Maxx - Minx + 1, Maxy - Miny + 1);
    cout << ans * ans - n << endl;
    return 0;
}
