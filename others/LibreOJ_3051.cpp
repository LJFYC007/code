/***************************************************************
	File name: LibreOJ_3051.cpp
	Author: ljfcnyali
	Create time: 2020年06月17日 星期三 14时28分29秒
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
const int Mod = 998244353;

int n, m, c, C0, C1, D0, D1, w[maxn], p[maxn], k, f[2][2510][2510], g[2510][2510], h[2510][2510], id[maxn];
vector<pii> a[maxn];
bool vis1[maxn], vis2[maxn];

namespace Subtask
{
    int f[1010][2510], g[1010][2510];

    inline void main()
    {
        REP(i, 0, c) REP(j, 0, m) f[i][j] = 0;
        REP(i, 0, n) REP(j, 0, m) g[i][j] = 0;
        f[0][0] = g[0][0] = 1;
        int sum = 0;
        REP(i, 0, c - 1) 
        {
            if ( vis1[i + 1] ) 
            {
                REP(j, 0, m) f[i + 1][j] = f[i][j];
                continue ;
            }
            REP(j, 0, min(sum, m))
            {
                if ( j > C0 || sum - j > C1 ) continue ;
                if ( j + w[i + 1] <= C0 ) f[i + 1][j + w[i + 1]] = (f[i + 1][j + w[i + 1]] + f[i][j]) % Mod;
                if ( w[i + 1] && sum - j + w[i + 1] <= C1 ) f[i + 1][j] = (f[i + 1][j] + f[i][j]) % Mod;
            }
            sum += w[i + 1];
        }
        sum = 0;
        int now = 0;
        REP(o, 0, c - 1) for ( auto i : a[o + 1] ) 
        {
            if ( vis2[i.second] ) 
            {
                ++ now;
                REP(j, 0, m) g[now][j] = g[now - 1][j];
                continue ;
            }
            REP(j, 0, min(sum, m))
            {
                if ( j > D0 || sum - j > D1 ) continue ;
                if ( j + i.first <= D0 ) g[now + 1][j + i.first] = (g[now + 1][j + i.first] + g[now][j]) % Mod;
                if ( sum - j + i.first <= D1 ) g[now + 1][j] = (g[now + 1][j] + g[now][j]) % Mod;
            }
            sum += i.first; ++ now;
        }
        REP(i, 1, m) 
        {
            f[c][i] = (f[c][i] + f[c][i - 1]) % Mod;
            g[n][i] = (g[n][i] + g[n][i - 1]) % Mod;
        }
    }

    inline int Get(int l, int r, int L, int R)
    {
        if ( l > r || L > R ) return 0;
        if ( l < 0 && r < 0 ) return 0;
        if ( L < 0 && R < 0 ) return 0;
        l = max(0ll, l); r = max(0ll, r);
        L = max(0ll, L); R = max(0ll, R);
        return (f[c][r] - (l > 0 ? f[c][l - 1] : 0)) * (g[n][R] - (L > 0 ? g[n][L - 1] : 0)) % Mod;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T; scanf("%lld", &T);
    while ( T -- ) 
    {
        mem(vis1); mem(vis2); mem(w); mem(a);
        scanf("%lld%lld", &n, &c);
        REP(i, 1, n) p[i] = -1;
        scanf("%lld%lld%lld%lld", &C0, &C1, &D0, &D1);
        m = max(max(C0, C1), max(D0, D1));
        int s = 0;
        REP(i, 1, n) 
        { 
            int x, y; scanf("%lld%lld", &x, &y); 
            a[x].push_back(pii(y, i)); w[x] += y; 
            id[i] = x;
        }
        scanf("%lld", &k);
        REP(i, 1, k) 
        { 
            int x, y; scanf("%lld%lld", &x, &y); 
            p[x] = y; vis1[id[x]] = vis2[x] = true; 
        }
        REP(i, 1, c) s += w[i];

        Subtask :: main();

        REP(o, 0, 1) REP(i, 0, m) REP(j, 0, m) f[o][i][j] = 0;
        f[0][0][0] = 1; 
        int sum1 = 0, sum2 = 0, now = 0;
        REP(o, 1, c) 
        {
            if ( !a[o].size() || !vis1[o] ) continue ;
            now ^= 1;
            REP(x, 0, m) REP(y, 0, m) f[now][x][y] = 0;
            int num1, num2, cur = 0;

            for ( auto i : a[o] ) if ( !vis2[i.second] ) cur += i.first;

            REP(j, 0, 1) 
            {
                num1 = sum1 + cur; num2 = sum2;
                REP(x, 0, m) REP(y, 0, num2 + 10) g[x][y] = 0;
                REP(x, 0, m) REP(y, 0, num2 + 10) if ( x + (j ^ 1) * cur <= m ) g[x + (j ^ 1) * cur][y] = f[now ^ 1][x][y]; 

                for ( auto i : a[o] )
                {
                    if ( !vis2[i.second] ) continue ;
                    REP(x, 0, m) REP(y, 0, num2 + 10) h[x][y] = 0;
                    REP(x, 0, m) REP(y, 0, num2)
                    {
                        if ( num1 < x || num2 < y ) continue ;
                        if ( x > C0 || num1 - x > C1 || y > D0 || num2 - y > D1 ) continue ;
                        if ( j == 0 && x + i.first <= C0 && y + i.first <= D0 && p[i.second] != 0 ) (h[x + i.first][y + i.first] += g[x][y]) %= Mod;
                        if ( j == 0 && x + i.first <= C0 && num2 - y + i.first <= D1 && p[i.second] != 1 ) (h[x + i.first][y] += g[x][y]) %= Mod;
                        if ( j == 1 && num1 - x + i.first <= C1 && y + i.first <= D0 && p[i.second] != 2 ) (h[x][y + i.first] += g[x][y]) %= Mod;
                        if ( j == 1 && num1 - x + i.first <= C1 && num2 - y + i.first <= D1 && p[i.second] != 3 ) (h[x][y] += g[x][y]) %= Mod;
                    }
                    num1 += i.first; num2 += i.first;
                    REP(x, 0, m) REP(y, 0, num2) g[x][y] = h[x][y];
                }

                REP(x, 0, m) REP(y, 0, num2) f[now][x][y] = (f[now][x][y] + g[x][y]) % Mod;
            }
            sum1 = num1; sum2 = num2;
        }
        int ans = 0;
        REP(x, 0, C0) REP(y, 0, D0)
            ans = (ans + f[now][x][y] * Subtask :: Get(s - x - C1, C0 - x, s - y - D1, D0 - y)) % Mod;
        
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
