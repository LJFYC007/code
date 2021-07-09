/***************************************************************
	File name: HaHa
	Author: ljfcnyali
	Create time: 2019年11月10日 20时12分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int n, k, ans;

int main()
{
    scanf("%d%d", &n, &k);    
    ans = n * 3 + min(k - 1, n - k);
    printf("%d\n", ans);
    return 0;
}
