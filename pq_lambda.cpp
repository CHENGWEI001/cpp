// https://www.geeksforgeeks.org/tuples-in-c/
// http://www.cplusplus.com/reference/queue/priority_queue/
// https://thispointer.com/c11-lambda-how-to-capture-local-variables-inside-lambda/
// https://stackoverflow.com/questions/14896032/c11-stdset-lambda-comparison-function

// typedef tuple<int, int, int> myTuple;
typedef tuple<int, int> myTuple;

class Solution {
public:
    /**
     * @param arrs: the arrays
     * @return: the number of the intersection of the arrays
     */
    int intersectionOfArrays(vector<vector<int>> &arrs) {
        auto comp = [&](myTuple &a, myTuple &b) {
            // return get<0>(a) > get<0>(b);
            return arrs[get<0>(a)][get<1>(a)] > arrs[get<0>(b)][get<1>(b)];
        };
        priority_queue<myTuple, vector<myTuple>, decltype(comp)> pq(comp);
        
        for (int i = 0; i < arrs.size(); i++) {
            if (arrs[i].size() == 0) {
                return 0;
            }
            sort(arrs[i].begin(), arrs[i].end());
            pq.push(make_tuple(i, 0));
        }
        
        int count = 0;
        int lastValue = 0;
        int ans = 0;
        while (pq.size() > 0) {
            auto topTuple = pq.top();
            pq.pop();
            int r = get<0>(topTuple);
            int c = get<1>(topTuple);
            // cout<<arrs[r][c]<<endl;
            if (count == 0 || arrs[get<0>(topTuple)][get<1>(topTuple)] != lastValue) {
                lastValue = arrs[get<0>(topTuple)][get<1>(topTuple)];
                count = 1;
            } else {
                count++;
            }
            if (c + 1 < arrs[r].size()) {
                pq.push(make_tuple(r, c + 1));
            }
            if (count == arrs.size()) {
                ans++;
            }
        }
        
        return ans;
    }
};
