#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#include<string>
#include<iostream>
const int N=30;
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
 
#define io
#define Auto
 
#ifdef io
#ifdef Auto
namespace A
{
	std::string St[N];
	int p[N],t[N][N],m,pos,n,s,vis[N][N];
}
std::string go(int st,std::string dir,int pa)
{
	using namespace A;
	static int cnt=0;
	if((++cnt)>20000){ printf("Wrong Answer: step greater than 20000.\n"); exit(0); }
	int P=(p[pos]+pa)%m; p[pos]=(p[pos]+st)%m;
	if(!vis[pos][P]){ vis[pos][P]=1; s++; if(s==n*m){ printf("Accept: step equal to %d.\n",cnt); exit(0); } }
	St[pos]=dir; pos=t[pos][P];
    // printf("Q %d %6s %d => %6s\n",st,dir.c_str(),pa,St[pos].c_str());
    // printf("%d ", pos);
	return St[pos];
}
#else
std::string go(int st,std::string dir,int pa){ std::cout<<st<<' '<<dir<<' '<<pa<<std::endl; fflush(stdout); std::string s; std::cin>>s; if(s=="treasure") exit(0); return s; }
#endif
#else
#include"treasure.h"
#endif
 
const std::string L="left",R="right",C="center",Fuck="treasure";

using namespace std;

const int maxn = 50;

int n, p[maxn], len[maxn], mn[maxn], d[maxn];
string st;

void solve(int m)
{
    n = 1; p[n] = mn[n] = 0; d[n] = -1;
    while ( st != Fuck ) 
    {
        if ( p[n] == m )  
        {
            st = go(d[n], L, d[n]);
            REP(i, 1, len[n] - 2) st = go(0, st, 0);  
            -- n;
        }
        st = go(1, R, 1); d[n] = (d[n] - 1 + m) % m;
        if ( st == C ) { p[n] = mn[n] = 0; ++ n; p[n] = mn[n] = 0; continue ; }
        if ( st == L ) 
        {
            int num = 0, val = 0;
            while ( st == L ) { ++ num; st = go(0, L, 0); }
            while ( st == R ) { ++ num; st = go(0, R, 0); ++ val; }
            REP(i, 1, num - 1) st = go(0, st, 0); ++ p[n]; 
            if ( val > mn[n] && val <= n ) { mn[n] = val; len[n] = num; d[n] = 0; }
        }
        else
        {
            int num = 1, val = 1; st = go(0, L, 0);
            while ( st == R ) { ++ num; st = go(0, R, 0); ++ val; }
            st = go(0, R, 0);
            REP(i, 1, num - 2) st = go(0, st, 0); ++ p[n]; 
            if ( val > mn[n] && val <= n ) { mn[n] = val; len[n] = num; d[n] = 0; }
        }
    }
}
 
#include<random>
 
#ifdef io
int main()
{
    // freopen("input.txt", "r", stdin);
#ifdef Auto
	using namespace A;
	int &n=A::n,&m=A::m;
	std::cin>>n>>m;
	fr(i,1,n) St[i]=C;
	int op=2;
	switch(op)
	{
		case 1:	
		fr(i,1,n) fr(j,0,m-1) std::cin>>t[i][j];
		break;
		
		case 2:
		freopen("/dev/urandom","r",stdin);
    	unsigned int s=0; fr(i,1,100) s=s*s+getchar()+s;
        // s=3162855425;
		printf("sed: %u\n",s);
		std::mt19937 Rand(s);
		static int p[N];
		fr(i,1,n) p[i]=i;
		fr(i,1,n) std::swap(p[i],p[Rand()%i+1]);
        // fr(i, 1, n) printf("%d ", p[i]); puts("");
        fr(i,1,n) t[p[i]][m-1]=p[i==n?1:i+1];
		fr(i,1,n) fr(j,0,m-2) 
        {
            t[i][j]=Rand()%n+1;
            // while ( t[i][j] == i ) t[i][j] = Rand() % n + 1;
        }
		break;
	}
    printf("E:\n");
    fr(i,1,n) fr(j,0,m-1) printf("%d %d\n",i,t[i][j]);
	pos=1; solve(m);
	printf("Wrong Answer: visited edge : %d/%d.\n",s,A::n*A::m);
#else
	int n; std::string s; std::cin>>n>>s; solve(n); return 0;
#endif
}
#endif

