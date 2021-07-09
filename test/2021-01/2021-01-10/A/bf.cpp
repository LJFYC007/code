/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 08时28分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e5 + 10;
const int INF = 0x3f3f3f3f;

int n, a[maxn], Stack[maxn], tot, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) 
    {
        int Max = 0;
        REP(j, i, n) 
        {
            Max = max(Max, a[j]);
            if ( a[i] + a[j] == Max ) ++ ans;
        }
    }
    printf("%d\n", ans);
    return 0;
}
