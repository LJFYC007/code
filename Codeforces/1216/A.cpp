/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年09月21日 星期六 14时53分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

int n, ans;
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    scanf("%s", s + 1);
    int sum1 = 0, sum2 = 0;
    REP(i, 1, n)
    {
        if ( s[i] == 'a' ) ++ sum1;
        else ++ sum2;
        if ( i % 2 == 0 && sum1 != sum2 )
        {
            ++ ans; sum1 = sum2;
            if ( s[i] == 'a' ) s[i] = 'b';
            else s[i] = 'a';
        }
    }
    printf("%d\n", ans);
    printf("%s", s + 1);
    return 0;
}
