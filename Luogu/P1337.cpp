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

const int maxn = 1010;
const double eps = 1e-14;
const double delta = 0.998;

double ansx, ansy, ans = 1e18, t;
int n, Sumx, Sumy;

struct node
{
    int u, v, w;
}a[maxn];

inline double js(double x, double y)
{
    double sum = 0;
    REP(i, 1, n)
    {
        double Deltax = x - a[i].u, Deltay = y - a[i].v;
        sum += sqrt(Deltax * Deltax + Deltay * Deltay) * a[i].w;
    }
    return sum;
}

inline void Run(double x, double y)
{
    t = 3000;
    while ( t > eps ) 
    {
        double X = (rand() * 2 - RAND_MAX) * t + x;
        double Y = (rand() * 2 - RAND_MAX) * t + y;
        double now = js(X, Y);
        double Delta = now - ans;
        if ( Delta < 0 ) 
        {
            x = X; y = Y; ansx = X; ansy = Y; ans = now;
        }
        else 
            if ( exp(-Delta / t) * RAND_MAX > rand() ) { x = X; y = Y; }
        t *= delta;
    }
}

inline void Solve()
{
    ansx = Sumx * 1.0 / n; ansy = Sumy * 1.0 / n;
    Run(ansx, ansy); Run(ansx, ansy); Run(ansx, ansy);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    srand(1314); srand(rand()); srand(rand());
    scanf("%d", &n);
    REP(i, 1, n) 
    {
        scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
        Sumx += a[i].u; Sumy += a[i].v;
    }
    Solve();
    printf("%.3lf %.3lf\n", ansx, ansy);
    return 0;
}
