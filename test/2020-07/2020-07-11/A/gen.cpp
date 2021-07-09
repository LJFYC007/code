/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月11日 星期六 10时04分21秒
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
    freopen("A.in", "w", stdout);
    srand(time(0));
    int n = 70;
    printf("1");
    REP(i, 2, n) printf("%d", rand() % 2); puts("");
    return 0;
}
