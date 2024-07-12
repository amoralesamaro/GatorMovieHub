#pragma once

#include <iostream>
#include <unordered_map>
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

// Class to handle the hash table using std::unordered_map
class MovieHashTable
{
private:
    unordered_map<int, Movie> table; // Hash table to store movies

public:
    void insert(const Movie &movie);          // Method to insert a movie into the hash table
    void updateRating(int id, double rating); // Method to update a movie's rating
    void finalizeRatings();                   // Method to finalize the ratings
    bool movieExists(int id) const;           // Method to check if a movie exists by ID
};

// Function to load movies from a file and insert them into the hash table
void loadMovies(MovieHashTable &hashTable, const string &filename);
// Function to load ratings from a file and update the hash table
void loadRatings(MovieHashTable &hashTable, const string &filename);
