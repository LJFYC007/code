/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年08月15日 星期六 11时04分44秒
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
    freopen("input.txt", "w", stdout);
    srand(time(0));
    int n = 500; printf("%d 400000\n", n);
    REP(i, 1, n - 1) printf("%d %d\n", (i - 1) / 2, i); 
    return 0;
}
