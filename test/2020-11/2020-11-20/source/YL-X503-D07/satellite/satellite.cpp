/***************************************************************
	File name: satellite.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 15时23分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, q, w, h, Mod, a, b, ans[maxn], numx[2010], numy[2010];
int f[2010][2010], X[2010], Y[2010], suf[2010][2010], pre[2010][2010];
struct node 
{
    int h, x, y; 
    node ( int a = 0, int b = 0, int c = 0 ) { h = a; x = b; y = c; }
} p[maxn];
vector<node> Q[2010][2010];
map<int, int> Mapx, Mapy;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("satellite.in", "r", stdin);
    freopen("satellite.out", "w", stdout);
    scanf("%lld%lld%lld%lld%lld%lld%lld", &n, &q, &w, &h, &Mod, &a, &b);
    REP(i, 1, n) { scanf("%lld%lld%lld", &p[i].h, &p[i].x, &p[i].y); Mapx[p[i].x] = Mapy[p[i].y] = true; }
    Mapx[w] = Mapy[h] = true;
    w = 0; for ( auto it : Mapx ) { ++ w; Mapx[it.first] = w; X[w] = it.first; }
    h = 0; for ( auto it : Mapy ) { ++ h; Mapy[it.first] = h; Y[h] = it.first; }
    REP(i, 1, n) { p[i].x = Mapx[p[i].x]; p[i].y = Mapy[p[i].y]; f[p[i].x][p[i].y] += p[i].h; }

    REP(i, 1, q) 
    { 
        int x, y; scanf("%lld%lld", &x, &y); 
        int posx = lower_bound(X + 1, X + w + 1, x) - X;
        int posy = lower_bound(Y + 1, Y + h + 1, y) - Y;
        Q[posx][posy].push_back(node(i, x, y)); 
    }

    X[w + 1] = X[w]; Y[h + 1] = Y[h];
    REP(i, 1, w + 1) numx[i] = power(a, X[i] - X[i - 1]);
    REP(i, 1, h + 1) numy[i] = power(b, Y[i] - Y[i - 1]);
    REP(j, 1, h) 
    {
        REP(i, 1, w) pre[i][j] = (pre[i - 1][j] * numx[i] + f[i][j]) % Mod;
        for ( int i = w; i >= 1; -- i ) suf[i][j] = (suf[i + 1][j] * numx[i + 1] + f[i][j]) % Mod;
    }

    REP(i, 1, w)
    {
        int val1 = 0, val2 = 0; 
        REP(j, 1, h)
        {
            for ( auto it : Q[i][j] ) 
            {
                int x = (val1 * power(a, it.x - X[i - 1]) + val2 * power(a, X[i] - it.x)) % Mod;
                ans[it.h] = (ans[it.h] + x * power(b, it.y - Y[j - 1])) % Mod;
            } 
            val1 = val1 * numy[j] % Mod;
            val2 = val2 * numy[j] % Mod;
            val1 = (val1 + pre[i - 1][j]) % Mod;
            val2 = (val2 + suf[i][j]) % Mod;
            // REP(k, 1, i - 1) val1 = (val1 + f[k][j] * power(a, X[i - 1] - X[k])) % Mod;
            // REP(k, i, w) val2 = (val2 + f[k][j] * power(a, X[k] - X[i])) % Mod;
        }
        val1 = val2 = 0;
        for ( int j = h; j >= 1; -- j ) 
        {
            val1 = (val1 + pre[i - 1][j]) % Mod;
            val2 = (val2 + suf[i][j]) % Mod;
            // REP(k, 1, i - 1) val1 = (val1 + f[k][j] * power(a, X[i - 1] - X[k])) % Mod;
            // REP(k, i, w) val2 = (val2 + f[k][j] * power(a, X[k] - X[i])) % Mod;
            for ( auto it : Q[i][j] ) 
            {
                int x = (val1 * power(a, it.x - X[i - 1]) + val2 * power(a, X[i] - it.x)) % Mod;
                ans[it.h] = (ans[it.h] + x * power(b, Y[j] - it.y)) % Mod;
            }
            val1 = val1 * numy[j] % Mod;
            val2 = val2 * numy[j] % Mod;
        }
    }
    REP(i, 1, q) printf("%lld\n", (ans[i] + Mod) % Mod);
    return 0;
}
