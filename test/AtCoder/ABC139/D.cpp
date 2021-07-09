/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年09月01日 星期日 19时57分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
    int n; scanf("%d", &n);
    LL ans = n; ans = ans * (n - 1) / 2;
    printf("%lld\n", ans);
    return 0;
}
