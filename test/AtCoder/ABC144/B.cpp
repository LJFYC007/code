/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年10月27日 星期日 19时54分33秒
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
    int n; scanf("%d", &n);
    REP(i, 1, 9) REP(j, 1, 9) if ( i * j == n ) { printf("Yes\n"); return 0; }
    printf("No\n");
    return 0;
}
