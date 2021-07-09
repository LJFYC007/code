#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define IL inline
#define RG register
#define gi geti<int>()
#define gl geti<ll>()
#define gc getchar()
#define File(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
template<typename T>IL bool chkmax(T &x,const T &y){return x<y?x=y,1:0;}
template<typename T>IL bool chkmin(T &x,const T &y){return x>y?x=y,1:0;}
template<typename T>
IL T geti()
{
	RG T xi=0;
	RG char ch=gc;
	bool f=0;
	while(!isdigit(ch))ch=='-'?f=1:f,ch=gc;
	while(isdigit(ch))xi=xi*10+ch-48,ch=gc;
	return f?-xi:xi;
}
template<typename T>
IL void pi(T k,char ch=0)
{
	if(k<0)k=-k,putchar('-');
	if(k>=10)pi(k/10);
	putchar(k%10+'0');
	if(ch)putchar(ch);
}
const int N=50007;
int ch[N][2],tot,bo[N];
queue<int>Q;
int nxt[N];
int s[207],n,m;
int f[207][N];
inline void init()
{
	for(int i=0;i<=tot;++i)ch[i][0]=ch[i][1]=bo[i]=0;
	for(int i=0;i<=m;++i)memset(f[i],0,tot*4+4);
	tot=1;
}
void insert(int *s)
{
	int u=1;
	for(int i=0;i<n;++i)
	{
		int c=s[i];
		if(!ch[u][c])ch[u][c]=++tot;
		u=ch[u][c];
	}
	++bo[u];
}
void build()
{
	for(int i=0;i<2;i++)ch[0][i]=1;
	Q.push(1);nxt[1]=0;
	while(!Q.empty())
	{
		int u=Q.front();Q.pop();
		for(int i=0;i<2;++i)
			if(!ch[u][i])ch[u][i]=ch[nxt[u]][i];
			else Q.push(ch[u][i]),nxt[ch[u][i]]=ch[nxt[u]][i];
	}
}
const int P=998244353;
inline void add(int &a,int b){
	a+=b;
	if(a>=P)a-=P;
}
inline void sub(int &a,int b){
	a-=b;
	if(a<0)a+=P;
}
inline ll ksm(ll a,int b,ll c=1)
{
	for(;b;b>>=1,a=a*a%P)
		if(b&1)c=c*a%P;
	return c;
}
int main(void)
{
    File("string");
	int T=gi;
	while(T--)
	{
		init();
		n=gi,m=gi;
		for(int i=0;i<n;++i)s[i]=getchar()-'0';
		insert(s);
		for(int i=0;i<n;++i)
		{
			s[i]^=1;
			insert(s);
			s[i]^=1;
		}
		build();
		f[0][1]=1;
		for(int i=0;i<m;++i)
			for(int j=1;j<=tot;++j)
				if(f[i][j])
					for(int k=0;k<2;++k)
						if(!bo[ch[j][k]])
							add(f[i+1][ch[j][k]],f[i][j]);
		int ans=ksm(2,m);
		for(int i=1;i<=tot;++i)sub(ans,f[m][i]);
		pi(ans,'\n');
	}
	return 0;
}

