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
    void sortMovieList(vector<Movie> movieList);

public:
    /***
     * Retrieves the movie list as a vector from the movie HashTable
     * @param table     hashtable containing movies
     * @return          returns the list of movies as a vector list of Movies
     */
    vector<Movie> getMovieList(MovieHashTable table);

    /***
     * Retreives the movie that matches the given movie id
     * @param movieID   the movie id of the Movie to return
     * @return          returns the Movie with the given movie id
     */
    Movie getMovie(int movieID);

};


#endif //GATORMOVIEHUB_MOVIEHUBMANAGER_H
