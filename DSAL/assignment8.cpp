#include <iostream>
using namespace std;

int sum(int arr[], int lo, int hi) {
    int sum = 0;
    for (int i = lo; i <= hi; i++) {
        sum += arr[i];
    }
    return sum;
}

int findOBST(int values[], int freqeuncies[], int n) {
    int cost[n][n];
    for(int i = 0; i < n; i++) {
        cost[i][i] = freqeuncies[i];
    }
    for(int len = 2; len <= n; len++) {
        for(int lo = 0; lo < n - len + 1; lo++) {
            int hi = lo + len - 1;
            cost[lo][hi] = 2147483647;
            int subarraySum = sum(freqeuncies, lo, hi);
            for (int i = lo; i <= hi; i++) {
                int leftCost = i > lo ? cost[lo][i - 1] : 0;
                int rightCost = i < hi ? cost[i + 1][hi] : 0;
                int currentCost = leftCost + rightCost + subarraySum;
                if (currentCost < cost[lo][hi]) {
                    cost[lo][hi] = currentCost;
                }
            }
        }
    }
    return cost[0][n-1];
}

int main() {
    int k[] = {12, 13, 14, 15};
    int p[] = {10, 9, 8, 7};
    cout << findOBST(k, p, 4);
}
