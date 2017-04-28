#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define psi pair<int,pii>
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MAXN = 501;

int n,m;
string mat[MAXN];
int dist[MAXN][MAXN];
int mov[4] = {1, -1, 0, 0};
int mov2[4] = {0, 0, 1, -1};

int bfs(int x,int y) {
    forn(i, n)
    forn(j, m)
        dist[i][j] = 1e8;

    deque<pii> q;
    dist[x][y] = 1;
    q.push_back(pii(x, y));

    while(!q.empty()) {
        x = q.front().fi;
        y = q.front().se;
        q.pop_front();

        forn(i, 4) {
            int x1 = x + mov[i];
            int y1 = y + mov2[i];
            if(x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || mat[x1][y1] == '#') 
                continue;
            int d = (mat[x1][y1] == 'c');
            if(dist[x1][y1] > dist[x][y] + d) {
                dist[x1][y1] = dist[x][y] + d;
                if(d) q.push_back(pii(x1, y1));
                else q.push_front(pii(x1, y1));
            }
        }
    }

    int mini = 1e8;
    forn(i, n)
        if(mat[i][0] == 'D')
            mini = min(mini, dist[i][0]);
    
    forn(i, n)
        if(mat[i][m - 1] == 'D')
            mini = min(mini, dist[i][m - 1]);

    forn(i, m)
        if(mat[0][i] == 'D')
            mini = min(mini, dist[0][i]);

    forn(i, m)
        if(mat[n - 1][i] == 'D')
            mini = min(mini, dist[n - 1][i]);

    return mini;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int x,y;
    cin>>n>>m;
    forn(i, n)
        cin>>mat[i];

    cin>>x>>y;
    x--,y--;
    cout<<bfs(x, y)<<endl;
    return 0;
}
