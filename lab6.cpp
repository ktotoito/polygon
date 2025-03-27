#include <iostream>
#include <vector>

int uniquePaths(int m, int n) { // m и n = 4+4=8 байт
    std::vector<int> upperrow(n, 1); // 32 + 4*n байт

    for (int i = 1; i < m; i++) { // i = 4 байта
        std::vector<int> currentrow(n, 1); // 32 + 4*n байт
        for (int j = 1; j < n; j++) { // j = 4 байта
            currentrow[j] = currentrow[j - 1] + upperrow[j];
            upperrow[j] = currentrow[j];
        }
    }
    return upperrow[n - 1];
}
