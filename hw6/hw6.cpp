#include <iostream>
using namespace std;

const int K = 4;

void whereToPutTheCar(int n, int m, float* Q, int* R, int* A, int* B, float** U, int** D, int** x);

int main()
{
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

    whereToPutTheCar(n, m, Q, R, A, B, U, D, x);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) 
        {
            cout << x[i][j];
            if (j != m - 1) cout << ",";
        }
        cout << "\n";
    }
    
    for (int i = 0; i < n; i++)
    {
        delete [] U[i];
        delete [] x[i];
    }
    for (int i = 0; i < m; i++) {
        delete [] D[i];
    }

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
}

void whereToPutTheCar(int n, int m, float* Q, int* R, int* A, int* B, float** U, int** D, int** x)
{
    float target = 0, revenue = 0;
    int k = 0, indexI = 0, indexJ = 0;
    int* carIn = new int [m];
    float maxRevenue = 0;
    
    while (true)
    {
        // 每一次要新增一台車時都跑 3 (2 + 1) 層 for 迴圈，來看在哪個站點放哪個車型會有最大利益
        float revenue = 0;
        float maxTarget = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                x[i][j]++;
                carIn[j]++;
                A[i]--;
                
                float sum = 0;
                int index1 = j;
                for (int j2 = 0; j2 < m; j2++)
                {
                    if (D[index1][j2] == 0) k = 0;
                    if (1 <= D[index1][j2] && D[index1][j2] <= 300) k = 1;
                    if (301 <= D[index1][j2] && D[index1][j2] <= 500) k = 2;
                    if (501 <= D[index1][j2] && D[index1][j2] <= 1000) k = 3; 
                    if (1000 < D[index1][j2]) continue;
                    sum += carIn[j2] * Q[k];
                }

                target = 24 * R[i] * (U[i][j] - sum + Q[0]);
                revenue += target;
                // cout << "sum: " << sum << "\n";
                // cout << "target: " << target << "\n";
                if (target > maxTarget && revenue > 0 && 0 <= A[i] && carIn[j] <= B[j])
                {
                    maxTarget = target;
                    indexI = i;
                    indexJ = j;
                }
                x[i][j]--;
                carIn[j]--;
                A[i]++;
            }
        }
        
        // cout << "maxTarget: " << maxTarget << "\n";
        // cout << indexI << "," << indexJ << "\n";
        if (maxTarget > 0 && 0 < A[indexI] && carIn[indexJ] < B[indexJ])
        {
            x[indexI][indexJ]++;
            A[indexI]--;
            carIn[indexJ]++;
        }
        if (maxTarget <= 0) break;
    }
    delete [] carIn;
    carIn = nullptr;
}
