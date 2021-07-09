/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年07月30日 星期四 14时32分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define inv(x) power(x, Mod - 2)
typedef long long LL;

const int maxn = 1 << 16;
const int Mod = 998244353;

int n, m, a[17], inv[17];
vector<int> f[17], g, h, H, G, F;
bool Edge[17][17];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = (LL)r * a % Mod; a = (LL)a * a % Mod; b >>= 1; } return r; }

inline vector<int> FWT(vector<int> f, int op)
{
    REP(Mid, 0, n - 1)
        for ( int i = 0; i < (1 << n); i += (1 << Mid + 1) )
            REP(j, 0, (1 << Mid) - 1)
                f[i + (1 << Mid) + j] = (f[i + (1 << Mid) + j] + f[i + j] * op) % Mod;
    return f;
}

vector<int> operator * (vector<int> a, vector<int> b)
{
    vector<int> f[17], g[17];
    REP(i, 0, n) { f[i].resize(1 << n); g[i].resize(1 << n); }
    REP(i, 0, (1 << n) - 1) 
    {
        f[__builtin_popcount(i)][i] = a[i];
        g[__builtin_popcount(i)][i] = b[i];
    }
    REP(i, 0, n) { f[i] = FWT(f[i], 1); g[i] = FWT(g[i], 1); }
    REP(i, 0, (1 << n) - 1) 
    {
        static int a[17]; REP(j, 0, n) a[j] = 0;
        REP(j, 0, n) REP(k, 0, n) if ( j + k <= n ) a[j + k] = (a[j + k] + (LL)f[j][i] * g[k][i]) % Mod;
        REP(j, 0, n) f[j][i] = a[j];
    }
    REP(i, 0, n) f[i] = FWT(f[i], -1);
    a.clear(); a.resize(1 << n);
    REP(i, 0, (1 << n) - 1) a[i] = f[__builtin_popcount(i)][i];
    return a;
}

inline vector<int> ln(vector<int> g)
{
    vector<int> f[20]; REP(i, 0, n) f[i].resize(1 << n);
    REP(i, 0, (1 << n) - 1) f[__builtin_popcount(i)][i] = g[i];
    REP(i, 0, n) f[i] = FWT(f[i], 1);
    REP(i, 0, (1 << n) - 1) 
    {
        REP(j, 0, n) a[j] = f[j][i];
        f[0][i] = 0;
        REP(k, 1, n)
        {
            int ret = (LL)k * a[k] % Mod;
            REP(j, 1, k - 1) ret = (ret - ((LL)j * f[j][i] % Mod) * a[k - j]) % Mod;
            f[k][i] = (LL)inv[k] * ret % Mod;
        }
    }
    REP(i, 0, n) f[i] = FWT(f[i], -1);
    REP(i, 0, (1 << n) - 1) g[i] = f[__builtin_popcount(i)][i];
    return g;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    int T; scanf("%d", &T);
    REP(i, 0, 20) inv[i] = inv(i);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m); 
        if ( n == 1 ) { puts("0"); continue ; }
        mem(Edge);
        REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); Edge[u][v] = Edge[v][u] = 1; }

        g.resize(1 << n); h.resize(1 << n);
        REP(i, 0, (1 << n) - 1)
        {
            int ret = 0;
            REP(j, 1, n) if ( (i >> j - 1) & 1 ) 
                REP(k, j + 1, n) if ( (i >> k - 1) & 1 ) 
                    ret += Edge[j][k];
            g[i] = power(2, ret);
        }
        f[0] = ln(g);
        REP(i, 0, (1 << n) - 1) g[i] = 0;
        REP(i, 1, n)
        {
            REP(j, 0, (1 << n) - 1) if ( (j >> i - 1) & 1 ) 
                g[j ^ (1 << i - 1)] = f[i - 1][j];
            g = ln(g); f[i] = f[i - 1];
            REP(j, 0, (1 << n) - 1) if ( !((j >> i - 1) & 1) )
                f[i][j ^ (1 << i - 1)] = g[j], g[j] = 0;
        }

        G = H = f[n];
        
        for ( int i = n; i >= 1; -- i ) 
        {
            REP(j, 0, (1 << n) - 1) g[j] = h[j] = 0;
            REP(j, 0, (1 << n) - 1) if ( (j >> i - 1) & 1 )
                g[j ^ (1 << i - 1)] = H[j], h[j ^ (1 << i - 1)] = f[i - 1][j];
            g = g * h;
            REP(j, 0, (1 << n) - 1) if ( !((j >> i - 1) & 1) )
                H[j ^ (1 << i - 1)] = g[j];

            F = G; 
            REP(j, 0, (1 << n) - 1) g[j] = h[j] = 0;
            REP(j, 0, (1 << n) - 1) if ( (j >> i - 1) & 1 )
                g[j ^ (1 << i - 1)] = G[j], h[j] = f[i - 1][j];
            g = g * h;
            REP(j, 0, (1 << n) - 1) if ( ((j >> i - 1) & 1) )
                G[j] = g[j]; 

            REP(j, 0, (1 << n) - 1) g[j] = h[j] = 0;
            REP(j, 0, (1 << n) - 1) if ( (j >> i - 1) & 1 )
                g[j ^ (1 << i - 1)] = F[j], h[j ^ (1 << i - 1)] = G[j];
            g = g * h;
            REP(j, 0, (1 << n) - 1) if ( !((j >> i - 1) & 1) )
                H[j ^ (1 << i - 1)] = (H[j ^ (1 << i - 1)] + g[j]) % Mod;
        }

        int ans = (G[(1 << n) - 1] + H[(1 << n) - 1]) % Mod;
        ans = (LL)ans * inv[2] % Mod;
        printf("%d\n", (ans + Mod) % Mod);
    }
    return 0;
}
