/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年09月04日 星期三 17时16分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

char s[maxn];
int n, sum, k;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    scanf("%s", s + 1);
    for ( int i = n; i >= 1; -- i ) 
    {
        if ( s[i] == '(' ) { s[0] = '('; s[i] = 0; break ; }
    }
    REP(i, 0, n)
    {
        if ( s[i] == '(' ) ++ sum;
        else if ( s[i] == ')' ) -- sum;
        if ( sum < 0 ) { puts("NO"); return 0; }
    }
    if ( sum > 0 ) { puts("NO"); return 0; }
    puts("YES");
    return 0;
}
