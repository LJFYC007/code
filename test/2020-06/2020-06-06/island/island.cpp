/***************************************************************
    File name: island.cpp
    Author: ljfcnyali
    Create time: 2020年06月06日 星期六 07时59分46秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;
 
const int maxn = 1e6 + 1e3;
const int Mod = 998244353;
const int inv2 = (Mod + 1) / 2;
const int inv3 = 332748118;
const int inv6 = inv2 * inv3 % Mod;
const int INF = 1e18;
 
int n, l[maxn], r[maxn], h[maxn], ans, H1[maxn], H2[maxn], H3[maxn], H4[maxn];
int Min[maxn][21], a[maxn][21], p[maxn];
char s[3];
 
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
 
inline int Get(int l, int r) { return l <= r ? ((r - l + 1) * (l + r) / 2) % Mod : 0; }
 
inline int Get2(int n) { return ((n * (n + 1) % Mod) * (2 * n + 1) % Mod) * inv6 % Mod; }
 
inline int Find(int l, int r, int val)
{
    int num = (H1[r] - H1[l - 1]) % Mod, ret = (H2[r] - H2[l - 1]) % Mod;
    ret = (ret - 2 * val * num) % Mod;
    ret = (ret + (val * val % Mod) * (r - l + 1)) % Mod;
    ret = (ret - val * (r - l + 1)) % Mod;
    ret = (ret + num) % Mod;
    return ret * inv2 % Mod;
}
 
inline void Build()
{
    REP(i, 1, n) { Min[i][0] = h[i]; a[i][0] = i; }
    for ( int i = n; i >= 1; -- i ) REP(j, 1, 20) 
    { 
        if ( i + (1 << j) - 1 > n ) continue ;
        if ( Min[i][j - 1] < Min[i + (1 << j - 1)][j - 1] )
        {
            Min[i][j] = Min[i][j - 1];
            a[i][j] = a[i][j - 1];
        }
        else
        {
            Min[i][j] = Min[i + (1 << j - 1)][j - 1];
            a[i][j] = a[i + (1 << j - 1)][j - 1];
        }
    }
}
 
inline int st(int l, int r)
{
    int x = p[r - l + 1];
    if ( Min[l][x] < Min[r - (1 << x) + 1][x] ) return a[l][x];
    return a[r - (1 << x) + 1][x];
}

inline int calc(int X, int Y)
{
    int ret = 0, sum1, sum2;
    sum1 = (Get(1, X - 1) + Get2(X - 1)) * inv2 % Mod;
    sum2 = (Get(1, Y - 1) + Get2(Y - 1)) * inv2 % Mod;
    if ( X == 1 || Y == 1 ) ret = (sum1 + sum2) % Mod;
    else ret = (sum1 * (Y * Y % Mod) + sum2 * (X * X % Mod)) % Mod;
    return ret;
}
 
inline void Solve(int l, int r, int dep)
{
    if ( l > r ) return ;
    int pos = st(l, r), Min = h[pos];
 
    int X = r - l + 1, Y = Min - dep, ret = 0, sum1 = 0, sum2 = 0, num1 = 0, num2 = 0;
    sum1 = (Get(1, X - 1) + Get2(X - 1)) * inv2 % Mod;
    sum2 = (Get(1, Y - 1) + Get2(Y - 1)) * inv2 % Mod;
    if ( X == 1 || Y == 1 ) ret = (sum1 + sum2) % Mod;
    else ret = (sum1 * (Y * Y % Mod) + sum2 * (X * X % Mod)) % Mod;
 
    int num1L = (H1[pos - 1] - H1[l - 1]) % Mod;
    int num1R = (H1[r] - H1[pos]) % Mod;
 
    sum1 = Find(l, pos - 1, Min + 1);
    num1 = (num1L - Min * (pos - l)) % Mod;
    sum2 = Find(pos + 1, r, Min);
    num2 = (num1R - Min * (r - pos)) % Mod;
    ret = (ret + sum1 * num2 + sum2 * num1) % Mod;
    ret = (ret + num1 * num2) % Mod;
 
    sum2 = (pos * num1L - (H3[pos - 1] - H3[l - 1]) - Min * (pos * (pos - l) % Mod) + Get(l, pos - 1) * Min) % Mod;
    ret = (ret + sum2 * num2) % Mod;
    sum2 = (-pos * num1R + (H3[r] - H3[pos]) + Min * (pos * (r - pos) % Mod) - Get(pos + 1, r) * Min) % Mod;
    ret = (ret + sum2 * num1) % Mod;
 
    int num = X * Y % Mod;
    ret = (ret + Find(l, r, Min) * num) % Mod;
    sum2 = Get(1, Y - 1) * X % Mod;
    ret = (ret + sum2 * ((H1[r] - H1[l - 1] - Min * (r - l + 1)) % Mod)) % Mod;
     
 
    num = (r * r + l * l + r - l) % Mod;
    num = num * ((H1[r] - H1[l - 1] - Min * (r - l + 1)) % Mod) % Mod;
    num = (num - (H3[r] - H3[l - 1]) * (2 * r + 2 * l)) % Mod;
    num = (num + 2 * (H4[r] - H4[l - 1])) % Mod;
    int val = 2 * (Get2(r) - Get2(l - 1)) % Mod;
    val = (Get(l, r) * (2 * l + 2 * r) - val) % Mod;
    num = (num + val * Min) % Mod;
    num = num * inv2 % Mod;
    ret = (ret + num * Y) % Mod;
 
    ans = (ans + ret) % Mod;
 
    Solve(l, pos - 1, Min);
    Solve(pos + 1, r, Min);
}
 
inline void read(int &x)
{
    x = 0; char c = getchar();
    bool flag = false;
    while ( c < '0' || c > '9' ) { if ( c == '-' ) flag = true; c = getchar(); }
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
    if ( flag ) x = -x;
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);
#endif
    scanf("%lld%s", &n, s);
    REP(i, 1, n) read(l[i]), read(r[i]);
    if ( s[0] == 'A' && s[1] == '1' ) { printf("%lld\n", (2 * calc(r[1] - l[1], n) + Mod) % Mod); puts(""); return 0; }
    if ( s[0] == 'A' && s[1] == '3' ) { printf("%lld\n", (2 * calc(r[1] - l[1], n) + Mod) % Mod); puts(""); return 0; }
    p[1] = 0; REP(i, 2, n) p[i] = p[i / 2] + 1;
 
    int sum1 = 0, sum2 = 0, num1 = 0, num2 = 0, sum = 0, num = 0;
    for ( int i = n; i >= 1; -- i ) 
    {
        sum = (sum + Get(1, r[i] - 1)) % Mod;
        num = (num + r[i]) % Mod;
        num2 = (num2 + r[i]) % Mod; 
        sum2 = (sum2 + num2) % Mod;
    }
    REP(i, 1, n)
    {
        sum2 = (sum2 - num2) % Mod; 
        num2 = (num2 - r[i]) % Mod;
        int ret = (sum1 + sum2 + sum) % Mod;
        ans = (ans + ret * (-l[i]) + num * Get(1, -l[i])) % Mod;
        num1 = (num1 + r[i]) % Mod;
        sum1 = (sum1 + num1) % Mod; 
    }

    REP(i, 1, n) 
    { 
        h[i] = -l[i]; 
        H1[i] = (H1[i - 1] + h[i]) % Mod; 
        H2[i] = (H2[i - 1] + h[i] * h[i]) % Mod; 
        H3[i] = (H3[i - 1] + h[i] * i) % Mod; 
        H4[i] = (H4[i - 1] + (h[i] * i % Mod) * i) % Mod; 
    }
    Build(); Solve(1, n, 0);
    REP(i, 1, n) 
    { 
        h[i] = r[i]; 
        H1[i] = (H1[i - 1] + h[i]) % Mod; 
        H2[i] = (H2[i - 1] + h[i] * h[i]) % Mod; 
        H3[i] = (H3[i - 1] + h[i] * i) % Mod; 
        H4[i] = (H4[i - 1] + (h[i] * i % Mod) * i) % Mod; 
    }
    Build(); Solve(1, n, 0);
    ans = ans * 2 % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
