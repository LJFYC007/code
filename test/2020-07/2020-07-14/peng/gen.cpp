/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月14日 星期二 19时47分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
    freopen("peng.in", "w", stdout);
    int n = 3, m = 3; printf("%d %d\n", n, m);
    REP(i, 1, n)
    {
        int x = rand() % 10 + 1;
        while ( a[x] ) x = rand() % 10 + 1;
    }
    return 0;
}
