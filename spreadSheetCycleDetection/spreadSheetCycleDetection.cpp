#include <vector>
#include <queue>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//  gg 550549

bool isApha(char c) {
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// 求get_reference_list("=A10*5*A77*(B2+3/C3)")   ⇒  ["A10", "A77", "B2", "C3"]
vector<string> getRefList(string &s) {
    vector<string> res;
    for (int i = 0; i < s.size(); i++) {
        if (!isApha(s[i])) {
            continue;
        }
        int j = i;
        string buf;
        while (j < s.size() && (isApha(s[j]) || isDigit(s[j]))) {
            buf.push_back(s[j]);
            j++;
        }
        res.push_back(buf);
        i = j;
    }
    return res;
}

/*
has_circle({

  "A1": "=D1+B1+1",

  "B1": "=D1+C1+2",

  "C1": "=D1 + A1+3"

})  ⇒   True     // circular references between A1, B1, and C
*/

void makeGraph(vector<string> &exps, unordered_map<string, unordered_set<string>> &graph) {
    for (string &e: exps) {
        int i = 0;
        while (i < e.size() && e[i] != ':') {
            i++;
        }
        // i stop at ':'
        string ls = e.substr(0,i);
        string rs = e.substr(i+1);
        auto left = getRefList(ls);
        auto right = getRefList(rs);
        for (string &nei: right) {
            graph[left[0]].insert(nei);
            // printf("%s->%s\n", left[0].c_str(), nei.c_str());
        }
    }
}

void printPath(vector<string> &path) {
    for (string &s: path) {
        printf("%s -> ", s.c_str());
    }
}

bool dfs(const string &curr, unordered_map<string, unordered_set<string>> &graph, vector<string> &path, unordered_set<string> &vis) {
    if (vis.count(curr)) {
        return true;
    }
    path.push_back(curr);
    vis.insert(curr);
    for (const string &nei: graph[curr]) {
        if (dfs(nei, graph, path, vis)) {
            return true;
        }
    }
    vis.erase(curr);
    path.pop_back();
}

void printCycle(unordered_map<string, unordered_set<string>> &graph) {
    vector<string> path;
    unordered_set<string> visited;
    for (auto &item: graph) {
        const string &p = item.first;
        if (dfs(p, graph, path, visited)) {
            printPath(path);
            return;
        }
    }
}

bool hasCycle(vector<string> &exps) {
    unordered_map<string, unordered_set<string>> graph;
    makeGraph(exps, graph);
    unordered_map<string, int> indegree;
    queue<string> q;
    for (auto &item: graph) {
        const string &p = item.first;
        const auto &neis = item.second;
        if (!indegree.count(p)) {
            indegree[p] = 0;
        }
        for (auto &nei: neis) {
            indegree[nei]++;
        }
    }
    for (auto &item: indegree) {
        if (item.second == 0) {
            q.push(item.first);
        }
    }
    int cnt = 0;
    while (q.size()) {
        auto curr = q.front();
        cnt++;
        q.pop();
        for (auto &nei: graph[curr]) {
            if (indegree[nei]-- == 1) {
                q.push(nei);
            }
        }
    }
    bool hs = cnt != graph.size();
    if (hs) {
        printCycle(graph);
    }
}

void test1() {
    string s = "=A10*5*A77*(B2+3/C3)";
    auto res = getRefList(s);
    for (string &ss: res) {
        printf("%s, ", ss.c_str());
    }
    printf("\ndone test1\n\n");
}

void test2() {
    vector<string> exps = {
      "\"A1\": \"=D1+B1+1",
      "\"B1\": \"=D1+C1+2",
      "\"C1\": \"=D1 + A1+3",
    };
    bool res = hasCycle(exps);
    printf("hasCycle:%d\n", res? 1: 0);

}

int main() {
    // test1();
    test2();
    return 0;
}