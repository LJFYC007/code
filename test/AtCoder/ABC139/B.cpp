/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年09月01日 星期日 19时57分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int n, m, ans;

int main()
{
    scanf("%d%d", &n, &m);
    int now = 1;
    while ( now < m ) 
    {
        now += n - 1;
        ++ ans;
    }
    printf("%d\n", ans);
    return 0;
}
