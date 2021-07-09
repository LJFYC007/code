/***************************************************************
	File name: CF1238A.cpp
	Author: ljfcnyali
	Create time: 2019年10月10日 星期四 11时37分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

int T, a, b;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d", &T);
    while ( T -- ) 
    {
        scanf("%I64d%I64d", &a, &b);
        if ( a > b + 1 ) puts("YES");
        else puts("NO");
    }
    return 0;
}
