#include <iostream>
using namespace std;

bool checkConstraints(int** x, int* A, int n, int m);

/* 全擺 0: 1*/
/* 每個站點平均擺: 2 */
/* 根據 U 哪裡大就投哪的方法: 3 */

int K = 4;

int main()
{
    cout << "breakpoint 1";
    int n = 0, m = 0;
    float Q[K];
    cin >> n >> m;
    for (int i = 0; i < K; i++) cin >> Q[i];

    int* R = new int [n];
    int* A = new int [n];
    int* B = new int [m];
    for (int i = 0; i < n; i++) cin >> R[i];
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < m; i++) cin >> B[i];

    float** U = new float* [n];
    int** D = new int* [m];
    for (int i = 0; i < n; i++)
    {
        U[i] = new float [m];
        for (int j = 0; j < m; j++) cin >> U[i][j];
    }
    for (int i = 0; i < m; i++)
    {
        D[i] = new int [m];
        for (int j = 0; j < m; j++) cin >> D[i][j];
    }

    int** x = new int* [n];
    for (int i = 0; i < n; i++) x[i] = new int [m];

    cout << "breakpoint 2";
    
    int k = 0;
    int revenue = 0, indexI = 0, indexJ = 0;
    int* carIn = new int [m];
    // while (true)
    // {
    int maxRevenue = 0;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int sum = 0;
            int index1 = j;
            for (int j2 = 0; j2 < m; j++)
            {
                if (D[index1][j2] == 0) k = 0;
                if (1 <= D[index1][j2] && D[index1][j2] <= 300) k = 1;
                if (301 <= D[index1][j2] && D[index1][j2] <= 500) k = 2;
                if (501 <= D[index1][j2] && D[index1][j2] <= 1000) k = 3; 
                sum += carIn[j2] * Q[k];
                // index1++;
            }

            revenue = 24 * R[i] * (U[i][j] - sum + Q[0]) * (x[i][j] + 1);
            if (revenue > maxRevenue && 0 < A[i] && 0 < B[j] && carIn[indexJ] < B[indexJ])
            {
                maxRevenue = revenue;
                indexI = i;
                indexJ = j;
            }
        }
    }
    if (maxRevenue > 0 && 0 < A[indexI] && 0 < B[indexJ] && carIn[indexJ] < B[indexJ])
    {
        x[indexI][indexJ]++;
        A[indexI]--;
        B[indexJ]--;
        carIn[indexJ]++;
    }
    // if (maxRevenue == 0) break;
    // }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) 
        {
            cout << "x[i][j]" << x[i][j];
            if (j != m - 1) cout << ",";
        }
        cout << "\n";
    }
    
    for (int i = 0; i < n; i++)
    {
        delete [] U[i];
        delete [] x[i];
    }
    for (int i = 0; i < m; i++) delete [] D[i];
    delete [] R;
    R = nullptr;
    delete [] A;
    A = nullptr;
    delete [] B;
    B = nullptr;
    delete [] U;
    U = nullptr;
    delete [] D;
    D = nullptr;
    delete [] x;
    x = nullptr;
    delete [] carIn;
    carIn = nullptr;
}

bool checkConstraints(int** x, int* A, int n, int m) {
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += x[i][j];
        }
        if (sum > A[i]) {
            return false; // 如果任何限制式不被滿足，則返回 false
        }
    }
    return true; // 所有限制式都被滿足，返回 true
}

