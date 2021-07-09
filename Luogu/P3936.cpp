// luogu-judger-enable-o2
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 21;
const double eps = 1e-15;
const double Delta = 0.9999;
const double MAX_TIME = 4.8;

int n, m, c, p[51], a[maxn][maxn], ans = 0x3f3f3f3f, sum, out[maxn][maxn];
double T;
bool vis1[maxn][maxn], vis2[maxn][maxn];

inline int js()
{
    int sum = (n - 1) * m + n * (m - 1);
    mem(vis1); mem(vis2);
    REP(i, 1, n)
        REP(j, 1, m)
        {
            if ( a[i][j] == a[i][j - 1] ) vis1[i][j] = true;
            if ( a[i][j] == a[i][j + 1] ) vis1[i][j + 1] = true;
            if ( a[i][j] == a[i + 1][j] ) vis2[i + 1][j] = true;
            if ( a[i][j] == a[i - 1][j] ) vis2[i][j] = true;
        }
    REP(i, 1, n + 1)
        REP(j, 1, m + 1)
        {
            if ( vis1[i][j] == true ) -- sum;
            if ( vis2[i][j] == true ) -- sum;
        }
    return sum;
}

inline int JS(int x, int y)
{
    int sum = 0;
    if ( a[x][y] != a[x - 1][y] ) ++ sum;
    if ( a[x][y] != a[x + 1][y] ) ++ sum;
    if ( a[x][y] != a[x][y - 1] ) ++ sum;
    if ( a[x][y] != a[x][y + 1] ) ++ sum;
    return sum;
}

inline void update()
{
    REP(i, 1, n) REP(j, 1, m) out[i][j] = a[i][j];
}

inline void SA()
{
    T = 1; sum = js();
    while ( T > eps ) 
    {
        if ( (double)clock() / CLOCKS_PER_SEC >= MAX_TIME ) return ;
        int x1 = rand() % n + 1;
        int y1 = rand() % m + 1;
        int x2 = rand() % n + 1;
        int y2 = rand() % m + 1;
        while ( x1 == x2 && y1 == y2 ) y2 = rand() % m + 1;
        int now = sum;
        now -= JS(x1, y1) + JS(x2, y2);
        swap(a[x1][y1], a[x2][y2]);
        now += JS(x1, y1) + JS(x2, y2);
        int delta = now - ans;
        if ( delta < 0 ) { ans = now; sum = now; update(); }
        else if ( exp(-delta / T) * RAND_MAX > rand() ) 
        {
            if ( sum == now ) update(); 
            sum = now;
        }
        else swap(a[x1][y1], a[x2][y2]);
        T *= Delta;
    }        
}

inline void Solve()
{
    srand(1314); srand(rand()); srand(rand());
    while ( (double)clock() / CLOCKS_PER_SEC < MAX_TIME ) SA(); 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &c);
    int x = 1, y = 1;
    REP(i, 1, c) 
    {
        scanf("%d", &p[i]);
        REP(j, 1, p[i])
        {
            a[x][y] = i; ++ y;
            if ( y > m ) { ++ x; y = 1; }
        }
    }
    Solve();
    REP(i, 1, n)
    {
        REP(j, 1, m)
            printf("%d ", out[i][j]);
        puts("");
    }
    return 0;
}
