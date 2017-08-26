#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
using namespace std;
#else
#include "header.h"
#include "debug.h"
#endif
#define sz(s) int((s).size())
#define clr(a) memset(a,0,sizeof(a))
#define all(x) (x).begin(),(x).end()
#define rep(i,n) for(int(i)=0; (i)<(n);++(i))
#define ru(i,a,b) for(int(i)=a;(i)<=(b);++(i))
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
typedef pair <int,int> pii;
typedef int64_t LL;
template <class T> inline T gcd(T a,T b){return (!b? a : gcd(b,a%b));}
template <class T> inline T ABS(T x){return ((x)>0?(x):(-(x)));}
inline int inp () {int n=0,s=1;char p=getchar_unlocked();if(p=='-')s=-1;while((p<'0'||p>'9')&&p!=EOF&&p!='-')p=getchar_unlocked();if(p=='-')s=-1,p=getchar_unlocked();while(p>='0'&&p<='9')n=(n<<3)+(n<<1)+(p-'0'),p=getchar_unlocked();return n*s;}
inline void out (int x) {if(x<0)putchar_unlocked('-'),x=-x;int ll=0,dd[10];while(x)dd[ll++]=x%10,x/=10;if(!ll)dd[ll++]=0;while(ll--)putchar_unlocked(dd[ll]+48);}
const int N = 20000 + 10;
 
vector <int> g [N];
int dp [N], dp2 [N], dp3 [N], marked [N];
pii edge [N];
 
void dfs (int u, int p) {
  for (int v : g [u]) {
    if (v != p) {
      dfs (v, u);
      dp [u] += dp [v];
    }
  }
}
 
void dfs2 (int u, int p) {
  for (int v : g [u]) {
    if (v != p) {
      dp2 [v] += dp2 [u];
      dfs2 (v, u);
    }
  }
}
 
void dfs3 (int u, int p) {
  for (int v : g [u]) {
    if (v != p) {
      dfs3 (v, u);
      dp3 [u] += dp3 [v];
    }
  }
}
 
int dfs4 (int u, int p) {
  int cnt = 0;
  for (int v : g [u]) {
    if (v != p && dp3 [v] == 0) {
      cnt += dfs4 (v, u);
    }
  }
  return cnt + 1;
}
  
 
int main() {
  #ifndef ONLINE_JUDGE
    freopen ("in.txt", "r", stdin);
  #endif
  int tt = inp ();
  for (int tc = 1; tc <= tt; ++tc) {
    int n = inp (), k = inp ();
    for (int i = 1; i <= n; ++i) {
      g [i].clear ();
      marked [i] = dp3 [i] = dp2 [i] = dp [i] = 0;
    }
    for (int i = 1; i < n; ++i) {
      int u = inp (), v = inp ();
      g [u].pb (v);
      g [v].pb (u);
      edge [i] = mp (u, v);
    }
    for (int i = 0; i < k; ++i) {
      int idx = inp ();
      ++idx;
      int u = edge [idx].ff;
      int v = edge [idx].ss;
      dp [u] += 1;
      dp [v] += 1;
      marked [u] = dp3 [u] = dp2 [u] = dp [u];
      marked [v] = dp3 [v] = dp2 [v] = dp [v];
    }
    
    dfs  (1, 0);
    int cnt_one = 0;
    int u = 0, v = 0;
    for (int i = 1; i <= n; ++i) {
      if (dp [i] == 1) {
        ++cnt_one;
        if (u == 0) {
          u = i;
        } else {
          v = i;
        }
      }
    }
    
    if (! (cnt_one >= 1 && cnt_one <= 2)) {
      puts ("0");
      continue;
    }
    
    if (cnt_one == 2) {
      dfs2 (u, 0);
      if (dp2 [v] != (k << 1)) {
        puts ("0");
        continue;
      }
    }
    
    // Ans exists and (ans >= 1).
    
    if (cnt_one == 1) {
      for (int i = 1; i <= n; ++i) {
        if (marked [i] == 1 && dp [i]  == (k << 1)) {
          v = i;
        }
      }
    }
    
    // Now I have u & v.
    
    dfs3 (u, 0);
    for (int i = 1; i <= n; ++i) {
      if (dp3 [i] == (k << 1) && !marked [i]) {
        dp3 [i] = 0;
      }
    }
    
    int cnt1 = dfs4 (u, 0);
    int cnt2 = dfs4 (v, 0);
    
    out (cnt1 * cnt2);
    putchar_unlocked ('\n');
  }
}