/***************************************************************
	File name: CF1464D.cpp
	Author: ljfcnyali
	Create time: 2020年12月28日 星期一 22时06分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int T, n, a[maxn], p[maxn], sum, ans;
bool vis[maxn];

inline void Get()
{
    ++ sum; if ( a[2] ) -- sum;
    for ( int i = 2; i <= n; i += 3 ) if ( a[i] ) { -- a[i]; ++ a[i - 2]; return ; } 
    for ( int i = 4; i <= n; i += 3 ) if ( a[i] ) { -- a[i]; ++ a[i - 2]; return ; } 
    if ( a[1] >= 2 ) { a[1] -= 2; return ; }
    for ( int i = 3; i <= n; i += 3 ) if ( a[i] ) { -- a[i]; ++ a[i - 2]; return ; } 
}

inline void Get2()
{
    ++ sum; if ( a[4] ) -- sum;
    for ( int i = 4; i <= n; i += 3 ) if ( a[i] ) { -- a[i]; ++ a[i - 4]; return ; } 
    if ( a[2] >= 2 ) { a[2] -= 2; -- sum; return ; }
    if ( a[2] ) for ( int i = 5; i <= n; i += 3 ) if ( a[i] ) { -- a[2]; -- a[i]; ++ a[i - 2]; return ; } 
    if ( a[1] >= 2 ) for ( int i = 2; i <= n; i += 3 ) if ( a[i] ) { -- a[i]; a[1] -= 2; ++ a[i - 2]; if ( i != 2 ) ++ sum; return ; } 
    if ( a[1] >= 4 ) { a[1] -= 4; ++ sum; return ; } 
    if ( a[1] ) for ( int i = 3; i <= n; i += 3 ) if ( a[i] ) { -- a[1]; -- a[i]; ++ a[i - 3]; if ( i != 3 ) ++ sum; return ; } 
    -- sum; Get(); Get(); 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n); REP(i, 1, n) scanf("%d", &p[i]);
        REP(i, 1, n) vis[i] = a[i] = 0;
        REP(i, 1, n) if ( !vis[i] )
        {
            int x = i, num = 0; 
            while ( !vis[p[x]] ) { ++ num; x = p[x]; vis[x] = true; }
            ++ a[num];
        }

        if ( n % 3 == 2 ) { ans = 2; for ( int i = 1; i <= n - 2; i += 3 ) ans = ans * 3 % Mod; }
        else if ( n % 3 == 0 ) { ans = 1; for ( int i = 1; i <= n; i += 3 ) ans = ans * 3 % Mod; }
        else if ( n % 3 == 1 ) { ans = 4; for ( int i = 1; i <= n - 4; i += 3 ) ans = ans * 3 % Mod; }
        printf("%d ", ans);

        ans = sum = 0; if ( n % 3 == 2 ) Get(); else if ( n % 3 == 1 ) Get2();
        REP(i, 4, n) { sum += a[i] * ((i - 1) / 3); a[i % 3] += a[i]; }
        while ( a[1] && a[2] ) { -- a[1]; -- a[2]; ++ sum; }
        if ( a[1] ) sum += (a[1] / 3) * 2;
        else sum += a[2];
        printf("%d\n", sum);
    }
    return 0;
}
