#pragma once

#include "HashTable.h"
#include <vector>
#include <string>

using namespace std;

// Define a struct to store movie details and ratings
struct Movie
{
    int id;                 // Movie ID
    string title;           // Movie title
    string genres;          // Movie genres
    double rating;          // Average rating of the movie
    int rating_count;       // Number of ratings received
    double weighted_rating; // Weighted rating of the movie

    // Constructor to initialize the Movie struct
    Movie() : id(0), rating(0.0), rating_count(0), weighted_rating(0.0) {}
};

// Class to handle the hash table using the custom HashTable
class MovieHubManager
{
private:
    HashTable<int, Movie> table; // Hash table to store movies
    vector<Movie> sorted_movies; // Vector to store sorted movies

    // Merge function for merge sort
    void merge(vector<Movie> &movies, int left, int mid, int right);

    // Merge sort function
    void mergeSort(vector<Movie> &movies, int left, int right);

public:
    MovieHubManager() {} // Default constructor

    void insert(const Movie &movie);                                               // Method to insert a movie into the hash table
    bool search(int id, Movie &movie);                                             // Method to search for a movie by its ID
    void updateRating(int id, double rating);                                      // Method to update a movie's rating
    void finalizeRatings();                                                        // Method to finalize the ratings and sort the movies
    void display();                                                                // Method to display all movies in the hash table
    void displayTopRated(int n);                                                   // Method to display top-rated movies
    void displayTopRatedByGenres(string genre, int n);                             // Method to display top-rated movies by genre
    bool movieExists(const string &title) const;                                   // Method to check if a movie exists by its title and genres
    bool addMovie(Movie &movie, const string &filename, const string &ratingFile); // Method to add a new movie
    bool getMovieInput(Movie &newMovie);                                           // Method to get movie input from the user
    int getNextID();                                                               // Method to get the next available ID
};

// Function to load movies from a file and insert them into the hash table
void loadMovies(MovieHubManager &hashTable, const string &filename);
// Function to load ratings from a file and update the hash table
void loadRatings(MovieHubManager &hashTable, const string &filename);

// Helper function to capitalize the first letter of each word in a string
string capitalize(const string &str);

// Helper function to check if a genre is valid
bool isValidGenre(const string &genre, const vector<string> &validGenres);
