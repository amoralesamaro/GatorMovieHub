//
// Created by Daniel Kim on 7/30/24.
//

#include "MovieHubManager.h"

void MovieHubManager::mergeSortMovieList(vector<Movie> movieList, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        sortMovieList(movieList, left, mid);
        sortMovieList(movieList, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void MovieHubManager::merge(vector<Movie>& movieList, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Movie> X(n1);
    vector<Movie> Y(n2);

    for (int i = 0; i < n1; i++)
    {
        X[i] = movieList[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        Y[j] = movieList[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (X[i] < Y[j])
        {
            movieList[k] = X[i];
            i++;
        }
        else
        {
            movieList[k] = Y[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        movieList[k] = X[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        moveList[k] = Y[j];
        j++;
        k++;
    }
}

int MovieHubManager::searchMovieHelper(vector<Movie> movies, int low, int high, int movieID)
{
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (movies[mid].id == movie) {
            return mid;
        }
        if (movies[mid].id < movieID) {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

vector<Movie> MovieHubManager::getMovieList(const MovieHashTable& table)
{

    for (Movie m: table) {
        movieList.push_back(m);
    }
    return movieList;

}

Movie MovieHubManager::getMovie(int movieID, const MovieHastTable& table)
{
    if (table.find(movieID) == table.end()) {
        return -1;
    }
    return table[movieID];
}

Movie MovieHubManager::searchMovie(int movieID)
{
    int low = 0;
    int high = movieList.size() - 1;
    int movieIDResult= searchMovieHelper(movieList, low, high, movieID);
    return movieList[movieIDResult];
}
