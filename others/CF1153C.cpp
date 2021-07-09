/***************************************************************
	File name: CF1153C.cpp
	Author: ljfcnyali
	Create time: 2019年09月03日 星期二 20时44分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 300010;

char s[maxn];
int sum, n, Max;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    if ( n % 2 != 0 ) { puts(":("); return 0; }
    scanf("%s", s + 1);
    REP(i, 1, n) if ( s[i] == '(' ) Max = max(Max, i), ++ sum;
    if ( sum > n / 2 ) { puts(":("); return 0; }
    REP(i, 1, n)
    {
        if ( s[i] != '?' ) continue ;
        if ( sum < n / 2 ) { ++ sum; s[i] = '('; }
        else s[i] = ')';
    }
    sum = 0;
    REP(i, 1, n)
    {
        if ( s[i] == '(' ) ++ sum;
        else -- sum;
        if ( sum < 0 || (i != n && sum == 0) ) { puts(":("); return 0; }
    }
    REP(i, 1, n) putchar(s[i]); puts("");
    return 0;
}
