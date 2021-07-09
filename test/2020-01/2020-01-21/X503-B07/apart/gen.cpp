/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年01月21日 星期二 09时43分21秒
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
    freopen("apart.in", "w", stdout);
    int T = 1;
    int n = 500, m = 500;  
    printf("%d\n", T); 
    printf("%d %d\n", n, m);
    REP(i, 2, m) printf("%d %d %d\n", i - 1, i, rand() % 10000 + 1);
    printf("%d %d %d\n", 1, n, rand() % 10000 + 1);
    return 0;
}
