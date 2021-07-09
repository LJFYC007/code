/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年10月27日 星期日 19时54分27秒
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
    int a, b; scanf("%d%d", &a, &b);
    if ( a > 9 || b > 9 ) puts("-1");
    else printf("%d\n", a * b);
    return 0;
}
