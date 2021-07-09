/***************************************************************
	File name: hybrid.cpp
	Author: ljfcnyali
	Create time: 2019年11月01日 星期五 08时39分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 20;
const int seed1 = 107;
const int seed2 = 131;
const int Mod1 = 998244353;
const int Mod2 = 1e9 + 7;

int n, m, k, a[maxn][maxn], p[maxn][2], ans;
bool flag, use[maxn][2];
map<int, bool> Map[3];
vector<int> f[3];

inline void Check()
{
    int ret1 = 0, ret2 = 0;
    REP(i, 1, n) REP(j, 1, m) 
    { 
        ret1 = (ret1 * seed1 + a[p[i][0]][p[j][1]] + 1) % Mod1; 
        ret2 = (ret2 * seed2 + a[p[i][0]][p[j][1]] + 1) % Mod2; 
    }
    if ( Map[1].count(ret1) && Map[2].count(ret2) ) flag = false;
    f[1].push_back(ret1); f[2].push_back(ret2);
}

inline void DFS1(int x, int opt)
{
    if ( !flag ) return ; 
    if ( !opt && x == n + 1 ) { DFS1(1, 1); return ; }
    if ( opt && x == m + 1 ) { Check(); return ; }
    REP(i, 1, !opt ? n : m) if ( !use[i][opt] ) { use[i][opt] = true; p[x][opt] = i; DFS1(x + 1, opt); use[i][opt] = false; }
}

inline void DFS(int x, int y)
{
    if ( y == m + 1 ) { y = 1; ++ x; }
    if ( x == n + 1 ) 
    { 
        flag = true; mem(use); f[1].clear(); f[2].clear(); DFS1(1, 0);  
        if ( flag ) ++ ans;
        for ( auto i : f[1] ) Map[1][i] = true;
        for ( auto i : f[2] ) Map[2][i] = true;
        return ; 
    }
    REP(i, 0, k - 1) { a[x][y] = i; DFS(x, y + 1); }
}

namespace Subtask1
{
#define int long long
    const int Mod = 998244353;

    inline int power(int a, int b) 
    { 
        int r = 1; 
        while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } 
        return r; 
    }

    inline int C(int n, int k)
    {
        int ret = 1;
        REP(i, k + 1, n) ret = ret * i % Mod;
        REP(i, 2, n - k) ret = ret * power(i, Mod - 2) % Mod;
        return ret;
    }

    inline int main()
    {
        printf("%lld\n", C(m + k - 1, k - 1));
        return 0;
    }
#undef int
}

int main()
{
    freopen("hybrid.in", "r", stdin);
    freopen("hybrid.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    if ( n > m ) swap(n, m);
    if ( n == 1 ) return Subtask1 :: main();
    DFS(1, 1);
    printf("%d\n", ans);
    return 0;
}
