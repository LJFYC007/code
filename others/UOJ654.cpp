/***************************************************************
	File name: UOJ654.cpp
	Author: ljfcnyali
	Create time: 2021年06月28日 星期一 16时32分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int unsigned int 
typedef long long LL;

const int maxn = 2e6 + 10;

namespace GenHelper
{
    int z1,z2,z3,z4,b;
    int read()
    {
        b=((z1<<6)^z1)>>13;
        z1=((z1&4294967294U)<<18)^b;
        b=((z2<<2)^z2)>>27;
        z2=((z2&4294967288U)<<2)^b;
        b=((z3<<13)^z3)>>21;
        z3=((z3&4294967280U)<<7)^b;
        b=((z4<<3)^z4)>>12;
        z4=((z4&4294967168U)<<13)^b;
        return (z1^z2^z3^z4);
    }
}
using namespace GenHelper;

int n, seed, d[maxn], h[maxn], ans;

void srand(int x)
{
	z1=x;
	z2=(~x)^0x233333333U;
	z3=x^0x1234598766U;
	z4=(~x)+51;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	cin >> n >> seed; 
	srand(seed);
	h[1] = 1; REP(i, 1, n) for ( int j = i + i; j <= n; j += i ) h[j] += h[i];
	REP(i, 1, n) for ( int j = i; j <= n; j += i ) d[j] += h[i];
	REP(i, 2, n) d[i] += d[i - 1];
	REP(i, 2, n) h[i] += h[i - 1];
	REP(i, 0, n - 1)
	{
		int x = read(), ret = d[min(i, n - i - 1)] + h[max(i, n - i - 1)];
		if ( n == 1 ) ret = 1;
		ans += x * ret;
	}	
	cout << ans << endl;
    return 0;
}
