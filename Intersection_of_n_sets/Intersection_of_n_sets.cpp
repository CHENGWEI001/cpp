// inspire by  https://www.geeksforgeeks.org/intersection-of-n-sets/

// C++ program to find intersection of n sets
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;

// The main function that receives a set of sets as parameter and
// returns a set containing intersection of all sets

// time complexity: O(mk), k sets and avg each set m items
// space complexity: O(n) , n is max set size among sets
vector <int> getIntersectionHmap(vector < vector <int> > &sets)
{
    unordered_map<int, int> hmap;
    for (int v: sets[0]) {
        hmap[v]++;
    }
    for (auto &set: sets) {
        auto prev = hmap;
        hmap.clear();
        for (int v: set) {
            if (prev.count(v)) {
                hmap[v]++;
                if(prev[v]-- == 1) {
                    prev.erase(v);
                }
            }
        }
    }
    vector<int> ans;
    for (auto &item: hmap) {
        for (int i = 0; i < item.second; i++) {
            ans.push_back(item.first);
        }
    }
    return ans;
}


vector <int> getIntersection(vector < vector <int> > &sets) {
    int m = sets.size();
    vector<int> indice(m, 0);
    vector<int> ans;
    while (1) {
        bool theSame = true;
        int minIdx = 0;
        for (int i = 1; i < m; i++) {
            if (indice[i] == sets[i].size()) {
                return ans;
            }
            if (sets[i][indice[i]] < sets[minIdx][indice[minIdx]]) {
                minIdx = i;
            }
            if (sets[i][indice[i]] != sets[i-1][indice[i-1]]) {
                theSame = false;
            }
        }
        if (theSame) {
            ans.push_back(sets[0][indice[0]]);
            for (int i = 0; i < m; i++) {
                indice[i]++;
            }
        } else {
            indice[minIdx]++;
        }
    }
    return ans;
}

// A utility function to print a set of elements
void printset(vector <int> set)
{
    for (int i = 0 ; i < set.size() ; i++)
        cout<<set[i]<<" ";
}


// Test case
void TestCase1()
{
    vector < vector <int> > sets;
    vector <int> set1;
    set1.push_back(1);
    set1.push_back(1);
    set1.push_back(2);
    set1.push_back(2);
    set1.push_back(5);

    sets.push_back(set1);

    vector <int> set2;
    set2.push_back(1);
    set2.push_back(1);
    set2.push_back(4);
    set2.push_back(3);
    set2.push_back(5);
    set2.push_back(9);

    sets.push_back(set2);

    vector <int> set3;
    set3.push_back(1);
    set3.push_back(1);
    set3.push_back(2);
    set3.push_back(3);
    set3.push_back(5);
    set3.push_back(6);

    sets.push_back(set3);

    vector <int> r = getIntersection(sets);

    printset(r);

}

// Driver program to test above functions
int main()
{
    TestCase1();
    return 0;
}