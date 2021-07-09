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
	T xi=0;
	char ch=gc;
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
const int N=1e6+7,mod=1e9+7;
const double inf=1e18;
ll fac[N],sigma[N],l,r;
int pr[N],cnt;
bitset<N>npr;
inline void sieve(int n)
{
	for(int i=2;i<=n;++i)
	{
		if(!npr._Unchecked_test(i))pr[++cnt]=i;
		for(int j=1;j<=cnt&&i*pr[j]<=n;++j)
		{
			npr._Unchecked_set(i*pr[j]);
			if(i%pr[j]==0)break;
		}
	}
}
ll mul(ll a,ll b,ll P){
//	if(a<inf/b)return a*b%P;
	return (a*b-(ll)((long double)a/P*b)*P+P)%P;
}
ll qpow(ll a,ll b,ll P)
{
	ll c=1;
	for(;b;b>>=1,a=mul(a,a,P))if(b&1)c=mul(c,a,P);
	return c;
}
bool Test(ll a,ll x)
{
	if(a>=x)return 1;
	ll ret,s=x^1;
	int p=__builtin_ctzll(s);
	ret=qpow(a,s>>=p,x);
	if(ret==1||ret==(x^1))return 1;
	while(p--&&ret!=(x^1))ret=mul(ret,ret,x);
	return p>=0;
}
int lst[]={2,3,5,7,11,13,17,19,23};
bool Miller_Rabin(ll x)
{
/*	
	if(x==1)return 0;
	if(x==2)return 1;
	if(x&1)
	{
		for(int i=0;i<9;++i)if(!Test(lst[i],x))return 0;
		return 1;
	}
	return 0;
*/
	if(x==46856248255981ll||x<2)return false;
	if(x==2||x==3||x==7||x==61||x==24251)return true;
	return Test(2,x)/*&&Test(3,x)&&Test(7,x)*/&&Test(61,x);//&&Test(24251,x);
}
inline ll sqr(ll x){return x*x;}
/*
inline ll _rand(ll x,ll c,ll P){
	return (mul(x,x,P)+c);
}
*/
#define _rand(x,c,P) (mul(x,x,P)+c)
inline ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
/*
inline ll gcd(ll a,ll b){
    if(!a)return b;
    if(!b)return a;
    int t=__builtin_ctzll(a|b);
    a>>=__builtin_ctzll(a);
    do{
        b>>=__builtin_ctzll(b);
        if(a>b){ll t=b;b=a,a=t;}
        b-=a;
    }while(b);
    return a<<t;
}
*/
inline ll Fact(ll x)
{
	ll s=0,t=0,c=rand()%(x-1)+1,val=1;
	for(int len=1;;len<<=1,s=t,val=1)
	{
		for(int tot=1;tot<=len;++tot)
		{
			t=_rand(t,c,x),val=mul(val,abs(t-s),x);
			if((tot%255)==0)
			{
				ll d=gcd(val,x);
				if(d^1)return d;
			}
		}
		ll d=gcd(val,x);
		if(d^1)return d;
	}
}
ll mxfac;
inline void Fac(ll x)
{
	if(x<=mxfac||x<2)return;
	if(Miller_Rabin(x))return chkmax(mxfac,x),void();
	ll p=x;
	while(p>=x)p=Fact(x);
	while(x%p==0)x/=p;
	Fac(x),Fac(p);
}
inline ll Pollard_Rho(ll x)
{
	if(Miller_Rabin(x))return x;
	mxfac=1,Fac(x);
	return mxfac;
}
float InvSqrt(float x)
{
	float xhalf=0.5f*x;
	int i=*(int*)&x;
	i=0x5f375a86-(i>>1);
	x=*(float*)&i;
	x=x*(1.5f-xhalf*x*x);
	return x;
}
inline bool chksqrt(ll x)
{
	ll y=1/InvSqrt(x);
	return y*y==x;
//	return sqr(sqrt(x))==x;
}
inline ll Add(ll x){return x>mod?x-mod:x;}
int main(void)
{
	srand(time(0));
	l=gl,r=gl;
	for(ll i=l;i<=r;++i)fac[i-l]=i,sigma[i-l]=1;
	sieve(1000000);
	for(int i=1;i<=cnt&&pr[i]<=r;++i)
	{
		int p=pr[i];
		for(int j=((l-1)/p+1)*p-l;j<=r-l;j+=p)
		{
			int k=0;
			ll ans=1;
			while(fac[j]%p==0)++k,fac[j]/=p,ans=mul(ans,p,mod)+1;
			sigma[j]=mul(sigma[j],ans,mod);
		}
	}
	ll ans=0;
	for(int i=0;i<=r-l;++i)
	{
		if(fac[i]!=1)
		{
			ll t=fac[i];
			if(chksqrt(t))sigma[i]=mul(sigma[i],(t%mod+(ll)sqrt(t)+1)%mod,mod);
			else if(Miller_Rabin(t))sigma[i]=mul(sigma[i],(t+1)%mod,mod);
			else{
				ll ret=Pollard_Rho(t);
				sigma[i]=mul(sigma[i],(ret+1)*(t/ret+1)%mod,mod);
			}
		}
		ans=Add(ans+sigma[i]);
	}
	pi(ans);
	return 0;
}
