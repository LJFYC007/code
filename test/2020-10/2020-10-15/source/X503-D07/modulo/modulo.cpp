/***************************************************************
	File name: modulo.cpp
	Author: ljfcnyali
	Create time: 2020年10月15日 星期四 09时54分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e7 + 10;
const int INF = 0x3f3f3f3f;

int n, k, a[maxn], ans, Stack[maxn], top;
char s[maxn];
bool vis[maxn];

int main()
{
    freopen("modulo.in", "r", stdin);
    freopen("modulo.out", "w", stdout);
    scanf("%d", &k); 
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) a[i] = (k - s[i] + '0') % k;
    if ( k <= 3 ) 
    {
        int num = 0;
        REP(i, 0, n - 1)
        {
            int val;
            if ( a[i] > a[i + 1] ) val = k + a[i + 1] - a[i];
            else 
            {
                ans += a[i + 1] - a[i];
                val = a[i] - a[i + 1];
            }
            if ( val == 1 ) ++ num;
            else if ( val == -2 && num > 0 ) { -- num; -- ans; }
        }
    }
    else 
    {
        int num1 = 0, num2 = 0;
        REP(i, 0, n - 1)
        {
            int val;
            if ( a[i] > a[i + 1] ) val = k + a[i + 1] - a[i];
            else 
            {
                ans += a[i + 1] - a[i];
                val = a[i] - a[i + 1];
            }
            if ( val == 1 ) Stack[++ num1] = i;
            else if ( val == -3 && num1 > 0 ) { vis[Stack[num1]] = vis[i] = true; -- num1; ans -= 2; }
        }
        num1 = 0; num2 = 0;
        REP(i, 0, n - 1)
        {
            if ( vis[i] ) continue ;
            int val;
            if ( a[i] > a[i + 1] ) val = k + a[i + 1] - a[i];
            else val = a[i] - a[i + 1];
            if ( val == 1 ) ++ num1;
            if ( val == 2 ) ++ num2;
            if ( val == -2 && num1 > 0 ) { -- num1; -- ans; }
            if ( val == -3 && num2 > 0 ) { -- num2; -- ans; }
        }
    }
    printf("%d\n", ans);
    return 0;
}
