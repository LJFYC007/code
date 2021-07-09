/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年07月11日 星期六 10时39分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, ans;
__int128 val;
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);    
    REP(i, 1, n) val = val * 2 + s[i] - '0';
    while ( val > 1 ) 
    {
        if ( val & 1 ) val = val * 3 + 1;
        else val >>= 1;
        ++ ans;
    }
    printf("%d\n", ans);
    return 0;
}
