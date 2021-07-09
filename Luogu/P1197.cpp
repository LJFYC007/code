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

const int maxn = 400010;

int f[maxn], n, m, k, ans, Begin[maxn], Next[maxn], To[maxn], e;
deque<int> a, b;
bool use[maxn];

struct node
{
    int u, v;
} p[maxn];

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { scanf("%d%d", &p[i].u, &p[i].v); add(p[i].u, p[i].v); add(p[i].v, p[i].u); }
    REP(i, 0, n - 1) { use[i] = true; f[i] = i; }
    scanf("%d", &k);
    REP(i, 1, k) 
    {
        int x; scanf("%d", &x); 
        a.push_back(x);
        use[x] = false;
    }
    REP(i, 1, m)
    {
        if ( use[p[i].u] && use[p[i].v] ) 
        {
            int fx = cha(p[i].u), fy = cha(p[i].v);
            if ( fx != fy ) f[fx] = fy; 
        }
    }
    REP(i, 0, n - 1) if ( f[i] == i && use[i] ) ++ ans;
    b.push_front(ans);
    while ( !a.empty() ) 
    {
        int x = a.back(); a.pop_back();
        use[x] = true;
        ++ ans;
        for ( int i = Begin[x]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( !use[v] ) continue ;
            int fx = cha(x), fy = cha(v);
            // printf("%d %d %d\n", x, fx, fy);
            if ( fx != fy ) { f[fx] = fy; -- ans; } 
        }
        b.push_front(ans);
    }
    while ( !b.empty() ) 
    {
        printf("%d\n", b.front());
        b.pop_front();
    } 
    return 0;
}
