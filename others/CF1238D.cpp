/***************************************************************
	File name: CF1238D.cpp
	Author: ljfcnyali
	Create time: 2019年10月10日 星期四 19时45分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 300010;

int a[maxn], n, ans, sum;
char s[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d", &n);
    scanf("%s", s + 1);
    REP(i, 1, n)
    {
        if ( s[i] == s[i + 1] ) a[i] = 2;
        else if ( s[i] == s[i + 2] ) a[i] = 3;
        if ( a[i] ) ++ sum;
    }
    REP(i, 1, n)
    {
        if ( a[i] ) ans += sum;
        if ( a[i] ) -- sum;
    }
    printf("%I64d\n", ans);
    return 0;
}
