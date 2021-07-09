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

const int maxn = 110;
const double Delta = 0.9998;
const double eps = 1e-14;
const double MAX_TIME = 0.7;

int p[maxn][maxn], q[maxn][maxn], n, a[maxn], ans;
double T; 

inline int js()
{
    int sum = 0;
    REP(i, 1, n)
        sum += p[i][a[i]] * q[a[i]][i];
    return sum;
}

inline void SA()
{
    REP(i, 1, n) a[i] = i;
    T = 600;
    while ( T > eps )
    {
        int x = rand() % n + 1, y = rand() % n + 1;
        while ( x == y ) y = rand() % n + 1;
        swap(a[x], a[y]);
        int now = js();
        int delta = ans - now;
        if ( delta < 0 ) ans = now;
        else if ( exp(-delta / T) * RAND_MAX > rand() ) ;
        else swap(a[x], a[y]);
        T *= Delta;
    }
}

inline void Solve()
{
    while ( (double)clock() / CLOCKS_PER_SEC < MAX_TIME ) SA();
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    srand(1314); srand(rand()); srand(rand());
    scanf("%d", &n);
    REP(i, 1, n) REP(j, 1, n) scanf("%d", &p[i][j]);
    REP(i, 1, n) REP(j, 1, n) scanf("%d", &q[i][j]);
    Solve();
    printf("%d\n", ans);
    return 0;
}
