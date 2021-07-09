/***************************************************************
	File name: dna.cpp
	Author: ljfcnyali
	Create time: 2020年10月07日 星期三 08时10分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e6 + 10;

int n, k, a[maxn], ans;
char s[maxn];

inline int find(char c)
{
    if ( c == 'A' ) return 0;
    if ( c == 'G' ) return 1;
    if ( c == 'C' ) return 2;
    return 3;
}

int main()
{
    freopen("dna.in", "r", stdin);
    freopen("dna.out", "w", stdout);
    scanf("%s", s + 1); n = str(s + 1);
    scanf("%d", &k);
    int x = 1 << (k + k - 2), val = 0;
    REP(i, 1, k) val += (1 << (i + i - 2)) * find(s[i]);
    ++ a[val];
    REP(i, k + 1, n)
    {
        val /= 4;
        val += x * find(s[i]);
        ++ a[val];
    }
    REP(i, 0, maxn - 10) ans = max(ans, a[i]);
    printf("%d\n", ans);
    return 0;
}
