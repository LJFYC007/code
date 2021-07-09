/***************************************************************
	File name: operator.cpp
	Author: ljfcnyali
	Create time: 2020年11月04日 星期三 10时47分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;
const int maxm = 5010;

int n, k, m, f[maxm][maxm], g[maxm][maxm], val[maxn], t[maxn];
int fac[maxn], inv[maxn], ans, h[maxm][maxm], pre[maxm], len[maxn];
pii a[maxn];
char s[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline void Solve(int x, int l, int r)
{
    vector<pii> p; p.clear(); 
    vector<int> son;
    bool vis[maxn]; REP(i, l, r) vis[i] = false;
    for ( int i = l; i <= r; ++ i ) 
    {
        if ( s[i] != '(' ) continue ;
        int j = i, num = 1;
        while ( num > 0 ) 
        { 
            if ( s[j + 1] == '(' ) ++ num; 
            if ( s[j + 1] == ')' ) -- num;
            ++ j;
        }
        ++ m; a[m] = pii(i, j); son.push_back(m); Solve(m, i + 1, j - 1);
        REP(o, i, j) vis[o] = true;
        p.push_back(pii(i, j)); i = j;
    }
    int N = 0, pos = 0;
    REP(i, l, r)
    {
        if ( vis[i] ) 
        { 
            val[++ N] = -1; pre[N] = t[a[son[pos]].second] - t[l]; 
            len[N] = t[a[son[pos]].second] - t[a[son[pos]].first];
            i = a[son[pos]].second; ++ pos; continue ; 
        }
        if ( s[i] < '1' || s[i] > '9' ) continue ;
        int x = 0; pre[++ N] = t[i] - t[l];
        while ( s[i] >= '0' && s[i] <= '9' ) { x = x * 10 + s[i] - '0'; ++ i; }
        val[N] = x;
    }

    REP(i, 1, N) REP(j, 0, k) f[i][j] = g[i][j] = 0;      
    pos = 0;
    if ( val[1] == -1 ) { REP(i, 0, k) g[1][i] = h[son[pos]][i]; ++ pos; }
    else g[1][0] = val[1];
    REP(i, 1, N - 1) 
    {
        REP(j, 0, min(k, pre[i + 1])) 
        {
            if ( val[i + 1] == -1 ) REP(o, 0, k - j)
            {
                if ( j > pre[i] || !h[son[pos]][o] ) break ; 
                f[i + 1][j + o] = (f[i + 1][j + o] + f[i][j] * C(len[i + 1], o)) % Mod;
                f[i + 1][j + 1 + o] = (f[i + 1][j + 1 + o] + (f[i][j] + g[i][j]) * C(len[i + 1], o))% Mod;
                g[i + 1][j + o] = (g[i + 1][j + o] + g[i][j] * h[son[pos]][o]) % Mod;
                g[i + 1][j + 1 + o] = (g[i + 1][j + 1 + o] + C(pre[i], j) * h[son[pos]][o]) % Mod;
            }
            else
            {
                f[i + 1][j] = (f[i + 1][j] + f[i][j]) % Mod;
                f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j] + g[i][j]) % Mod; 
                g[i + 1][j] = (g[i + 1][j] + g[i][j] * val[i + 1]) % Mod;
                g[i + 1][j + 1] = (g[i + 1][j + 1] + C(pre[i], j) * val[i + 1]) % Mod; 
            }
        }
        if ( val[i + 1] == -1 ) ++ pos; 
    }
    REP(i, 0, min(k, pre[N])) h[x][i] = (f[N][i] + g[N][i]) % Mod;
}

namespace Fucku
{
    inline int main()
    {
        REP(i, 1, n)
        {
            if ( s[i] < '1' || s[i] > '9' ) continue ;
            int x = 0;
            while ( s[i] >= '0' && s[i] <= '9' ) { x = x * 10 + s[i] - '0'; ++ i; }
            val[++ m] = x; 
        }
        g[1][0] = val[1];
        REP(i, 1, m - 1) REP(j, 0, k) 
        {
            f[i + 1][j] = (f[i + 1][j] + f[i][j]) % Mod;
            f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j] + g[i][j]) % Mod; 
            g[i + 1][j] = (g[i + 1][j] + g[i][j] * val[i + 1]) % Mod;
            g[i + 1][j + 1] = (g[i + 1][j + 1] + C(i - 1, j) * val[i + 1]) % Mod; 
        }
        printf("%lld\n", (f[m][k] + g[m][k] + Mod) % Mod);
        return 0;
    }
}

signed main()
{
    freopen("operator.in", "r", stdin);
    freopen("operator.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%s", s + 1);
    REP(i, 1, n) t[i] = t[i - 1] + (s[i] == '-');
    m = 1; a[1] = pii(1, n); Solve(1, 1, n);
    printf("%lld\n", (h[1][k] + Mod) % Mod);
    return 0;
}
