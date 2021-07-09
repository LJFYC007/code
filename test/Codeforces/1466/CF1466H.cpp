/***************************************************************
	File name: CF1466H.cpp
	Author: ljfcnyali
	Create time: 2021年01月06日 星期三 20时52分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 41;
const int Mod = 1e9 + 7;

int n, m, a[maxn], fac[maxn], inv[maxn], g[maxn][maxn][maxn], siz[maxn], belong[maxn];
bool vis[maxn];
map<vector<int>, int> Map[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 

inline int Solve(vector<int> a, int lst) ;

inline int DFS(vector<int> b, int x, vector<int> a, int lst, int sum, int num, int i)
{
    if ( x == m ) 
    {
        if ( sum == i ) return 0;
        return Solve(b, sum - i) * num % Mod;
    }
    int ret = 0;
    REP(j, a[x], siz[belong[x]]) 
    {
        b.push_back(j);
        ret += DFS(b, x + 1, a, lst, sum + belong[x] * j, num * 
         C(siz[belong[x]] - a[x], j - a[x]) % Mod * power(g[i][lst][belong[x]], j - a[x]) % Mod, i);
        b.pop_back();
    }
    return ret % Mod;
}

inline int Solve(vector<int> a, int lst)
{
    if ( Map[lst].count(a) ) return Map[lst][a];
    int sum = 0; REP(i, 0, m - 1) sum += a[i] * belong[i];
    // cerr << a.size() << endl;
    if ( sum == n ) return 1;
    vector<int> b; int ret = DFS(b, 0, a, lst, 0, 1, sum);
    Map[lst][a] = ret; return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 0, n - 1) REP(j, 0, n) REP(k, 1, n)
    {
        if ( j == 0 ) { g[i][j][k] = power(fac[n - 1], k); continue ; } 
        int num1 = 0, num2 = 0;
        REP(o, 0, i) 
        {
            num1 = (num1 + C(i, o) * fac[o] % Mod * fac[n - o - 1]) % Mod;
            num2 = (num2 + C(i - j, o) * fac[o] % Mod * fac[n - o - 1]) % Mod;
        }
        g[i][j][k] = (power(num1, k) - power(num2, k)) % Mod;
    }
    REP(i, 1, n) if ( !vis[i] ) 
    {
        int cnt = 0, x = i;
        while ( !vis[a[x]] ) { vis[a[x]] = true; x = a[x]; ++ cnt; }
        ++ siz[cnt];
    }
    REP(i, 1, n) if ( siz[i] ) belong[m ++] = i;
    vector<int> p; REP(i, 1, m) p.push_back(0);
    printf("%lld\n", (Solve(p, 0) + Mod) % Mod);
    return 0;
}
