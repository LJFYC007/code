/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 14时55分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int Mod = 1e9 + 7;

int n, ans;

int main()
{
    freopen("yushu.in", "r", stdin);
    freopen("yushu.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) ans = (ans + n % i) % Mod;
    printf("%d\n", ans);
    return 0;
}
