/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年09月04日 星期三 19时45分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int a[100010];

int main()
{
    srand(time(0));
    freopen("rotate.in", "w", stdout);
    int n = 100000;
    printf("%d\n", n);
    REP(i, 1, n) a[i] = i;
    random_shuffle(a + 1, a + n + 1);
    REP(i, 1, n) printf("%d ", a[i]); puts("");
    return 0;
}
