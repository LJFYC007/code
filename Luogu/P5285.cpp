/***************************************************************
	File name: P5285.cpp
	Author: ljfcnyali
	Create time: 2019年10月23日 星期三 20时47分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100;

char s[maxn];


namespace Subtask1
{
#define int long long
    int Mod = 998244353;

    inline int read()
    {
        char c = getchar(); int x = 0;
        while ( c < '0' || c > '9' ) c = getchar();
        while ( c >= '0' && c <= '9' ) { x = (x * 10 + c - '0') % (Mod - 1); c = getchar(); }
        return x;
    }

    inline int power(__int128 a, __int128 b)
    {
        __int128 r = 1;
        while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
        return r;
    }

    inline int main()
    {
        int n; scanf("%lld", &n);
        if ( s[2] == '?' ) Mod = 1145141;
        if ( s[3] == '+' ) Mod = 5211600617818708273;
        REP(i, 1, n) printf("%lld\n", power(19, read()));
        return 0;
    }
#undef int
}

namespace Subtask2 
{
    const int A = 55244;
    const int B = 45699;
    const int Mod = 998244353;

    inline __int128 read()
    {
        char c = getchar(); __int128 x = 0;
        while ( c < '0' || c > '9' ) c = getchar();
        while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
        return x;
    }

    int a[200000];

    inline int main()
    {
        a[0] = 1; REP(i, 1, A + B + 10) a[i] = a[i - 1] * 19 % Mod;
        int n; scanf("%d", &n); 
        REP(i, 1, n) { __int128 x = read(); printf("%d\n", a[x <= A ? x : (x - A) % B + A]); }
        return 0;
    }
}

inline void Subtask3
{
    inline int main()
    {
        int n; scanf("%d", &n);
        REP(i, 1, n)
        {
            int l, r; scanf("%d%d", &l, &r);
            if ( l == 2 && r == 10 ) puts("pp.p.p...");
            if ( l == 5 && r == 10 ) puts("p.p...");
            if ( l == 2 && r == 15 ) puts("pp.p.p...p.p..");
            if ( r == 1000000 ) 
        }
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("../../additional_file_3050/software8.in", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1);    
    if ( s[1] == '1' && s[2] != 'w' ) return Subtask1 :: main();
    if ( s[1] == '1' && s[2] == 'w' ) return Subtask2 :: main();
    if ( s[1] == '2' && s[2] == 'p' ) return Subtask3 :: main();
    return 0;
}
