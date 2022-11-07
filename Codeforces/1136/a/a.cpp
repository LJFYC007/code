/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年11月10日 星期日 20时01分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int n, l[maxn], r[maxn], ans, x;

int main()
{
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &l[i], &r[i]);
    scanf("%d", &x);
    REP(i, 1, n) if ( l[i] <= x && x <= r[i] ) { printf("%d\n", n - i + 1); return 0; }
    return 0;
}
