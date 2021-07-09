/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 22时13分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 200010;

int T, n, sum1[30], sum2[30], c[30];
char s[maxn], t[maxn];

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i <= 26; i += lowbit(i) ) c[i] += val; }

inline int get(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n);
        scanf("%s", s + 1);
        scanf("%s", t + 1);
        REP(i, 0, 26) sum1[i] = sum2[i] = c[i] = 0;
        REP(i, 1, n) ++ sum1[s[i] - 'a'], ++ sum2[t[i] - 'a'];
        bool flag = 0;
        REP(i, 0, 25) if ( sum1[i] != sum2[i] ) { puts("NO"); flag = 1; break ; }
        if ( flag ) continue ;
        REP(i, 0, 25) if ( sum1[i] > 1 || sum2[i] > 1 ) { puts("YES"); flag = 1; break ;  }
        if ( flag ) continue ;
        int ret1 = 0, ret2 = 0;
        REP(i, 1, n)
        {
            ret1 += i - get(s[i] - 'a' + 1) - 1;
            add(s[i] - 'a' + 1, 1);
        }
        REP(i, 1, 26) c[i] = 0;
        REP(i, 1, n)
        {
            ret2 += i - get(t[i] - 'a' + 1) - 1;
            add(t[i] - 'a' + 1, 1);
        }
        if ( ret1 % 2 == ret2 % 2 ) puts("YES");
        else puts("NO");
    }
    return 0;
}
