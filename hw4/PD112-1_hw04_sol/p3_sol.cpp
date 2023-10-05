#include <iostream>
using namespace std;

void recommendMovie(int memberCnt, int movieCnt, int memberId, int* movieListSizes, int** movieLists, int** scoreLists, int ret[]);

int main() {
    int memberCnt = 0, movieCnt = 0, memberId = 0;
    cin >> memberCnt >> movieCnt >> memberId;

    int* movieListSizes = new int[memberCnt];
    int** movieLists = new int*[memberCnt];
    int** scoreLists = new int*[memberCnt];

    int ret[3] = {0}; // movie no, score count, score sum

    for(int i = 0; i < memberCnt; i++) {
        cin >> movieListSizes[i];
        movieLists[i] = new int[movieListSizes[i]];
        scoreLists[i] = new int[movieListSizes[i]];

        for(int j = 0; j < movieListSizes[i]; j++)
            cin >> movieLists[i][j] >> scoreLists[i][j];
    }

    recommendMovie(memberCnt, movieCnt, memberId, movieListSizes, movieLists, scoreLists, ret);
    cout << ret[0] << "," << ret[1] << "," << ret[2];
    
    // delete statement
    for(int i = 0; i < memberCnt; i++) {
        delete[] movieLists[i];
        delete[] scoreLists[i];
        movieLists[i] = nullptr;
        scoreLists[i] = nullptr;
    }
    delete[] movieLists;
    delete[] scoreLists;
    delete[] movieListSizes;
    movieLists = nullptr;
    scoreLists = nullptr;
    movieListSizes = nullptr;
    return 0;
}

// recommend movie by finding a movie with the highest score sum
// if there are more than one movie, recommend the one with more score count
// if there are still more than one movie, recommend the one with smallest id
void recommendMovie(int memberCnt, int movieCnt, int memberId, int* movieListSizes, int** movieLists, int** scoreLists, int ret[]) {
    int** score = new int*[2];
    score[0] = new int[movieCnt];
    score[1] = new int[movieCnt];
    // initialization
    for (int i = 0; i < movieCnt; i++) {
        score[0][i] = 0; // movie i's score count
        score[1][i] = 0; // movie i's score sum
    }

    // exclude movies the member p watched
    for(int i = 0; i < movieListSizes[memberId - 1]; i++) {
        int watchedMovie = movieLists[memberId - 1][i];
        score[0][watchedMovie - 1] = -1;
        score[1][watchedMovie - 1] = -1;
    }

    // calculate all movies' score count & score sum
    for(int i = 0; i < memberCnt; i++) {
        if(i + 1 == memberId) 
            continue;
        else {
            for(int j = 0; j < movieListSizes[i]; j++) {
                int targetMovie = movieLists[i][j];
                if(score[0][targetMovie - 1] != -1) { // member p hasn't watched
                    score[0][targetMovie - 1]++;
                    score[1][targetMovie - 1] += scoreLists[i][j];
                }
                else continue;
            }
        }
    }

    // find the movie to recommend
    // ret[3]: movie no, score count, score sum
    ret[2] = -1;
    for(int i = 0; i < movieCnt; i++) {
        if (score[1][i] > ret[2] || (score[1][i] == ret[2] && score[0][i] > ret[1])) {
            ret[0] = i + 1;
            ret[1] = score[0][i];
            ret[2] = score[1][i]; 
        }
    }
    
    // delete statement
    delete[] score[0];
    delete[] score[1];
    score[0] = score[1] = nullptr;
    delete[] score;
    score = nullptr;
}