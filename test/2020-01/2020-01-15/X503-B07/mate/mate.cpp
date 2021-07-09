/***************************************************************
	File name: mate.cpp
	Author: ljfcnyali
	Create time: 2020年01月15日 星期三 08时21分59秒
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
const int Mod = 1e9 + 7;

int n, m1, m2, a[maxn], p1[maxn], p2[maxn], sum, num1, num2, num3, f[maxn][2], g[maxn];
bool vis[maxn], flag;
vector<int> p;

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

inline int GetFac(int x)
{
    int ret = 1;
    REP(i, 2, x) ret = ret * i % Mod;
    return ret;
}

inline void DFS(int x, int y, int opt)
{
    if ( opt == 1 && (!p1[x] && !p1[y]) ) flag = true;
    if ( opt == 2 && (!p2[x] && !p2[y]) ) flag = true;
    if ( flag == true ) return ;
    if ( opt == 1 && p1[x] && p1[y] ) DFS(p1[x], p1[y], 2);
    else if ( opt == 2 && p2[x] && p2[y] ) DFS(p2[x], p2[y], 1);
}

inline void Solve(int x)
{
    p.clear(); vis[x] = true; queue<int> Q; Q.push(x);
    while ( !Q.empty() ) 
    {
        int x = Q.front(); Q.pop(); p.push_back(x);
        if ( !vis[p1[x]] && p1[x] ) { vis[p1[x]] = true; Q.push(p1[x]); }
        if ( !vis[p2[x]] && p2[x] ) { vis[p2[x]] = true; Q.push(p2[x]); }
    }
    int sum1 = 0, sum2 = 0, num = 0;

    for ( auto i : p )
    {
        if ( p1[i] ) ++ sum1;
        if ( p2[i] ) ++ sum2;
        if ( !p1[i] || !p2[i] ) ++ num;
    }
    sum1 /= 2; sum2 /= 2;
    if ( num == 2 && sum1 + sum2 + 1 == p.size() ) { ++ f[sum1 + sum2][sum1 % 2]; return ; }

    sum1 = sum2 = 0;
    for ( auto i : p ) { if ( p1[i] ) ++ sum1; if ( p2[i] ) ++ sum2; }
    flag = false;
    for ( auto i : p ) if ( !p1[i] || !p2[i] ) flag = true;
    if ( sum1 == sum2 && !flag ) { sum = sum * sum1 % Mod; ++ g[sum1]; return ; }
    for ( auto i : p ) 
    {
        if ( p1[i] && p2[i] && p1[p2[i]] ) 
        {
            flag = false;
            DFS(i, p2[i], 1);
            if ( flag == true ) { sum = sum * 2 % Mod; return ; }
        }
        if ( p1[i] && p2[i] && p2[p1[i]] )
        {
            flag = false;
            DFS(i, p1[i], 2);
            if ( flag == true ) { sum = sum * 2 % Mod; return ; }
        }
    }
}

inline int Get(int x)
{
    int ret = 1;
    REP(i, 1, x) ret = ret * i * 2 % Mod;
    return ret;
}

signed main()
{
    freopen("mate.in", "r", stdin);
    freopen("mate.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m1, &m2);
    REP(i, 1, m1) { int u, v; scanf("%lld%lld", &u, &v); p1[u] = v; p1[v] = u; }
    REP(i, 1, m2) { int u, v; scanf("%lld%lld", &u, &v); p2[u] = v; p2[v] = u; }
    REP(i, 1, n) if ( !p1[i] && !p2[i] ) ++ sum;
    sum = GetFac(sum); 
    REP(i, 1, n) 
    {
        if ( vis[i] ) continue ;
        if ( !vis[p1[i]] && p1[i] && !p2[i] && !p2[p1[i]] ) { ++ num1; vis[p1[i]] = vis[i] = true; continue ; }
        if ( !vis[p2[i]] && p2[i] && !p1[i] && !p1[p2[i]] ) { ++ num2; vis[p2[i]] = vis[i] = true; continue ; }
        if ( !vis[p1[i]] && p1[i] && p2[i] && p1[i] == p2[i] ) { ++ num3; vis[p1[i]] = vis[i] = true; continue ; }
        if ( !vis[p1[i]] && !vis[p2[i]] ) Solve(i);
    }
    sum = sum * Get(num1) % Mod;
    sum = sum * Get(num2) % Mod;
    sum = sum * Get(num3) % Mod;
    REP(i, 1, n) REP(j, 0, 1) 
    {
        sum = sum * GetFac(f[i][j]) % Mod;
        if ( i & 1 ) sum = sum * power(2, f[i][j]) % Mod;
    }
    REP(i, 1, n) sum = sum * GetFac(g[i]) % Mod;
    printf("%lld\n", sum);
    return 0;
}
