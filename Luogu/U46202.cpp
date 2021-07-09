#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define abs abss

const int maxn = 31;
const double MAX_TIME = 0.8;
const double eps = 1e-14;
const double Delta = 0.99;

int a[maxn], n, m, k1[maxn], k2[maxn], ans = 0x3f3f3f3f, sum, Ans, p[maxn];
bool vis[maxn];
double T;

inline void FZ(int x)
{
    REP(i, 1, x / 2) swap(a[i], a[x - i + 1]);
}

inline int js()
{
    int sum = 0;
    REP(i, 1, n) if ( a[i] == i ) ++ sum;
    return sum;
}

inline void SA()
{
    // puts("1");
    T = 1; Ans = 0;
    REP(i, 1, n) a[i] = p[i];
    sum = js();
    if ( sum == n ) { printf("0\n"); exit(0) ; }
    while ( T > eps ) 
    {
        int p = rand() % n + 1;
        FZ(p);
        int now = js();
        int delta = sum - now;
        ++ Ans;
        if ( delta <= 0 ) { sum = now; if ( js() == n ) ans = min(ans, Ans);}
        else if ( exp(-delta / T) * RAND_MAX > rand() ) sum = now;
        else { FZ(p); -- Ans; }
        T *= Delta;
    }  
}

inline void Solve()
{
    srand(13141314); srand(rand()); srand(rand());
    REP(i, 1, n) p[i] = a[i];
    while ( (double)clock() / CLOCKS_PER_SEC < MAX_TIME ) SA();
    printf("%d\n", ans);
}

inline void DFS(int x)
{
    if ( x == n + 1 )
    {
        Solve();
        exit(0);
    }
    REP(i, 1, n)
    {
        if ( vis[i] ) continue ;
        REP(j, 1, m) if ( (k1[j] == i && vis[k2[j]]) || (k2[j] == i && !vis[k1[j]]) ) goto no;
        a[x] = i; vis[i] = true;
        DFS(x + 1); 
        vis[i] = false;
no: ;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d%d", &k1[i], &k2[i]);
    DFS(1);
    printf("-1\n");
    return 0;
}
