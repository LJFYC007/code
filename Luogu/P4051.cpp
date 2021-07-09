/***************************************************************
	File name: P4051.cpp
	Author: ljfcnyali
	Create time: 2019年11月15日 星期五 08时21分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, tot, sa[maxn], x[maxn], y[maxn], c[maxn], len;
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1); m = 300;
    REP(i, 1, n) s[n + i] = s[i]; len = n; n += n;
    REP(i, 1, n) { x[i] = s[i]; ++ c[x[i]]; }
    REP(i, 1, m) c[i] += c[i - 1];
    for ( int i = n; i >= 1; -- i ) sa[c[x[i]] --] = i;
    for ( int k = 1; k < n; k <<= 1 )
    {
        mem(c); tot = 0;
        REP(i, n - k + 1, n) y[++ tot] = i;
        REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;
        REP(i, 1, n) ++ c[x[y[i]]];
        REP(i, 1, m) c[i] += c[i - 1];
        for ( int i = n; i >= 1; -- i ) sa[c[x[y[i]]] --] = y[i];
        swap(x, y); x[sa[1]] = tot = 1;
        REP(i, 1, n) x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? tot : ++ tot;
        if ( tot >= n ) break ; m = tot;
    }
    REP(i, 1, n) if ( sa[i] <= len ) printf("%c", s[sa[i] + len - 1]); puts("");
    return 0;
}
