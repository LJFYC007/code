/***************************************************************
	File name: cloudy1.cpp
	Author: ljfcnyali
	Create time: 2019年10月14日 星期一 10时29分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

long double n, s, v1, v2, ans, x, y, t;

int main()
{
    freopen("cloudy.in", "r", stdin);
    freopen("cloudy.out", "w", stdout);
    cin >> s >> n >> v1 >> v2;    
    if ( v1 < v2 ) 
    {
        printf("%.5Lf\n", s / v1);
        return 0;
    }
    x = -s * v1 + 2 * n * s * v1 + s * v2; 
    y = v1 * (v1 - v2 + 2 * n * v2);
    printf("%.5Lf\n", x / y);
    return 0;
}
