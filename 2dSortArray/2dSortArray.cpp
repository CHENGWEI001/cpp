#include <vector>
#include <stdio.h>
#include <queue>

using namespace std;

// gg mj  gg 549518

void twodSortV1(vector<vector<int>> &matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> ans(m, vector<int>(n, 0));
    // int total = m*n;
    int idx = 0;
    priority_queue<pair<int, int>> pq;
    vector<int> indice(m, 0);
    for (int i = 0; i < m; i++) {
        pq.push({-matrix[i][0], i});
    }
    while (pq.size()) {
        auto curr = pq.top();
        pq.pop();
        ans[idx/n][idx%n] = -curr.first;
        idx++;
        int liIdx = curr.second;
        if (indice[liIdx] + 1 < n) {
            int i = indice[liIdx] + 1;
            pq.push({-matrix[liIdx][i], liIdx});
            indice[liIdx]++;
        }
    }
    matrix = ans;
}

void quickSort(vector<vector<int>> &matrix, int start, int end, int n) {
    if (start > end) {
        return;
    }
    int mi = start + (end - start)/2;
    swap(matrix[mi/n][mi%n], matrix[start/n][start%n]);
    int pivot = matrix[start/n][start%n];
    int j = start+1;
    for (int i = start+1; i <= end; i++) {
        if (matrix[i/n][i%n] <= pivot) {
            swap(matrix[i/n][i%n], matrix[j/n][j%n]);
            j++;
        }
    }
    // j is at first > pivot item
    swap(matrix[start/n][start%n], matrix[(j-1)/n][(j-1)%n]);
    quickSort(matrix, start, j-2, n);
    quickSort(matrix, j, end, n);
}

void twodSortV2(vector<vector<int>> &matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    quickSort(matrix, 0, m*n-1, n);
}



void showMatrix(vector<vector<int>> &ma) {
    int m = ma.size();
    int n = ma[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", ma[i][j]);
        }
        printf("\n");
    }
}

int main() {
    vector<vector<int>> m = {
        {5, 12, 17},
        {1,  2,  4},
        {12,14, 18},
    };
    twodSortV2(m);
    showMatrix(m);
    return 0;
}

