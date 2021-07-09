/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月06日 星期一 10时20分58秒
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
    int k = 100; printf("%d\n", k);
    REP(i, 1, 100) printf("%c", rand() % 4 + 'a'); puts("");
    return 0;
}
