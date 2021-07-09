/***************************************************************
	File name: P3375.cpp
	Author: ljfcnyali
	Create time: 2019年11月14日 星期四 09时03分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, Next[maxn];
char s[maxn], t[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    n = str(s + 1); m = str(t + 1);
    for ( int i = 2, j = 0; i <= m; ++ i )
    {
        while ( j && t[i] != t[j + 1] ) j = Next[j];
        if ( t[i] == t[j + 1] ) ++ j;
        Next[i] = j;
    }
    for ( int i = 1, j = 0; i <= n; ++ i ) 
    {
        while ( j && s[i] != t[j + 1] ) j = Next[j];
        if ( s[i] == t[j + 1] ) ++ j;
        if ( j == m ) printf("%d\n", i - m + 1);
    }
    REP(i, 1, m) printf("%d ", Next[i]); puts("");
    return 0;
}
