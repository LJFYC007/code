/***************************************************************
	File name: sage.cpp
	Author: ljfcnyali
	Create time: 2020年10月07日 星期三 09时33分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

namespace IO{ int c;
	unsigned int seed;
	unsigned int randnum(){
		seed^=seed<<13;
		seed^=seed>>17;
		seed^=seed<<5;
		return seed;
	}
	inline int read(int &x){scanf("%d",&x);return x;}
	inline void init_case(int &m,int &a,int &b,int &d,int p[]){
		scanf("%d%u%d%d%d%d",&m,&seed,&a,&b,&c,&d);
		for(int i=1;i<=m;i++){
			if(randnum()%c==0)p[i]=-1;
			else p[i]=randnum()%b;
		}
	}

	inline void update_ans(unsigned int &ans_sum,unsigned int cur_ans,int no){
		const static unsigned int mod=998244353;
		ans_sum^=(long long)no*(no+7)%mod*cur_ans%mod;
	}
}
using IO::read;
using IO::init_case;
using IO::update_ans;

int n, m, a, b, d, p[maxn], vis[maxn], Min, Stack[maxn], l, r, RealMin;
bool flag;

inline void ReBuild()
{
    Min = 2 * m + 1;
    REP(i, l, r) Min = min(Min, Stack[i]);
    // REP(i, Min, 2 * m) if ( vis[i] != 1 ) { Min = i; return ; }
    // Min = 2 * m + 1;
}

inline void Delete()
{
    if ( d == 1 || l > r ) { flag = true; return ; }
    int t = Stack[l ++]; vis[t] = 1;
    if ( t == Min ) ReBuild();
}

int main()
{
    freopen("sage.in", "r", stdin);
    freopen("sage.out", "w", stdout);
	int T; read(T);
    while ( T -- )
    {
		unsigned int ans_sum = 0, cur_ans = 0;
		init_case(m, a, b, d, p);
        l = 1; r = 0;
        mem(vis); REP(i, 0, a) vis[i] = 1;
        Min = RealMin = a + 1;
        REP(i, 1, m)
        {
            flag = false; 
            if ( p[i] == -1 ) Delete();
            else if ( vis[p[i]] == 0 ) 
            {
                vis[p[i]] = 1;
                while ( vis[RealMin] != 0 ) ++ RealMin;
                if ( p[i] == Min ) ReBuild(); 
            }
            else if ( vis[p[i]] == 1 ) 
            { 
                if ( d == 1 ) continue ; vis[p[i]] = 2; 
                Stack[++ r] = p[i]; Min = min(Min, p[i]);
            }
            else Delete();
            if ( flag ) continue ;
			update_ans(ans_sum, min(Min, RealMin), i);
		}
		printf("%u\n", ans_sum);
	}
    return 0;
}
