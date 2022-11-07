#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
const int N=110,M=20000000;
int n,l[N],m,q[N];
char s[N][15];
char c[M];
int cnt[N],v,L,R;
int main()
{
	fr(T,1,read())
	{
		n=read(); m=0;
		fr(i,1,n){ scanf("%s",s[i]); l[i]=strlen(s[i]); q[i]=0; }
		int p=1;
		while(1)
		{
			c[++m]=s[p][q[p]]; q[p]++; if(q[p]==l[p]) q[p]=0; p++; if(p==n+1) p=1;
			if(p==1)
			{
				int flag=1;
				fr(i,1,n) if(q[p]) flag=0;
				if(flag) break;
			}
		}
//		c[m+m+1]=0; printf("%s\n",c+1);
		L=1; R=1; v=0; fr(i,0,25) cnt[i]=0;
		fr(i,1,m) cnt[c[i]-'a']=1;
		fr(i,0,25) v+=cnt[i];
		while(v){ v-=cnt[c[R]-'a']; cnt[c[R]-'a']=0; R++; }
		int ans=R-L;
		fr(i,1,R-1) cnt[c[i]-'a']++;
		while(1)
		{
			if(v){ if(R>m) break; cnt[c[R]-'a']++; if(cnt[c[R]-'a']==1) v--; R++; }
			else { ans=std::min(ans,R-L); /*printf("%d %d\n",L,R);*/ cnt[c[L]-'a']--; if(!cnt[c[L]-'a']) v++; L++; }
		}
		printf("%d\n",ans);
	}
	return 0;
}
