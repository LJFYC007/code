/***************************************************************
	File name: candy.cpp
	Author: ljfcnyali
	Create time: 2020年10月19日 星期一 19时40分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int __int128
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], b[maxn], k[maxn], T, K;

inline int Solve(int a, int b)
{
    if ( a == b ) return 0;
    if ( K % 2 == 0 ) 
    {
        if ( b % 2 == 1 ) 
        {
            if ( a % 2 == 1 ) return 0;   
            if ( a * K > b ) return 1;
            return 3 - Solve(a * K, b);
        }
        if ( a * K <= b / K ) return Solve(a, b / K / K);
        int pos = b / K;
        if ( a > pos ) return a & 1;
        return 2 - (a & 1);
    }
    int pos = b / K, num = 0;
    while ( a <= pos ) 
    {
        if ( a == pos ) return 2;
        ++ num;
        pos = (pos - 1) / K;
    }
    return (b - a + num) % 2;
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("candy.in", "r", stdin);
    freopen("candy.out", "w", stdout);
    read(T);
    while ( T -- )
    {
        read(n);
        REP(i, 1, n) { read(a[i]); read(b[i]); read(k[i]); }
        int ans = 0;
        REP(i, 1, n) { K = k[i]; ans ^= Solve(a[i], b[i]); }
        if ( ans ) puts("Alice");
        else puts("Bob");
    }
    return 0;
}
