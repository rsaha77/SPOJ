#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
using namespace std;
#else
#include "header.h"
#endif
#define SS(n) scanf("%s",n)
#define pn putchar_unlocked('\n')
#define ps putchar_unlocked(' ')
#define sz(s) int((s).size())
#define rep(i,n) for(int(i)=0; (i)<(n);++(i))
#define ru(i,a,b) for(int(i)=a;(i)<=(b);++(i))
#define rd(i,b,a) for(int(i)=b;(i)>=(a);--(i))
#define clr(a) memset(a,0,sizeof(a))
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
typedef long long LL; typedef vector <int> vi; typedef pair<int,int> pii; typedef map <int,int> mii; template <class T> inline T max(T a,T b,T c) {return (max(max(a,b),c));} template <class T> inline T min(T a,T b,T c) {return (min(min(a,b),c));} template <class T> inline T sqr(T x) {return x*x;} inline int inp() {int n=0,s=1;char p=getchar_unlocked();if(p=='-')s=-1;while((p<'0'||p>'9')&&p!=EOF&&p!='-')p=getchar_unlocked();if(p=='-')s=-1,p=getchar_unlocked();while(p>='0'&&p<='9')n=(n<<3)+(n<<1)+(p-'0'),p=getchar_unlocked();return n*s;} void out(int x){if(x<0)putchar_unlocked('-'),x=-x;int ll=0,dd[10];while(x)dd[ll++]=x%10,x/=10;if(!ll)dd[ll++]=0;while(ll--)putchar_unlocked(dd[ll]+48);} inline int ins(int x,int y,int m,int n){return (x>=1&&x<=m&&y>=1&&y<=n);} template <class T> inline T gcd(T a,T b){return (!b? a : gcd(b,a%b));} template <class T> inline T ABS(T x){return ((x)>0?(x):(-(x)));}
const int N = 1e5 + 11;
const LL mod = 1000000007;

vector <pii> edge[N];
LL dp[N];

LL dfs1(int u, int p) {
  LL cnt = 0;
  rep(i,sz(edge[u])) {
    int v = edge[u][i].ff;
    LL w = edge[u][i].ss;
    if(v != p) {
      cnt += w*dfs1(v,u) + w;
      if(cnt >= mod) cnt %= mod;
    }
  }
  return dp[u] = cnt;
}

void dfs2(int u, int p) {
  rep(i,sz(edge[u])) {
    int v = edge[u][i].ff;
    LL w = edge[u][i].ss;
    if(v != p) {
      LL sub = dp[v]*w + w; if(sub >= mod) sub %= mod;
      dp[u] = dp[u] + mod - sub;
      dp[v] += dp[u]*w; if(dp[v] >= mod) dp[v] %= mod;
      dfs2(v,u);
    }
  }
}


//4:26 am to 5:24 (Almost sure of AC) ---- (WA at 11th TC :/  ..)
//4:26 am to 5:48 (WA at 9 TC :/  ..) // Thought i submitted the same code!!!!
//4:26 am to 6:30 (EXPECTING AC) .. PROBLEM WAS WITH MOD ... Argghh!!
int main() {
  #ifndef ONLINE_JUDGE
    freopen("in2.txt","r",stdin);
  #endif
  for(int tc=1,t=1; tc<=t; ++tc) {
    int n=inp();
    for(int i=1; i<n; ++i) {
      int u=inp(), v=inp(), co=inp();
      edge[u].pb(mp(v,co));
      edge[v].pb(mp(u,co));
    }
    dfs1(1,0);
    LL ans = 0;
    //Rooted at 1.
    ru(i,1,n) {
      ans += dp[i];
      if(ans >= mod) ans %= mod;
    }
    dfs2(1,0);
    //In opposite direction.
    ru(i,1,n) {
      ans += dp[i];
      if(ans >= mod) ans %= mod;
    }
    out(ans);
  }
}