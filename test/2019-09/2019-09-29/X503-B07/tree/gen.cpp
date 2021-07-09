/*
@Date    : 2019-09-29 10:16:45
@Author  : Adscn (adscn@qq.com)
@Link    : https://www.cnblogs.com/LLCSBlog
*/
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
set<int>p;
int main(void)
{
	srand(time(0));
	freopen("tree.in","w",stdout);
	int n=300000,m=n;
	pi(n,' '),pi(m,'\n');
	for(int i=2;i<=n;++i)pi(i,' '),pi(rand()%(i-1)+1,'\n');
	int cnt=0;
	for(int i=1;i<=m;++i){
		int opt=rand()%3+1;
		if(p.empty())opt=rand()%2+1;
		pi(opt,' ');
		if(opt==1||opt==2)printf("%d %d\n",rand()%n+1,rand()%n+1);
		else 
		{
			printf("%d\n",*p.begin());
			p.erase(p.begin());
		}
		if(opt==1)++cnt,p.insert(cnt);
	}
	return 0;
}
