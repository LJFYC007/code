/***************************************************************
	File name: allocation.cpp
	Author: ljfcnyali
	Create time: 2020年07月18日 星期六 11时53分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int op, n, q;

int main()
{
    freopen("allocation.in", "r", stdin);
    freopen("allocation.out", "w", stdout);
    scanf("%d", &op);
    scanf("%d%d", &n, &q);
    int x; scanf("%d", &x);
    while ( q -- ) 
    {
        int C; scanf("%d", &C);
        printf("%d\n", x);
    }
    return 0;
}
