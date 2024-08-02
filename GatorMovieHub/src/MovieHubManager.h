//
// Created by Daniel Kim on 7/30/24.
//

#ifndef GATORMOVIEHUB_MOVIEHUBMANAGER_H
#define GATORMOVIEHUB_MOVIEHUBMANAGER_H
#include <Hash_table.h>

/***
 * Manages Movie objects such as sorting obtaining movies
 */
class MovieHubManager
{

private:
    /***
     * Container to hold the list of movies
     */
    vector<Movie> movieList;

    /***
     * Sorts the movie list by rating
     * @param movieList     the list of movies to be sorted
     */
    void mergeSortMovieList(vector<Movie> movieList, int left, int right);

    void merge(vector<Movie> movieList, int left, int mid, int right);

    Movie searchMovieHelper(vector<Movie> movies, int low, int high, int movieID);

public:
    MovieHubManager();
    /***
     * Retrieves the movie list as a vector from the movie HashTable
     * @param table     hashtable containing movies
     * @return          returns the list of movies as a vector list of Movies
     */
    vector<Movie> getMovieList(const MovieHashTable& table);

    /***
     * Retreives the movie that matches the given movie id
     * @param movieID   the movie id of the Movie to return
     * @return          returns the Movie with the given movie id
     */
    Movie getMovie(int movieID, const MovieHastTable& table);

    Movie searchMovie(int movieID);

};


#endif //GATORMOVIEHUB_MOVIEHUBMANAGER_H
