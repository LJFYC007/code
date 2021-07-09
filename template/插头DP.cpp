/***************************************************************
	File name: P2289.cpp
	Author: ljfcnyali
	Create time: 2019年09月20日 星期五 16时33分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int __int128
#define LL __int128

namespace IO
{
    inline int read()
    {
        int x = 0; char c = getchar();
        while ( c < '0' || c > '9' ) c = getchar();
        while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
        return x;
    }

    inline void put(__int128  x)
    {
        if ( x == 0 ) { printf("1\n"); return ; }
        stack<int> Stack;
        while ( x ) { Stack.push(x % 10); x /= 10; } 
        while ( !Stack.empty() ) { printf("%c", Stack.top() + '0'); Stack.pop(); }
    }
}

const int maxn = 25;

map<LL, LL> f;
int n, m, p[maxn];

inline __int128 DFS(int x, int y, LL s)
{
    LL t = s * n * m + x * m + y; __int128 ans = 0;
    if ( f.count(t) ) return f[t];
    if ( x == n && y == m ) 
    {
        if ( s - 7 * p[y - 1] == 0 ) ans = 2;
        return f[t] = ans;
    }
    int left = s / p[y - 1] % 3, up = s / p[y] % 3;
    if ( !left && !up ) 
    {
        LL S = s + p[y - 1] + p[y] * 2;
        if ( y != m ) ans = DFS(x, y + 1, S);
    }
    else if ( left && !up ) 
    {
        LL S = s - p[y - 1] * left;
        if ( y != m ) ans = DFS(x, y + 1, S + p[y - 1] * left) + DFS(x, y + 1, S + p[y] * left);
        else ans = DFS(x + 1, 1, (S + p[y - 1] * left) * 3);
    }
    else if ( !left && up ) 
    {
        LL S = s - p[y] * up;
        if ( y != m ) ans = DFS(x, y + 1, S + p[y] * up) + DFS(x, y + 1, S + p[y - 1] * up);
        else ans = DFS(x + 1, 1, (S + p[y - 1] * up) * 3);
    }
    else if ( left == up && left == 1 ) 
    {
        int tot = 1; LL S = s - p[y - 1] - p[y];
        REP(i, y + 1, m - 1)
            if ( S / p[i] % 3 == 1 ) ++ tot;
            else if ( S / p[i] % 3 == 2 )
            {
                -- tot;
                if ( !tot ) { S -= p[i]; break ; }
            }
        if ( y != m ) ans = DFS(x, y + 1, S);
    }
    else if ( left == up && left == 2 ) 
    {
        int tot = 1; LL S = s - 2 * p[y - 1] - 2 * p[y];
        for ( int i = y - 2; i >= 0; -- i ) 
            if ( S / p[i] % 3 == 2 ) ++ tot;
            else if ( S / p[i] % 3 == 1 )
            {
                -- tot; 
                if ( !tot ) { S += p[i]; break ; }
            }
        if ( y != m ) ans = DFS(x, y + 1, S);
        else ans = DFS(x + 1, 1, S * 3);
    }
    else if ( left == 2 && up == 1 ) 
    {
        LL S = s - left * p[y - 1] - up * p[y];
        if ( y != m ) ans = DFS(x, y + 1, S);
    }
    return f[t] = ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = IO :: read(); m = IO :: read();
    if ( n < m ) swap(n, m);
    p[0] = 1; REP(i, 1, 21) p[i] = p[i - 1] * 3;
    IO :: put(DFS(1, 1, 0));
    return 0;
}
