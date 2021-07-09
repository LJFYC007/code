/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年01月24日 星期日 10时16分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], b[maxn];

int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &b[i]);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) 
    {
        REP(x, 1, n) REP(y, 1, n) if ( a[x] + a[y] == b[i] ) printf("%lld %lld\n", x, y); 
        puts("");
    }
    return 0;
}
