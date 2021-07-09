/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年01月24日 星期日 20时23分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

map<int, bool> Map[maxn];

int main()
{
    freopen("input.txt", "w", stdout);
    srand(time(0));
    int n = 10, m = rand() % 4 + n;
    printf("%d %d 2 6\n" ,n, m);
    REP(i, 1, n) Map[i][i] = true;
    REP(i, 1, n) printf("%d ", rand() % 3 >= 2 ? rand() % 2 + 1 : 0); puts("");
    REP(i, 2, n)
    {
        int u = i, v = rand() % (i - 1) + 1;
        Map[u][v] = Map[v][u] = true;
        printf("%d %d\n", u, v);
    }
    REP(i, n, m) 
    {
        int u = rand() % n + 1, v = rand() % n + 1;
        while ( Map[u][v] ) { u = rand() % n + 1; v = rand() % n + 1; }
        Map[u][v] = Map[v][u] = true;
        printf("%d %d\n", u, v);
    }
    return 0;
}
