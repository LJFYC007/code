/***************************************************************
	File name: geometry.cpp
	Author: ljfcnyali
	Create time: 2020年10月31日 星期六 10时31分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const double N = 1e9;
const double pi = 3.14159265358979;

int n;
long double sumx, sumy;

int main()
{
    freopen("geometry.in", "r", stdin);
    freopen("geometry.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n)
    {
        int x; scanf("%d", &x);
        long double posx = cos(x / N * pi);
        long double posy = sin(x / N * pi);
        sumx += posx ; sumy += posy;
    }
    printf("%.15Lf %.15Lf\n", sumx * 3 / 2 / n, sumy * 3 / 2 / n);
    return 0;
}
