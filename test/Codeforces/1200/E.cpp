/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 22时18分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5000010;
const LL inv1 = 233;
const LL inv2 = 377;
const LL Mod1 = 1e9 + 7;
const LL Mod2 = 1e9 + 9;

int n;
LL Hash1[maxn], Hash2[maxn], Hash3[maxn], Hash4[maxn], p1[maxn], p2[maxn];
string a, b;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    p1[0] = 1; REP(i, 1, maxn - 10) p1[i] = (p1[i - 1] * inv1) % Mod1;
    p2[0] = 1; REP(i, 1, maxn - 10) p2[i] = (p2[i - 1] * inv2) % Mod2;
    cin >> a;
    REP(o, 2, n)
    {
        cin >> b;
        int len = min(a.size(), b.size()) - 1, L = -1;
        Hash1[len + 1] = 0;
        REP(i, 0, len)
        {
            Hash1[a.size() - i - 1] = (Hash1[a.size() - i] + a[a.size() - i - 1] * p1[i]) % Mod1;
            Hash2[i] = (Hash2[i - 1] * inv1 + b[i]) % Mod1;
            Hash3[a.size() - i - 1] = (Hash3[a.size() - i] + a[a.size() - i - 1] * p2[i]) % Mod2;
            Hash4[i] = (Hash4[i - 1] * inv2 + b[i]) % Mod2;
            if ( Hash1[a.size() - i - 1] == Hash2[i] && Hash3[a.size() - i - 1] == Hash4[i] ) L = i;
        }
        b.erase(0, L + 1);
        a += b;
    }
    cout << a << endl;
    return 0;
}
