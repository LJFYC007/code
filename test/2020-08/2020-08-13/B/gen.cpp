/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年08月13日 星期四 09时21分58秒
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
    freopen("B.in", "w", stdout);
    srand(time(0));
    int n = 250000;
    REP(i, 1, n) printf("%c", rand() % 2 + '0');
    puts("");
    return 0;
}
