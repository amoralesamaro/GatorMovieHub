#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include "MovieHubManager.h"
#include <fstream>

using namespace std;

// Display available commands to the user
void showCommands()
{
    cout << "Available commands:" << endl;
    cout << "  display_all      - Display all movies" << endl;
    cout << "  top_rated <n>    - Display top n rated movies" << endl;
    cout << "  recommend_movie  - Recommend movie based on genre" << endl;
    cout << "  search <id>      - Search for a movie by ID" << endl;
    cout << "  add_movie        - Add a new movie" << endl;
    cout << "  exit             - Exit the program" << endl
         << endl;
}

int main(int argc, char *argv[])
{
    string filename = "ml-100k/u.item";    // File containing movie information
    string ratingsFile = "ml-100k/u.data"; // File containing movie ratings

    MovieHubManager hashTable;           // Manager for movie hash table
    loadMovies(hashTable, filename);     // Load movies into hash table
    loadRatings(hashTable, ratingsFile); // Load ratings into hash table

    hashTable.finalizeRatings(); // Finalize and sort movie ratings

    string command;
    while (true)
    {
        showCommands(); // Display available commands
        cout << "Enter command: ";
        getline(cin, command);
        stringstream ss(command);
        string cmd;
        ss >> cmd;

        if (cmd == "display_all")
        {
            hashTable.display(); // Display all movies
            cout << endl;
        }
        else if (cmd == "top_rated")
        {
            int n;
            if (ss >> n)
            {
                if (n <= 0) // Moved this condition inside the block
                {
                    cout << "Please enter a value greater than 0\n"
                        << endl;
                continue;
            }
            hashTable.displayTopRated(n); // Display top n rated movies
            cout << endl;
        }
        else
        {
            cout << "Missing number of movie recommendations. Usage: top_rated <n>\n"
            << endl;
        }
        else if (cmd == "recommend_movie")
        {
            string genre;
            cout << "What genre? ";
            getline(cin, genre);

            // Prompt for number of recommendations
            int movieNum;
            cout << "How many movies would you like recommended? ";
            cin >> movieNum;

            hashTable.displayTopRatedByGenres(genre, movieNum); // Recommend n movies in the genre
            cout << endl;
        }
        else if (cmd == "search")
        {
            int id;
            if (ss >> id)
            {
                Movie movie;
                if (hashTable.search(id, movie))
                {
                    cout << "Found movie: " << movie.title << ", Rating: " << movie.rating << endl; // Movie found
                }
                else
                {
                    cout << "Movie not found." << endl; // Movie not found
                }
                cout << endl;
            }
            else
            {
                cout << "Missing movie ID. Usage: search <id>\n"
                     << endl;
            }
        }
        else if (cmd == "add_movie")
        {
            Movie newMovie;
            if (hashTable.getMovieInput(newMovie)) // Get movie input from user
            {
                if (hashTable.addMovie(newMovie, filename, ratingsFile)) // Add movie to hash table
                {
                    cout << "Movie added: ID=" << newMovie.id << ", Title=" << newMovie.title << ", Genres=" << newMovie.genres << ", Rating: " << newMovie.rating << endl;
                }
                else
                {
                    cout << "Failed to add movie." << endl;
                }
                cout << endl;
            }
        }
        else if (cmd == "exit")
        {
            break; // Exit the program
        }
        else
        {
            cout << "Invalid command." << endl;
            cout << endl;
        }
    }

    return 0;
}

