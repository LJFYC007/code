/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年08月04日 星期日 19时58分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

char s[maxn];
int a[maxn], R[maxn], L[maxn], n, ans[maxn];

int main()
{
    scanf("%s", s); n = str(s);
    REP(i, 0, n - 1) if ( s[i] == 'L' ) a[i + 1] = 1; else a[i + 1] = 2;
    REP(i, 2, n) if ( a[i - 1] == 2 && a[i] == 1 ) L[i] = i; else L[i] = L[i - 1];
    for ( int i = n - 1; i >= 1; -- i ) if ( a[i + 1] == 1 && a[i] == 2 ) R[i] = i; else R[i] = R[i + 1];
    REP(i, 1, n)
    {
        int x;
        if ( a[i] == 1 ) { x = i - L[i]; if ( x & 1 ) ++ ans[L[i] - 1]; else ++ ans[L[i]]; }
        else { x = R[i] - i; if ( x & 1 ) ++ ans[R[i] + 1]; else ++ ans[R[i]]; }
    }
    REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}
