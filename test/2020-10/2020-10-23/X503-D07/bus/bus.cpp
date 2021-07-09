/***************************************************************
	File name: bus.cpp
	Author: ljfcnyali
	Create time: 2020年10月23日 星期五 09时03分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e18;
const double eps = 1e-12;

int n, m, c[maxn], v[maxn], f[maxn];
deque<int> Q[11][11];

inline int get(int x, int y)
{
    return f[x] + (y - x) / c[x] * v[x];
}

inline double getpos(int x, int y)
{
    return 1.0 * (f[y] * c[x] - y * v[y] + x * v[x] - f[x] * c[x]) / (v[x] - v[y]);
}

inline void Maintain(int x)
{
    int num = x % c[x];
    while ( !Q[c[x]][num].empty() && v[Q[c[x]][num].front()] >= v[x] ) Q[c[x]][num].pop_front();

    if ( !Q[c[x]][num].empty() ) 
    {
        int t = Q[c[x]][num].front(); Q[c[x]][num].pop_front();
        double pos = getpos(t, x);
        while ( !Q[c[x]][num].empty() && getpos(Q[c[x]][num].front(), x) < pos + eps )
        {
            t = Q[c[x]][num].front();
            pos = getpos(t, x);
            Q[c[x]][num].pop_front();
        }
        Q[c[x]][num].push_front(t);
    }

    Q[c[x]][num].push_front(x);
}

signed main()
{
    freopen("bus.in", "r", stdin);
    freopen("bus.out", "w", stdout);
    scanf("%lld%lld", &n, &m);    
    REP(i, 0, n - 1) scanf("%lld%lld", &c[i], &v[i]);
    REP(i, 1, n) f[i] = INF; 
    REP(i, 1, n)
    {
        if ( f[i - 1] != INF ) Maintain(i - 1);
        REP(j, 1, m)
        {
            int num = i % j;
            if ( Q[j][num].empty() ) continue ;
            int t = Q[j][num].front(); Q[j][num].pop_front();
            while ( !Q[j][num].empty() && get(t, i) >= get(Q[j][num].front(), i) )
            {
                t = Q[j][num].front(); Q[j][num].pop_front();
            }
            Q[j][num].push_front(t);
            f[i] = min(f[i], get(t, i));
        }
        // int Min = INF;
        // REP(j, 0, i - 1) if ( (i - j) % c[j] == 0 ) Min = min(Min, f[j] + v[j] * (i - j) / c[j]);
        // assert(Min == f[i]);
        // printf("%lld ", Min == INF ? -1 : Min);
        // if ( Min != f[i] ) cout << i << endl;
    }
    // puts("");
    REP(i, 1, n) printf("%lld ", f[i] == INF ? -1 : f[i]); puts("");
    return 0;
}
