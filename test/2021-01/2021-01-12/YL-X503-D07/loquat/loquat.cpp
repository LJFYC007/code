/***************************************************************
	File name: loquat.cpp
	Author: ljfcnyali
	Create time: 2021年01月12日 星期二 10时28分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 310;
const int Mod = 1e9 + 7;

int n, m, size[maxn], f[maxn];
map<int, int> g[maxn];
map<int, map<int, int> >h[maxn];
struct node { int u, v, x, y, w; } T[maxn];

inline int Solve3(int i, int j, int k)
{
    if ( i == 0 || j == k ) return 0;
    if ( j > k ) swap(j, k);
    if ( h[i][j].count(k) ) return h[i][j][k];
    int ret = 0;
    if ( k < size[T[i].x] ) ret = Solve3(T[i].x, j, k);
    else if ( j >= size[T[i].x] ) ret = Solve3(T[i].y, j - size[T[i].x], k - size[T[i].x]);
    else ret = (Solve3(T[i].x, j, T[i].u) + Solve3(T[i].y, T[i].v, k - size[T[i].x]) + T[i].w) % Mod;
    h[i][j][k] = ret; return ret;
}

inline int Solve2(int i, int j)
{
    if ( i == 0 ) return 0;
    if ( g[i].count(j) ) return g[i][j];
    int ret = 0;
    if ( j < size[T[i].x] ) 
        ret = (Solve2(T[i].x, j) + Solve2(T[i].y, T[i].v) + (T[i].w + Solve3(T[i].x, j, T[i].u)) * (size[T[i].y] % Mod)) % Mod;
    else 
        ret = (Solve2(T[i].y, j - size[T[i].x]) + Solve2(T[i].x, T[i].u) + (T[i].w + Solve3(T[i].y, j - size[T[i].x], T[i].v)) * (size[T[i].x] % Mod)) % Mod;
    g[i][j] = ret; return ret;
}

inline int Solve1(int i)
{
    if ( i == 0 ) return 0;
    if ( f[i] != -1 ) return f[i];
    int ret = (Solve1(T[i].x) + Solve1(T[i].y)) % Mod;
    ret = (ret + Solve2(T[i].x, T[i].u) * (size[T[i].y] % Mod)) % Mod;
    ret = (ret + Solve2(T[i].y, T[i].v) * (size[T[i].x] % Mod)) % Mod;
    ret = (ret + T[i].w * (size[T[i].x] % Mod) % Mod * (size[T[i].y] % Mod)) % Mod;
    f[i] = ret; return ret;
}

signed main()
{
    freopen("loquat.in", "r", stdin);
    freopen("loquat.out", "w", stdout);
    scanf("%lld", &m); size[0] = 1; REP(i, 0, m) f[i] = -1;
    REP(i, 1, m) 
    {
        scanf("%lld%lld%lld%lld%lld", &T[i].x, &T[i].y, &T[i].u, &T[i].v, &T[i].w);
        T[i].w %= Mod; size[i] = size[T[i].x] + size[T[i].y];
        printf("%lld\n", Solve1(i));
    }
    return 0;
}
