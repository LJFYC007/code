/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年10月20日 星期日 17时20分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 300010;

int n, sum, ans, pos, num;
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); scanf("%s", s + 1);
    REP(i, 1, n) sum += s[i] == '(' ? 1 : -1;
    if ( sum != 0 ) { printf("0\n1 1\n"); return 0; }
    REP(i, 1, n) 
    {
        sum += s[i] == '(' ? 1 : -1;
        if ( sum == 0 ) { if ( !pos ) pos = i; ++ num; }
    }
    ans = num;
    pos = pos == n ? 1 : pos + 1;
    cerr << pos << " " << num << endl;
    for ( int i = 1; i <= n; ++ i )
    {
        int x = pos + 1, val = 0; sum = 1;
        while ( sum != 0 )
        {
            sum += s[x] == '(' ? 1 : -1; 
            if ( sum == 1 ) ++ val;
            ++ i;
            x = x == n ? 1 : x + 1;
        }
        ans = max(ans, num + val);
    }
    printf("%d\n", ans);
    return 0;
}
