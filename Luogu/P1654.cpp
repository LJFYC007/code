/***************************************************************
	File name: P1654.cpp
	Author: ljfcnyali
	Create time: 2019年09月19日 星期四 20时25分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

double ans, x, x1, x2;
int n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n)
    {
        scanf("%lf", &x);
        ans += (3 * x2 + 3 * x1 + 1) * x;
        x2 = (x2 + 2 * x1 + 1) * x;
        x1 = (x1 + 1) * x;
    }
    printf("%.1lf\n", ans);
    return 0;
}
