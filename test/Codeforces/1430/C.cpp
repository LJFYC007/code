/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年10月11日 星期日 17时14分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

priority_queue<int> Q;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T, n; scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n);
        printf("%d\n", 2);
        while ( !Q.empty() ) Q.pop();
        REP(i, 1, n) Q.push(i);
        REP(i, 1, n - 1)
        {
            int a = Q.top(); Q.pop();
            int b = Q.top(); Q.pop();
            if ( a % 2 != b % 2 && !Q.empty() )
            {
                int c = Q.top(); Q.pop(); Q.push(b); b = c;
            }
            printf("%d %d\n", a, b);
            Q.push((a + b + 1) / 2);
        }
    }
    return 0;
}
