/***************************************************************
	File name: string.cpp
	Author: ljfcnyali
	Create time: 2019年09月08日 星期日 10时19分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 50;
const int Mod1 = 103;
const int Mod2 = 107;

char s[maxn], a[maxn], b[maxn];
int n, ans;
map<int, int> Map1, Map2;

inline void DFS1(int x, int len1, int len2)
{
    if ( x == n * 2 + 1 )
    {
        int sum1 = 0, sum2 = 0;
        REP(i, 1, len1) sum1 = sum1 * Mod1 + a[i], sum2 = sum2 * Mod2 + a[i];
        sum1 = sum1 * Mod1; sum2 = sum2 * Mod2;
        REP(i, 1, len2) sum1 = sum1 * Mod1 + b[i], sum2 = sum2 * Mod2 + b[i];
        ++ Map1[sum1]; ++ Map2[sum2]; return ;
    }
    a[len1 + 1] = s[x]; DFS1(x + 1, len1 + 1, len2);
    b[len2 + 1] = s[x]; DFS1(x + 1, len1, len2 + 1);
}

inline void DFS2(int x, int len1, int len2)
{
    if ( x == n + 1 )
    {
        int sum1 = 0, sum2 = 0;
        for ( int i = len1; i >= 1; -- i ) sum1 = sum1 * Mod1 + a[i], sum2 = sum2 * Mod2 + a[i];
        sum1 = sum1 * Mod1; sum2 = sum2 * Mod2;
        for ( int i = len2; i >= 1; -- i ) sum1 = sum1 * Mod1 + b[i], sum2 = sum2 * Mod2 + b[i];
        ans += min(Map1[sum1], Map2[sum2]); return ;
    }
    a[len1 + 1] = s[x]; DFS2(x + 1, len1 + 1, len2);
    b[len2 + 1] = s[x]; DFS2(x + 1, len1, len2 + 1);
}

signed main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%lld", &n);
    scanf("%s", s + 1);
    DFS1(n + 1, 0, 0);
    DFS2(1, 0, 0);
    printf("%lld\n", ans / 2);
    return 0;
}
