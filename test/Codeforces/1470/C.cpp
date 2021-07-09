/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年01月06日 星期三 09时25分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, num;
set<int> Set;

inline int pre(int x) { return x == 1 ? n : x - 1; }
inline int suf(int x) { return x % n + 1; }
inline int ask(int t) 
{ 
    ++ num; printf("? %d\n", t); fflush(stdout); scanf("%d", &t); 
    // if ( num == 1000 ) { printf("! 55467"); exit(0); }
    return t; 
}
inline int Get()
{
    int pos = rand() % n + 1;
    auto it = Set.lower_bound(pos);
    if ( it != Set.end() ) return *it;
    return *Set.begin();
}

int main()
{
    scanf("%d%d", &n, &k); srand(time(0));
    REP(i, 1, n) Set.insert(i);
    int pos = 1, x = ask(pos);
    while ( x == k ) 
    { 
        REP(i, 1, num - 1) pos = suf(pos);
        x = ask(pos); 
    }
    while ( x < k ) { pos = suf(pos); x = ask(pos); }
    while ( x > k ) { pos = pre(pos); x = ask(pos); }
    printf("! %d\n", pos);
    return 0;
}
