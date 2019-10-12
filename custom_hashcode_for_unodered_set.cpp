// https://www.geeksforgeeks.org/count-maximum-points-on-same-line/

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
private:
    struct pair_hash
    {
        template <class T1, class T2>
        size_t operator() (const pair<T1, T2> &pair) const
        {
            return hash<T1>()(pair.first) ^ hash<T2>()(pair.second);
        }
    };    
public:
    int maxPoints(vector<Point>& points) {
        if (points.size() < 2) return points.size();
        int max_size = 0;
        unordered_map<pair<int, int>, int, pair_hash> hm;
        for (int i = 0; i < points.size(); i++)
        {
            hm.clear();
            int overlapPoint = 1;
            int verticalPoint = 0;
            int local_max = 0;
            for (int j = i+1; j < points.size(); j++)
            {
                //printf("i:%d, j:%d\n", i, j);
                if (points[i].x == points[j].x && points[i].y == points[j].y)
                    overlapPoint++;
                else if (points[i].x == points[j].x)
                {   
                    verticalPoint++;
                    local_max = max(local_max, verticalPoint);  
                    //printf("key:%d, max_size:%d\n", key, max_size);
                }
                else
                {
                    int yDif = points[i].y - points[j].y;
                    int xDif = points[i].x - points[j].x;
                    int g = __gcd(xDif, yDif);
                    // reducing the difference by their gcd
                    yDif /= g;
                    xDif /= g;    
                    pair<int, int> key = make_pair(xDif, yDif);
                    //pair<double, double> key = make_pair(m, d);
                    //hm[key].insert(i);
                    hm[key]++;
                    local_max = max(local_max, hm[key]);  
                    //printf("m:%f, d:%f, max_size:%d\n", m, d, max_size);
                    //printf("xDif:%d, yDif:%d, max_size:%d\n", xDif, yDif, max_size);
                }
            }
            max_size = max(max_size, local_max + overlapPoint); 
        }
        return max_size;
    }
};
