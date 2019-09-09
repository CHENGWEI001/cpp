        // return min max base on the state, where state is grid of people and bike
        // memo store serialized state to min max of that state
        int dfs(vector<vector<char>> &state, unordered_map<string, int> &memo) {
            string key = makeKey(state);
            if (memo.count(key)) {
                return memo[key];
            }
            int m = state.size();
            int n = state[0].size();
            vector<pair<int, int>> pli;
            vector<pair<int, int>> bli;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (state[i][j] == 'P') {
                        pli.push_back({i, j});
                    } else if (state[i][j] == 'B') {
                        bli.push_back({i, j});
                    }
                }
            }
            int ansMin = -1;
            for (int i = 0; i < pli.size(); i++) {
                for (int j = 0; j < bli.size(); j++) {
                    int bs(pli[i].first - bli[j].first) + abs(pli[i].second - bli[j].second);
                    state[pli[i].first][pli[i].second] = '0';
                    state[bli[j].first][bli[j].second] = '0';
                    int subDist = dfs(state, memo);
                    state[pli[i].first][pli[i].second] = 'P';
                    state[bli[j].first][bli[j].second] = 'B';
                    ansMin = min(ansMin, max(currDist, subDist));
                }
            }
            memo[key] = ansMin;
            return ansMin;
        }