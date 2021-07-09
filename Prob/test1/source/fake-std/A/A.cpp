/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年06月18日 星期二 09时25分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10000010;

char s[maxn];
int n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%s", s); n = str(s);
//    if ( n >= 1010) { printf("%d\n", n - 1); return 0; }
    for ( int len = n; len >= 1; -- len ) 
    {
        bool flag = true;
        REP(i, 0, (len - 1) / 2)
            if ( s[i] != s[len - 1 - i] ) { flag = false; break ; }
        if ( flag == true ) { printf("%d\n", n - len); return 0; }
    }
    return 0;
}
