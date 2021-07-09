/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年01月13日 星期一 11时09分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int main()
{
    freopen("cows.in", "w", stdout);
    srand(time(0));
    int n = 50; printf("%d\n", n);
    REP(i, 1, n) { REP(j, 1, n) printf("%d", i == j ? 0 : 1); puts(""); }
    return 0;
}
