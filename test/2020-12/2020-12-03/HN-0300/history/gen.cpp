/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年12月03日 星期四 10时27分40秒
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
    freopen("history.in", "w", stdout);
    srand(time(0));
    int n = rand() % 2000000 + 1; printf("%d\n", n); 
    REP(i, 1, n) printf("%d ", rand() % 10000000 + 1); puts("");
    return 0;
}
