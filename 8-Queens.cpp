#include <bits/stdc++.h>
using namespace std;

bool isSafe(vector<vector<int>>& mat, int row, int col) {
    int n = mat.size();
    int i, j;

    for (i = 0; i < row; i++)
        if (mat[i][col])
            return false;

    for (i = row-1, j = col-1; i >= 0 && 
         j >= 0; i--, j--)
        if (mat[i][j])
            return false;

    for (i = row-1, j = col+1; j < n && 
         i >= 0; i--, j++)
        if (mat[i][j])
            return false;

    return true;
}

bool placeQueens(int row, vector<vector<int>>& mat) {
    int n = mat.size();

    if(row == n) return true;

    for(int i = 0; i < n; i++){

        if(isSafe(mat, row, i)){
            mat[row][i] = 1;
            if(placeQueens(row + 1, mat)) 
                return true;
            mat[row][i] = 0;
        }
    }
    return false;
}
vector<vector<int>> queens() {
    int n = 8;

    vector<vector<int>> mat(n, vector<int>(n, 0));

    placeQueens(0, mat);
    
    return mat;
}

int main() {
    vector<vector<int>> res = queens();
    for (auto v: res) {
        for (auto square: v) {
            cout << square << " ";
        }
        cout << endl;
    }
    return 0;
}
