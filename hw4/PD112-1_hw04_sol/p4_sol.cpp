#include <iostream>
#include <cmath>
using namespace std;

void findSimilarMember(int memberCnt, int movieCnt, int memberId, int* movieListSizes, int** movieLists, int** scoreLists, int ret[]);
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

    findSimilarMember(memberCnt, movieCnt, memberId, movieListSizes, movieLists, scoreLists, ret);
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



// recommend movie by finding the most similar member with the target member
// if the target member watched all the movies which the most similar member watched, use the algorithm of problem 3
void findSimilarMember(int memberCnt, int movieCnt, int memberId, int* movieListSizes, int** movieLists, int** scoreLists, int ret[]) {
    int minDistance = -1, minDistanceCnt = 0;
    int* minDistanceMember = new int[memberCnt];
    int similarMember = 0;

    // calculate d1
    for(int i = 0; i < memberCnt; i++) {
        if (i + 1 == memberId)
            continue;
        
        int distance = 0, index1 = 0, index2 = 0;  // index1 for member i, index 2 for member p
        
        while(index1 < movieListSizes[i] || index2 < movieListSizes[memberId - 1]) {
            if(index1 >= movieListSizes[i]) { // movies which member i watched have been tranversed
                distance += scoreLists[memberId - 1][index2];
                index2++;
            }
            else if(index2 >= movieListSizes[memberId - 1]) { // movies which member p watched have been tranversed
                distance += scoreLists[i][index1];
                index1++;
            }
            else if(movieLists[i][index1] < movieLists[memberId - 1][index2]) { // member p hasn't seen this movie
                distance += scoreLists[i][index1];
                index1++;
            }
            else if(movieLists[i][index1] == movieLists[memberId - 1][index2]) { // two members have watched the same movie
                distance += abs(scoreLists[i][index1] - scoreLists[memberId - 1][index2]);
                index1++;
                index2++;
            }
            else if(movieLists[i][index1] > movieLists[memberId - 1][index2]) { // member i hasn't seen this movie
                distance += scoreLists[memberId - 1][index2];
                index2++;
            }
        }
        if(minDistance == -1 || distance < minDistance) {
            minDistance = distance;
            minDistanceMember[0] = i + 1;
            minDistanceCnt = 1;
        }
        else if (distance == minDistance) {
            minDistanceMember[minDistanceCnt] = i + 1;
            minDistanceCnt ++;
        }
    }

    // calculate d2
    if (minDistanceCnt > 1) {
        int sameDistanceCnt = minDistanceCnt;
        minDistance = -1;
        minDistanceCnt = 0;

        for(int i = 0; i < sameDistanceCnt; i++) {
            int toCompare = minDistanceMember[i];
            int distance = 0, index1 = 0, index2 = 0; // index 1 for toCompare, index 2 for member p
            while(index1 < movieListSizes[toCompare - 1] || index2 < movieListSizes[memberId - 1]) {
                if(index1 >= movieListSizes[toCompare - 1])
                    index2++;
                else if(index2 >= movieListSizes[memberId - 1])
                    index1++;
                else if(movieLists[toCompare - 1][index1] < movieLists[memberId - 1][index2])
                    index1++;
                else if(movieLists[toCompare - 1][index1] == movieLists[memberId - 1][index2]) { // two members have watched the same movie -> distance doesn't increase
                    index1++;
                    index2++;
                    continue;
                }
                else if(movieLists[toCompare - 1][index1] > movieLists[memberId - 1][index2])
                    index2++;
                distance++; // distance increases when a movie is seen by only one member

            }
            if(minDistance == -1 || distance < minDistance) {
                minDistance = distance;
                similarMember = toCompare;
            }
        }
    }
    else
        similarMember = minDistanceMember[0];

    // exclude movies the member p watched
    int index1 = 0, index2 = 0; // index 1 for the most similar member, index 2 for member p
    while(index1 < movieListSizes[similarMember - 1] || index2 < movieListSizes[memberId - 1]) {
        if(index1 >= movieListSizes[similarMember - 1])
            index2++;
        else if(index2 >= movieListSizes[memberId - 1])
            index1++;
        else if(movieLists[similarMember - 1][index1] < movieLists[memberId - 1][index2])
            index1++;
        else if(movieLists[similarMember - 1][index1] == movieLists[memberId - 1][index2]) {
            scoreLists[similarMember - 1][index1] = -1;
            index1++;
            index2++;
        }
        else if(movieLists[similarMember - 1][index1] > movieLists[memberId - 1][index2])
            index2++;
    }

    // find the most similar member's favorite movie
    int movieId = -1, maxScore = 0;
    for(int i = 0; i < movieListSizes[similarMember - 1]; i++) {
        if(scoreLists[similarMember - 1][i] > maxScore) {
            maxScore = scoreLists[similarMember - 1][i];
            movieId = movieLists[similarMember - 1][i];
        }
    }

    if(movieId == -1) // use the algorithm of problem 3
        recommendMovie(memberCnt, movieCnt, memberId, movieListSizes, movieLists, scoreLists, ret);
    else {
        ret[0] = movieId;
        // calculate score count & score sum
        for(int i = 0; i < memberCnt; i++)
            if(i + 1 == memberId) 
                continue;
            else {
                for(int j = 0; j < movieListSizes[i]; j++) {
                    int targetMovie = movieLists[i][j];
                    if(targetMovie != movieId)
                        continue;
                    else {
                        ret[1]++;
                        ret[2] += scoreLists[i][j];
                    }
                }
            } 
    }

    // delete statement
    delete[] minDistanceMember;
    minDistanceMember = nullptr;
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