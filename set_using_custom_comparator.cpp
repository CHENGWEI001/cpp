//https://leetcode.com/problems/exam-room/

struct MyCmp {
    int n = 0;
    MyCmp() {
        
    }
    MyCmp(int n) {
        this->n = n;
    }
    
    // note for comparator in set, operator() must be const
    // so any thing called in this API must be const as well
    bool operator() (const pair<int, int> &a, const pair<int, int> &b) const {
        int da = getDist(a);
        int db = getDist(b);
        if (da == db) {
            return a.first < b.first;
        }
        return da > db;
    }
    
    //so even in this getDist, has const to gurantee it is not modifying 
    // anything here
    int getDist(const pair<int, int> &a) const{
        int l = a.first;
        int r = a.second;
        if (l == -1 || r == n) {
            return r - l - 1;
        }
        return (r - l)/2;
    }
};

class ExamRoom {
private:
    int n;
    set<pair<int, int>, MyCmp> slots;
public:
    ExamRoom(int N) {
        n = N;
        MyCmp mycmp(n);
        slots = set<pair<int, int>, MyCmp>(mycmp);
        slots.insert({-1, n});
    }
    
    int seat() {
        auto candp = *slots.begin();
        // becareful if erase with slots.end(), it will stuck
        slots.erase(slots.begin());
        int cand = -1;
        int l = candp.first;
        int r = candp.second;
        if (l == -1) {
            cand = 0;
        } else if (r == n) {
            cand = n-1;
        } else {
            cand = l + (r - l)/2;
        }
        slots.insert({l, cand});
        slots.insert({cand, r});    
        return cand;
    }
    
    void leave(int p) {
        pair<int, int> p1, p2;
        for (auto it = slots.begin(); it != slots.end(); it++) {
            auto curr = *it;
            if (curr.first == p) {
                p1 = curr;
            }
            if (curr.second == p) {
                p2 = curr;
            }
        }
        // printf("to rm(%d,%d)\n", p1.first, p1.second);
        // printf("to rm(%d,%d)\n", p2.first, p2.second);
        // printf("size before rm:%d\n", slots.size());        
        slots.erase(p1);
        slots.erase(p2);
        // printf("size after rm:%d\n", slots.size());
        slots.insert({p2.first, p1.second});
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(N);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */
