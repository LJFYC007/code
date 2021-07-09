/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月22日 星期四 10时14分38秒
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
    freopen("a.in", "w", stdout);
    int r = rand() % 7 + 1, m = rand() % 7 + 1;
    printf("%d %d\n", r, m);
    return 0;
}
