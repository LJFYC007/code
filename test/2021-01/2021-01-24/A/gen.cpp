/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年01月24日 星期日 10时18分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[maxn], b[maxn];
map<int, bool> Map;

int main()
{
    freopen("input.txt", "w", stdout);
    int n = rand() % 20 + 10; printf("%d\n", n);
    srand(time(0));
    REP(i, 1, n) a[i] = rand() % 1000 - 500; 
    REP(i, 1, 5) if ( a[i] % 2 == 0 ) ++ a[i];
    REP(i, 6, 10) if ( a[i] % 2 == 1 ) -- a[i];
    REP(i, 1, n)
    {
        int x = rand() % n + 1, y = rand() % n + 1;
        while ( Map[a[x] + a[y]] || (a[x] + a[y]) % 2 == 0 ) { x = rand() % n + 1; y = rand() % n + 1; }
        printf("%d ", a[x] + a[y]); Map[a[x] + a[y]] = true;
    }
    puts("");
    REP(i, 1, n) cout << a[i] << " "; cout << endl;
    return 0;
}
