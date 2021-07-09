/***************************************************************
	File name: CF506E.cpp
	Author: ljfcnyali
	Create time: 2020年05月20日 星期三 19时56分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;
const int Mod = 1e4 + 7;

int n, m, len, h[maxn][maxn][maxn];
bool vis[maxn][maxn][maxn];
char s[maxn];

struct Matrix
{
    int a[maxn][maxn];
} f, g;
Matrix operator * (Matrix a, Matrix b) 
{
    Matrix c; 
    REP(i, 1, len) REP(j, i, len)
    {
        c.a[i][j] = 0;
        REP(k, i, j) c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % Mod;
    }
    return c;
}

inline void power(int n)
{
    Matrix h = g; -- n; 
    int a[maxn];
    while ( n ) 
    {
        if ( n & 1 ) h = h * g;
        g = g * g; n >>= 1;
    }
    REP(i, 1, len) a[i] = 0;
    REP(i, 1, len) REP(j, 1, len) a[j] = (a[j] + f.a[i][i] * h.a[i][j]) % Mod;
    REP(i, 1, len) f.a[i][i] = a[i];
}

inline int DFS(int l, int r, int x)
{
    if ( x < 0 ) return 0;
    if ( vis[l][r][x] ) return h[l][r][x];
    vis[l][r][x] = true;
    if ( l == 1 && r == m ) h[l][r][x] = !x;
    if ( l > 1 && s[l - 1] != s[r] ) h[l][r][x] += DFS(l - 1, r, x - 1);
    if ( r < m && s[l] != s[r + 1] ) h[l][r][x] += DFS(l, r + 1, x - 1);
    if ( l > 1 && r < m && s[l - 1] == s[r + 1] ) h[l][r][x] += DFS(l - 1, r + 1, x);
    h[l][r][x] %= Mod; return h[l][r][x];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); m = str(s + 1); scanf("%d", &n);
    len = m + (m + 1) / 2;    
    REP(i, 0, m - 1)      
    {
        int num = (m - i + 1) / 2, sum = 0;
        REP(j, 1, m)
        {
            sum += DFS(j, j, i);
            if ( j < m && s[j] == s[j + 1] ) sum += DFS(j, j + 1, i);
        }
        if ( !i ) f.a[m][m] = sum; 
        else 
        {
            g.a[i][len - num] = sum; g.a[i][i] = 24;
            if ( i != 1 ) g.a[i - 1][i] = 1; else f.a[i][i] = 1;
        }
    }
    REP(i, m, len - 1) { g.a[i][i + 1] = 1; g.a[i][i] = 25; }
    g.a[len][len] = 26;
    power((n + m + 1) / 2); 
    if ( !((n + m) & 1) ) { printf("%d\n", f.a[len][len]); return 0; }

    int ans = f.a[len][len];
    mem(f.a); mem(g.a);
    REP(i, 0, m - 1)      
    {
        int num = (m - i + 1) / 2, sum = 0;
        REP(j, 1, m) if ( j < m && s[j] == s[j + 1] ) sum += DFS(j, j + 1, i);
        if ( !i ) f.a[m][m] = sum; 
        else 
        {
            g.a[i][len - num] = sum; g.a[i][i] = 24;
            if ( i != 1 ) g.a[i - 1][i] = 1; else f.a[i][i] = 1;
        }
    }
    REP(i, m, len - 1) { g.a[i][i + 1] = 1; g.a[i][i] = 25; }
    power((n + m + 1) / 2); 
    ans -= f.a[len][len];
    printf("%d\n", (ans + Mod) % Mod);
    return 0;
}
