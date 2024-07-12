#include <iostream>
#include "Hash_table.h"

using namespace std;

int main()
{
    // Hard-coded path to the u.item file
    string movieFile = "ml-100k/u.item";
    string ratingsFile = "ml-100k/u.data";

    MovieHashTable hashTable;            // Create a hash table
    loadMovies(hashTable, movieFile);    // Load movies from the file into the hash table
    loadRatings(hashTable, ratingsFile); // Load ratings from the file

    hashTable.finalizeRatings(); // Finalize ratings

    cout << "Movies and ratings loaded successfully." << endl;

    return 0;
}
