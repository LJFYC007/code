#include<cstdio>
using namespace std;
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
		return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
	}
	template<class T> void gi(T& x){
		x=0; char c=gc();
		for(;c<'0'||c>'9';c=gc());
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
int a;
long long b;
int main()
{
	gi(a);//输入一个int型变量
	gi(b);//输入一个long long型变量
	pi(a);//输出一个int型变量并换行
	pi(b);//输出一个long long型变量并换行
	int n=2333;
	for(int i=1;i<=n;i++)pi(i);//输出n行
	for(int i=1;i<=n;i++)pi(i,' ');//输出一行n个数，不换行
	for(int i=1;i<=n;i++)pi(i,i==n?'\n':' ');//输出一行n个数，换行
}
