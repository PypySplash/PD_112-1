#include <iostream>
#include <cmath>
using namespace std;
const int MAX_d1_MIN = 5001;
const int MAX_d2_MIN = 1001;

void baseNTUFlix(int& memberNumber, int& movieNumber, int& designatedMember, const int* movieListSizes, const int** movieLists, const int** scoreLists, int answerArray []);
void findUnwatchedMovies(int& movieNumber, int& designatedMember, const int* movieListSizes, const int** movieLists, bool* found);
void recommendMovie(int& memberNumber, int& movieNumber, const int* movieListSizes, const int** movieLists, const int** scoreLists, int answerArray [], bool* found);

int main()
{
    int memberNumber = 0, movieNumber = 0, designatedMember = 0;
    cin >> memberNumber >> movieNumber >> designatedMember;

    int* movieListSizes = new int [memberNumber];
    int** movieLists = new int* [memberNumber];
    int** scoreLists = new int* [memberNumber];

    for (int i = 0; i < memberNumber; i++)
    {
        cin >> movieListSizes[i];
        // movieLists[i] = new int [movieListSizes[i]];  // 動態記憶體配置二維陣列時，需記得 new column 的數量
        // scoreLists[i] = new int [movieListSizes[i]];
        movieLists[i] = new int [movieListSizes[i]];  // 動態記憶體配置二維陣列時，需記得 new column 的數量
        scoreLists[i] = new int [movieListSizes[i]];
        for (int j = 0; j < movieListSizes[i]; j++)
        {
            cin >> movieLists[i][j];
            cin >> scoreLists[i][j];
        }
    }
    
    int* d1Array = new int [memberNumber];
    for (int i = 0; i < memberNumber; i++) 
    {
        int d1 = 0, rIndex = 0, pIndex = 0;
        for (int j = 0; j < movieNumber; j++) 
        {
            if (i == designatedMember - 1) 
            {
                d1 = MAX_d1_MIN;
                break;
            }
            
            // 會員 r 看過，p 沒看過
            if (j == movieLists[i][rIndex] - 1 && j != movieLists[designatedMember - 1][pIndex] - 1)
            {
                // d1 += abs(movieArray[i][j] - movieArray[designatedMember - 1][j]);
                d1 += abs(scoreLists[i][rIndex] - 0);
                if (rIndex != movieListSizes[i] - 1)
                    rIndex++;
            }
            // 會員 p 看過，r 沒看過
            if (j != movieLists[i][rIndex] - 1 && j == movieLists[designatedMember - 1][pIndex] - 1)
            {
                d1 += abs(0 - scoreLists[designatedMember - 1][pIndex]);
                if (pIndex != movieListSizes[designatedMember - 1] - 1)
                    pIndex++;
            }
            // 兩個人都看過
            if (j == movieLists[i][rIndex] - 1 && j == movieLists[designatedMember - 1][pIndex] - 1)
            {
                d1 += abs(scoreLists[i][rIndex] - scoreLists[designatedMember - 1][pIndex]);
                if (rIndex != movieListSizes[i] - 1) 
                    rIndex++;
                if (pIndex != movieListSizes[designatedMember - 1] - 1)
                    pIndex++;
            }
        }
        d1Array[i] = d1;
        // cout << "d1Array:" << d1 << "\n";
    }

    int rMember = 0;
    int d1Min = MAX_d1_MIN;
    int d1Count = 0;
    // 找出d1Min，並記錄是誰，同時有複數個人，優先記編號最小者
    for (int i = 0; i < memberNumber; i++) 
    {
        if (d1Array[i] < d1Min) 
        {
            d1Min = d1Array[i];
            rMember = i + 1;
        }
    }

    // 遍歷 d1Array，看有幾個 d1 = d1Min，紀錄同時 d1 最小的人數
    for (int i = 0; i < memberNumber; i++) 
    {
        if (d1Array[i] == d1Min) 
            d1Count++;
    }
    // 紀錄 d1 最小的人的編號
    int* d1Same = new int [d1Count];
    int d1SameIndex = 0;
    for (int i = 0; i < memberNumber; i++) 
    {
        if (d1Array[i] == d1Min) 
        {
            d1Same[d1SameIndex] = i + 1;
            d1SameIndex++;
        }
    }
    // for (int i = 0; i < d1Count; i++) {
    //     // cout << "d1Same: " << d1Same[i] << "\n";
    // }
    // cout << rMember << "\n";
    

    if (d1Count >= 2) 
    {
        int d2Min = MAX_d2_MIN;
        for (int i = 0; i < d1Count; i++)
        {
            int d2 = 0, rIndex = 0, pIndex = 0;
            for (int j = 0; j < movieNumber; j++) 
            {
                if (j == movieLists[d1Same[i] - 1][rIndex] - 1 && j != movieLists[designatedMember - 1][pIndex] - 1)
                {
                    // cout << "1j: " << j << movieLists[d1Same[i] - 1][rIndex] - 1 << movieLists[designatedMember - 1][pIndex] - 1 << "\n";
                    d2++;
                    if (rIndex != movieListSizes[d1Same[i] - 1] - 1)
                        rIndex++;
                }
                if (j != movieLists[d1Same[i] - 1][rIndex] - 1 && j == movieLists[designatedMember - 1][pIndex] - 1)
                {
                    // cout << "p index1 : "<< pIndex << "\n";
                    // cout << "2j: " << j << movieLists[d1Same[i] - 1][rIndex] - 1 << movieLists[designatedMember - 1][pIndex] - 1 << "\n";
                    d2++;
                    if (pIndex != movieListSizes[designatedMember - 1] - 1)
                        pIndex++;
                    // cout << "p index2 : "<< pIndex << "\n";
                }
                if (j == movieLists[d1Same[i] - 1][rIndex] - 1 && j == movieLists[designatedMember - 1][pIndex] - 1)
                {
                    // cout << "3j: " << j << movieLists[d1Same[i] - 1][rIndex] - 1 << movieLists[designatedMember - 1][pIndex] - 1 << "\n";
                    if (rIndex != movieListSizes[d1Same[i] - 1] - 1)
                        rIndex++;
                    if (pIndex != movieListSizes[designatedMember - 1] - 1)
                        pIndex++;
                }
            }
            // cout << i << " time: d2 =  " << d2 << "\n";
            // cout << i << " time: d2Min = " << d2Min << "\n";
            if (d2Min > d2) 
            {
                d2Min = d2;
                rMember = d1Same[i];
            }
        }
    // cout << d2Min << "\n";
    }
    // cout << rMember << "\n";

    // 會員 p 和會員 r 看過的電影比較算分數，從會員 r 看過但會員 p 沒看過的電影中找會員 r 評分最高的電影
    int recommendedMovie = 0, tempScore = 0, rIndex = 0, pIndex = 0;
    for (int i = 0; i < movieNumber; i++) 
    {
        if (i != movieLists[rMember - 1][rIndex] - 1 && i == movieLists[designatedMember - 1][pIndex] - 1) 
        {
            if (pIndex != movieListSizes[designatedMember - 1] - 1)
                pIndex++;
        }
        if (i == movieLists[rMember - 1][rIndex] - 1 && i != movieLists[designatedMember - 1][pIndex] - 1) 
        {
            if (tempScore < scoreLists[rMember - 1][rIndex]) 
            {
                tempScore = scoreLists[rMember - 1][rIndex];
                recommendedMovie = i + 1;
            }
            if (rIndex != movieListSizes[rMember - 1] - 1)
                rIndex++;
        }
        if (i == movieLists[rMember - 1][rIndex] - 1 && i == movieLists[designatedMember - 1][pIndex] - 1) 
        {
            if (rIndex != movieListSizes[rMember - 1] - 1)
                rIndex++;
            if (pIndex != movieListSizes[designatedMember - 1] - 1)
                pIndex++;
        }
    }
    // cout << recommendedMovie << "\n";

    bool checkOldAlgorithm = 0;
    if (recommendedMovie == 0) {
        int answerArray [3] = {0};
        baseNTUFlix(memberNumber, movieNumber, designatedMember, const_cast<const int*>(movieListSizes), const_cast<const int**>(movieLists), const_cast<const int**>(scoreLists), answerArray);
        checkOldAlgorithm = 1;
        cout << answerArray[0] << "," << answerArray[1] << "," << answerArray[2] << "\n";
    }

    int totalScore = 0, scoreCount = 0;
    for (int i = 0; i < memberNumber; i++) 
    {
        for (int j = 0; j < movieListSizes[i]; j++) 
        {
            if (movieLists[i][j] == recommendedMovie) {
                scoreCount++;
                totalScore += scoreLists[i][j];
            }
        }
    }

    if (checkOldAlgorithm == 0) 
        cout << recommendedMovie << "," << scoreCount << "," << totalScore << "\n";
    
    for (int i = 0; i < movieListSizes[i]; i++)
    {
        delete[] movieLists[i];
        movieLists[i] = nullptr;
        delete[] scoreLists[i];
        scoreLists[i] = nullptr;
    }
    delete [] movieListSizes;
    movieListSizes = nullptr;
    delete [] movieLists;
    movieLists = nullptr;
    delete [] scoreLists;
    scoreLists = nullptr;
    delete [] d1Array;
    d1Array = nullptr;
    delete [] d1Same;
    d1Same = nullptr;
}



void baseNTUFlix(int& memberNumber, int& movieNumber, int& designatedMember, const int* movieListSizes, const int** movieLists, const int** scoreLists, int answerArray [])
{
    // 創建一個一維 boolean 陣列來判斷目標會員編號哪些電影沒看過，先初始化為 1，之後下面實作：沒看過更改為 0
    int targetMovieNumber = movieListSizes[designatedMember - 1];
    bool* found = new bool [movieNumber];
    for (int i = 0; i < movieNumber; i++)
        found[i] = 1;

    findUnwatchedMovies(movieNumber, designatedMember, movieListSizes, movieLists, found);
    recommendMovie(memberNumber, movieNumber, movieListSizes, movieLists, scoreLists, answerArray, found);

    delete [] found;
    found = nullptr;
}

void findUnwatchedMovies(int& movieNumber, int& designatedMember, const int* movieListSizes, const int** movieLists, bool* found)
{
    int indexFound = 0, indexMovieLists = 0;
    // 用 while 迴圈加上兩根指針來找哪些是沒看過的電影： indexFound -> check found array, index2 -> check movie lists
    int temp = movieNumber;
    while (temp > 0)
    {
        // 這裡是當 indexMovieLists 已經走完看過的所有電影，那後面的 Found[indexFound] 就全部都是 0
        if (indexMovieLists >= movieListSizes[designatedMember - 1])
        {
            found[indexFound] = 0;
            indexFound++;
        }
        // 編號一樣即是有看過 ex. 1 = 1, 2 = 2, ...以此類推
        else if ((indexFound + 1) == movieLists[designatedMember - 1][indexMovieLists])  
        {
            indexFound++;
            indexMovieLists++;
        }
        // 編號不一樣即找到沒看過的電影 ex. 5 = 6，則第 5 部電影為沒看過的電影
        else
        {
            found[indexFound] = 0;
            indexFound++;
        }
        temp--;
    }
}

void recommendMovie(int& memberNumber, int& movieNumber, const int* movieListSizes, const int** movieLists, const int** scoreLists, int answerArray [], bool* found)
{
    // 這邊來計算沒看過的電影總分及觀看次數
    int recommendedMovie = 0, recommendedMovieCount = 0, recommendedMovieScore = 0;
    for (int i = 0; i < movieNumber; i++)
    {
        int score = 0, count = 0;
        if (found[i] == 0)  // i = 4
        {
            for (int j = 0; j < memberNumber; j++)
            {
                for (int k = 0; k < movieListSizes[j]; k++)
                {
                    if (movieLists[j][k] == i + 1)  // 找 5
                    {
                        score += scoreLists[j][k];
                        count++;
                    }
                }
            }
            if (recommendedMovieScore < score)
            {
                recommendedMovie = i + 1;
                recommendedMovieCount = count;
                recommendedMovieScore = score;
            }
            if (recommendedMovieScore == score && recommendedMovieCount < count)
            {
                recommendedMovie = i + 1;
                recommendedMovieCount = count;
                recommendedMovieScore = score;
            }
        }
    }
    // 若沒看過的電影全都沒有其他人看過，則回傳沒看過的電影中，編號最小的那個
    if (recommendedMovieCount == 0 && recommendedMovieScore == 0)
    {
        for (int i = 0; i < movieNumber; i++)
        {
            if (found[i] == 0)
            {
                recommendedMovie = i + 1;
                break;
            }
        }
    }
    answerArray [0] = recommendedMovie;
    answerArray [1] = recommendedMovieCount;
    answerArray [2] = recommendedMovieScore;
}
