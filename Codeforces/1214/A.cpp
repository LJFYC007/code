/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年09月04日 星期三 17时03分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int n, d, e, ans = 0x3f3f3f3f;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &d, &e);
    e *= 5;
    REP(i, 0, n / d)
    {
        int sum = n - d * i;
        sum = sum - sum / e * e;
        ans = min(ans, sum);
    }
    printf("%d\n", ans);
    return 0;
}
