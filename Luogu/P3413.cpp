/***************************************************************
	File name: P3413.cpp
	Author: ljfcnyali
	Create time: 2019年10月21日 星期一 21时29分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 1010;
const int Mod = 1e9 + 7;

int f[maxn][12][12][2], tmp[maxn], n;
char s[maxn];

inline int DFS(int x, int last1, int last2, int opt, int flag)
{
    if ( x == n + 1 ) return flag;
    if ( !opt && f[x][last1][last2][flag] ) return f[x][last1][last2][flag];
    int Max = opt ? tmp[x] : 9, ret = 0;
    REP(i, 0, Max)
    {
        if ( i == 0 && last2 == 11 ) 
            ret = (ret + DFS(x + 1, last2, 11, opt & (i == Max), flag)) % Mod;
        else if ( i == last2 || i == last1 ) 
            ret = (ret + DFS(x + 1, last2, i, opt & (i == Max), flag | 1)) % Mod;
        else ret = (ret + DFS(x + 1, last2, i, opt & (i == Max), flag)) % Mod;
    }
    if ( !opt ) f[x][last1][last2][flag] = ret;
    return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) tmp[i] = s[i] - '0';
    int now = n, st = 1;
    while ( tmp[now] == 0 ) { tmp[now] = 9; -- now; }
    if ( now == 1 && tmp[now] == 1 ) st = 2;
    -- tmp[now];
    int ans = -DFS(st, 11, 11, 1, 0);

    mem(f);
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) tmp[i] = s[i] - '0';
    ans += DFS(1, 11, 11, 1, 0);

    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
