//https://leetcode.com/problems/k-closest-points-to-origin
struct MyCmp {
    vector<vector<int>> *psPtr;
    vector<int> cent;
    MyCmp(vector<vector<int>> &ps, vector<int> center) {
        psPtr = &ps;
        cent = center;
    }
    bool operator() (const int a, const int b) {
        return dist((*psPtr)[a]) < dist((*psPtr)[b]);
    }
    
    int dist(vector<int> &a) {
        int x = a[0] - cent[0];
        int y = a[1] - cent[1];
        return x*x + y*y;
    }
};

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        MyCmp mycmp(points, {0,0});
        // I found I must specify like below , priority_queue<int> pq(mycmp) won't work
        priority_queue<int, vector<int>, MyCmp> pq(mycmp);
        for (int i = 0; i < points.size(); i++) {
            pq.push(i);
            if (pq.size() > K) {
                pq.pop();
            }
        }
        vector<vector<int>> ans;
        while (pq.size()) {
            int idx = pq.top();
            pq.pop();
            ans.push_back(points[idx]);
        }
        return ans;
    }
};
