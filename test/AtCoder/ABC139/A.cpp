/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年09月01日 星期日 19时57分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

char s[4][4];

int main()
{
    scanf("%s", s[1]);
    scanf("%s", s[2]);
    int ans = 0;
    REP(i, 0, 2) if ( s[1][i] == s[2][i] ) ++ ans;
    printf("%d\n", ans);
    return 0;
}
