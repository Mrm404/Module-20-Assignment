#include <bits/stdc++.h>
using namespace std;
#define INF 1000000000

void weightedMazeRunner() {
    int n,m,T;
    cin >> n >> m >> T;

    vector<vector<int>> w(n, vector<int>(m));
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin >> w[i][j];

    int jump_cost; 
    cin >> jump_cost;

    vector<vector<pair<int,int>>> diag(n+m-1);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            diag[i+j].push_back({i,j});

    vector<vector<vector<int>>> dp(
        T+1, vector<vector<int>>(n, vector<int>(m, INF))
    );
    dp[0][0][0] = w[0][0];

    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    for(int t=0;t<T;t++){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(dp[t][i][j] == INF) continue;

                
                dp[t+1][i][j] = min(dp[t+1][i][j], dp[t][i][j] + w[i][j]);

                
                for(int k=0;k<4;k++){
                    int ni = i + dx[k], nj = j + dy[k];
                    if(ni>=0 && ni<n && nj>=0 && nj<m)
                        dp[t+1][ni][nj] = min(dp[t+1][ni][nj],
                                              dp[t][i][j] + w[ni][nj]);
                }

                
                for(auto p : diag[i+j]){
                    int x = p.first, y = p.second;
                    dp[t+1][x][y] =
                        min(dp[t+1][x][y],
                            dp[t][i][j] + jump_cost + w[x][y]);
                }
            }
        }
    }

    if(dp[T][n-1][m-1] >= INF)
        cout << -1 << "\n";
    else
        cout << dp[T][n-1][m-1] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    weightedMazeRunner();
}
