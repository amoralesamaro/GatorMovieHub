#include "Hash_table.h"
#include <fstream>
#include <sstream>

bool Movie::operator<(const Movie& other) const
{
    return weighted_rating < other.weighted_rating;
}

bool Movie::operator>(const Movie& other) const
{
    return weighted_rating > other.weighted_rating;
}

bool Movie::operator==(const Movie& other) const
{
    return weighted_rating == other.weighted_rating;
}

// Method to insert a movie into the hash table
void MovieHashTable::insert(const Movie &movie)
{
    table[movie.id] = movie;
}

// Method to update a movie's rating
void MovieHashTable::updateRating(int id, double rating)
{
    auto it = table.find(id);
    if (it != table.end())
    {
        Movie &movie = it->second;
        movie.rating = (movie.rating * movie.rating_count + rating) / (movie.rating_count + 1);
        movie.rating_count++;
    }
}

// Method to finalize the ratings
void MovieHashTable::finalizeRatings()
{
    for (auto &pair : table)
    {
        Movie &movie = pair.second;
        movie.weighted_rating = movie.rating;
    }
}

// Method to check if a movie exists in the hash table by ID
bool MovieHashTable::movieExists(int id) const
{
    return table.find(id) != table.end();
}

// Function to load movies from a file and insert them into the hash table
void loadMovies(MovieHashTable &hashTable, const string &filename)
{
    ifstream file(filename); // Open the file
    string line;

    // Define the genre names in the correct order
    vector<string> genreNames = {"Unknown", "Action", "Adventure", "Animation", "Children's", "Comedy", "Crime", "Documentary", "Drama", "Fantasy", "Film-Noir", "Horror", "Musical", "Mystery", "Romance", "Sci-Fi", "Thriller", "War", "Western"};

    // Read the file line by line
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        Movie movie;

        // Read the movie ID
        getline(ss, token, '|');
        movie.id = stoi(token);

        // Read the movie title
        getline(ss, movie.title, '|');

        // Skip release date, video release date, and IMDb URL
        getline(ss, token, '|'); // release date
        getline(ss, token, '|'); // video release date
        getline(ss, token, '|'); // IMDb URL

        // Read genres
        string genresList;
        for (int i = 0; i < genreNames.size(); ++i)
        {
            getline(ss, token, '|');
            if (token == "1")
            {
                if (!genresList.empty())
                {
                    genresList += ", ";
                }
                genresList += genreNames[i];
            }
        }
        movie.genres = genresList; // Assign genres to the movie

        // Insert the movie into the hash table
        hashTable.insert(movie);
    }
}

// Function to load ratings from a file and update the hash table
void loadRatings(MovieHashTable &hashTable, const string &filename)
{
    ifstream file(filename); // Open the file
    string line;

    // Read the file line by line
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;

        int user_id, item_id, rating;

        // Read the user ID
        getline(ss, token, '\t');
        user_id = stoi(token);

        // Read the item (movie) ID
        getline(ss, token, '\t');
        item_id = stoi(token);

        // Read the rating
        getline(ss, token, '\t');
        rating = stoi(token);

        // Update the movie's rating in the hash table
        hashTable.updateRating(item_id, rating);
    }
}
