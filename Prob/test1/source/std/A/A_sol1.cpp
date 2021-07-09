/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2019年06月15日 星期六 10时50分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

char s[maxn];
int len, Next[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%s", s); len = str(s);
    int n = str(s);
    REP(i, 0, len - 1) s[2 * len - i] = s[i];
    s[len] = '#'; len = len * 2 + 1;
    int j = 0;
    REP(i, 1, len - 1)
    {
        while ( j && s[i] != s[j] ) j = Next[j];
        Next[i + 1] = s[i] == s[j] ? ++ j : 0;
    }
    printf("%d\n", n - Next[len]);
    return 0;
}
