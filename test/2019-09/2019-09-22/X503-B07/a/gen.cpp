/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年09月22日 星期日 09时12分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
    freopen("a.in", "w", stdout);
    srand(time(0));
    int n = 2000000;
    printf("%d\n", n);
    REP(i, 1, n) printf("%d ", rand() % n + 1);
    puts("");
    return 0;
}
