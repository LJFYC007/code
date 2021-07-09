/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2019年10月30日 星期三 10时49分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long 
typedef long long LL;

const int Mod = 998244353;

signed main()
{
    freopen("output.txt", "w", stdout);
    int ret = 1;
    REP(i, 1, 10000040)
    {
        ret = ret * i % Mod;
    }
    printf("%d\n", ret);
    return 0;
}
