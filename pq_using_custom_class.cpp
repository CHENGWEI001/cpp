/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
 
 //https://www.lintcode.com/problem/k-closest-points/description?_from=ladder&&fromId=11

class Element {
public:
    int dist;
    int x;
    int y;
    Element(int dist, int x, int y) {
        this->dist = dist;
        this->x = x;
        this->y = y;
    }
};

class MyCmp {
public:
    bool operator() (const Element &a, const Element &b) {
        if (a.dist != b.dist) {
            return a.dist < b.dist;
        }
        if (a.x != b.x) {
            return a.x < b.x;
        }
        return a.y < b.y;
    }
};

class Solution {
public:
    /**
     * @param points: a list of points
     * @param origin: a point
     * @param k: An integer
     * @return: the k closest points
     */
    vector<Point> kClosest(vector<Point> &points, Point &origin, int k) {
        priority_queue<Element, vector<Element>, MyCmp> pq;
        vector<Point> ans;
        for (auto &p: points) {
            int dist = getDist(p, origin);
            Element ele(dist, p.x, p.y);
            pq.push(ele);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        while (pq.size()) {
            // don't use reference, since using reference after poping is having unexpected result
            // or either using reference but pop after using it
            auto &ele = pq.top();
            pq.pop();
            ans.push_back(Point(ele.x, ele.y));
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
    
    int getDist(Point &a, Point &b) {
        int xd = (a.x - b.x);
        int yd = (a.y - b.y);
        return xd*xd + yd*yd;
    }
};
