/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年08月11日 星期二 09时30分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, q, a[maxn], f[maxn], g[maxn];
char s[maxn];

int main()
{
    freopen("B.in", "r", stdin);
    freopen("B1.out", "w", stdout);
    scanf("%s", s + 1); n = str(s + 1); 
    REP(i, 1, n) a[i] = s[i] - 'a' + 1;
    scanf("%d", &q); 
    REP(i, 1, q) 
    {
        int l, r; scanf("%d%d", &l, &r);
        mem(f); mem(g);
        f[l] = 2; g[l] = 1;
        REP(j, l + 1, r)
        {
            g[j] = f[j - 1];
            REP(k, l, j - 1) if ( a[j] == a[k] ) g[j] -= g[k];
            g[j] %= Mod; f[j] = (f[j - 1] + g[j]) % Mod;
        }
        printf("%d\n", (f[r] - 1 + Mod) % Mod);
    }
    return 0;
}
