/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年09月01日 星期日 19时57分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

int n, a[maxn], ans, sum;

int main()
{
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1)
    {
        if ( a[i] >= a[i + 1] ) ++ sum;
        else { ans = max(ans, sum); sum = 0; }
    }
    ans = max(ans, sum);
    printf("%d\n", ans);
    return 0;
}
