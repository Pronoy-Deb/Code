#include <iostream>
#include <vector>

using namespace std;

void printMatrix(const vector<vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (auto val : row) {
            cout << val;
        }
        cout << '\n';
    }
}

vector<vector<char>> transposeMatrix(const vector<vector<char>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<char>> transpose(cols, vector<char>(rows));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transpose[j][i] = matrix[i][j];
        }
    }

    return transpose;
}

int main() {
    int rows, cols;
    cin >> rows; cols = rows;

    vector<vector<char>> matrix(rows, vector<char>(cols));
    string ar[rows];
    for (int i = 0; i < rows; ++i) {
        cin >> ar[i];
    }
    for(int i=0;i<rows;++i) {
        for(int j=0;j<rows;++j) {
            matrix[i][j] = ar[i][j];
        }
    }
    vector<vector<char>> transpose = transposeMatrix(matrix);
    printMatrix(transpose);

    return 0;
}
