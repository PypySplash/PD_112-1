#include <iostream>
using namespace std;

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
        movieLists[i] = new int [movieListSizes[i]];  // 動態記憶體配置二維陣列時，需記得 new column 的數量
        scoreLists[i] = new int [movieListSizes[i]];
        for (int j = 0; j < movieListSizes[i]; j++)
        {
            cin >> movieLists[i][j];
            cin >> scoreLists[i][j];
        }
    }

    int answerArray [3] = {0};

    baseNTUFlix(memberNumber, movieNumber, designatedMember, const_cast<const int*>(movieListSizes), const_cast<const int**>(movieLists), const_cast<const int**>(scoreLists), answerArray);

    cout << answerArray[0] << "," << answerArray[1] << "," << answerArray[2] << "\n";

    for (int i = 0; i < movieListSizes[i]; i++)
    {
        delete[] movieLists[i];
        delete[] scoreLists[i];
    }

    delete [] movieListSizes;
    movieListSizes = nullptr;
    delete [] movieLists;
    movieLists = nullptr;
    delete [] scoreLists;
    scoreLists = nullptr;

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
