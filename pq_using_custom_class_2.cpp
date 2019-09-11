//https://leetcode.com/problems/reorganize-string/
// https://www.geeksforgeeks.org/stl-priority-queue-for-structure-or-class/

struct Ele{
    int cnt;
    char c;
};

bool operator< (const Ele &a, const Ele &b) {
    return a.cnt < b.cnt;
}

class Solution {
public:
    string reorganizeString(string S) {
        int ccnt[128] = {0};
        priority_queue<Ele> pq;
        queue<Ele> q;
        int cnt = 2;
        string ans;
        for (char c: S) {
            ccnt[c]++;
        }
        for (int i = 0; i < 128; i++) {
            if (ccnt[i] > 0) {
                pq.push({ccnt[i], (char)i});    
            }
        }
        while (pq.size()) {
            auto curr = pq.top();
            pq.pop();
            ans.push_back(curr.c);
            // cout << ans << endl;
            if (curr.cnt-- > 1) {
                q.push(curr);
            }
            if (cnt-- == 1) {
                while (q.size()) {
                    pq.push(q.front());
                    q.pop();
                }
                cnt = 2;
            }
        }
        if (ans.size() == S.size()) {
            return ans;
        }
        return "";
    }
};
