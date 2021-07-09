/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年07月12日 星期日 16时38分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod1 = 998244353;
const int seed1 = 233;
// const int Mod2 = 1e9 + 7;

int n, a[maxn], b[maxn], sa[maxn], Hash1[2][maxn], p1[maxn], inv1[maxn], last[maxn];
char s[maxn];

inline int power(int a, int b, int Mod) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Check1(int op, int l, int r)
{
    int ret = (Hash1[op][r] - Hash1[op][l - 1]) % Mod1;
    ret = ret * inv1[l - 1] % Mod1;
    return (ret + Mod1) % Mod1;
}

inline bool cmp(int x, int y) 
{
    int l = 1, r = min(n - x + 1, n - y + 1), pos1 = 0, pos2 = 0;
    while ( l <= r ) 
    {
        int Mid = l + r >> 1;
        int fx = Check1(0, x, x + Mid - 1), fy = Check1(0, y, y + Mid - 1);
        if ( fx == fy ) { pos1 = Mid; l = Mid + 1; }
        else r = Mid - 1;
    }
    // printf("%lld %lld\n", Check1(0, 1, 3), Check1(0, 3, 5));
    // printf("%lld\n", pos1);
    l = 1; r = min(n - x + 1, n - y + 1);
    while ( l <= r ) 
    {
        int Mid = l + r >> 1;
        int fx = Check1(0, x, x + Mid - 1), fy = Check1(1, y, y + Mid - 1);
        if ( fx == fy ) { pos2 = Mid; l = Mid + 1; }
        else r = Mid - 1;
    }
    int pos = max(pos1, pos2);
    int X = last[x + pos], Y = last[y + pos];
    if ( X > pos ) X = 0;
    if ( Y > pos ) Y = 0;
    if ( X < Y ) return true;
    if ( X > Y ) return false;
    return x > y;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%lld", &n) )
    {
        scanf("%s", s + 1);
        p1[0] = inv1[0] = 1; REP(i, 1, n) { p1[i] = p1[i - 1] * seed1 % Mod1; inv1[i] = power(p1[i], Mod1 - 2, Mod1); }
        REP(i, 1, n) { a[i] = s[i] - 'a'; b[i] = a[i] ^ 1; }
        REP(i, 1, n) last[i] = 0;
        REP(i, 1, n)
            for ( int j = i - 1; j >= 1; -- j ) if ( a[i] == a[j] ) { last[i] = i - j; break ; }
        Hash1[0][0] = Hash1[1][0] = 0;
        REP(i, 1, n) 
        {
            Hash1[0][i] = (Hash1[0][i - 1] + a[i] * p1[i]) % Mod1;
            Hash1[1][i] = (Hash1[1][i - 1] + b[i] * p1[i]) % Mod1;
        }
        REP(i, 1, n) sa[i] = i;
        sort(sa + 1, sa + n + 1, cmp);
        REP(i, 1, n) printf("%lld ", sa[i]); puts("");
    }
    return 0;
}
