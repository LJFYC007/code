/***************************************************************
	File name: memoryofwinter.cpp
	Author: ljfcnyali
	Create time: 2020年10月25日 星期日 08时26分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int l, r, k, ans[40];
vector<int> p[40];

inline bool Check(int x)
{
    static int Stack[10]; int len = 0;
    while ( x ) { Stack[++ len] = x % 10; x /= 10; }
    int ret = 0;
    REP(i, 1, len) REP(j, i + 1, len) if ( Stack[i] < Stack[j] ) ++ ret;
    ++ ans[ret];
}

int main()
{
    freopen("memoryofwinter.in", "r", stdin);
    freopen("memoryofwinter.out", "w", stdout);
    REP(i, 1, 1000000000)
    {
        Check(i);
        if ( i % 10000000 == 0 ) REP(j, 0, 36) p[j].push_back(ans[j] % Mod);
    }
    REP(i, 0, 36)
    {
        cout << "{0";
        for ( auto it : p[i] ) cout << "," << it;
        cout << "},";
    }
    return 0;
}
