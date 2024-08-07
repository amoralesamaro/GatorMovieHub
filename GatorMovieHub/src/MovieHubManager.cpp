#include "MovieHubManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>

// Merge function for merge sort
void MovieHubManager::merge(vector<Movie> &movies, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Movie> L(n1);
    vector<Movie> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = movies[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = movies[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].weighted_rating > R[j].weighted_rating) // Sort in descending order of weighted_rating
        {
            movies[k] = L[i];
            i++;
        }
        else
        {
            movies[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        movies[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        movies[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function to sort movies by weighted_rating
void MovieHubManager::mergeSort(vector<Movie> &movies, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(movies, left, mid);
        mergeSort(movies, mid + 1, right);

        merge(movies, left, mid, right);
    }
}

// Method to insert a movie into the hash table
void MovieHubManager::insert(const Movie &movie)
{
    table.insert(movie.id, movie);
}

// Method to search for a movie by its ID
bool MovieHubManager::search(int id, Movie &movie)
{
    return table.search(id, movie);
}

// Method to update a movie's rating
void MovieHubManager::updateRating(int id, double rating)
{
    Movie movie;
    if (table.search(id, movie))
    {
        movie.rating = (movie.rating * movie.rating_count + rating) / (movie.rating_count + 1);
        movie.rating_count++;
        table.insert(id, movie); // Re-insert movie with updated rating
    }
}

// Method to finalize ratings and calculate weighted ratings
void MovieHubManager::finalizeRatings()
{
    double sum_ratings = 0;
    int total_ratings = 0;
    vector<Movie> movies = table.getAllElements();

    // Calculate the mean rating across all movies
    for (const auto &movie : movies)
    {
        sum_ratings += movie.rating * movie.rating_count;
        total_ratings += movie.rating_count;
    }
    double C = total_ratings > 0 ? sum_ratings / total_ratings : 0; // Avoid division by zero

    const int m = 50;

    // Clear the previous sorted_movies list before populating
    sorted_movies.clear();

    for (auto &movie : movies)
    {
        double weighted_rating = ((double)movie.rating_count / (movie.rating_count + m)) * movie.rating +
                                 ((double)m / (movie.rating_count + m)) * C;
        movie.weighted_rating = weighted_rating; // Update the movie's weighted rating
        sorted_movies.push_back(movie);
    }

    // Perform merge sort on sorted_movies
    mergeSort(sorted_movies, 0, sorted_movies.size() - 1);
}

// Method to display all movies in the hash table
void MovieHubManager::display()
{
    vector<Movie> movies = table.getAllElements();
    for (const auto &movie : movies)
    {
        cout << "ID: " << movie.id << ", Title: " << movie.title
             << ", Genres: " << movie.genres
             << ", Rating: " << movie.rating
             << ", Ratings Count: " << movie.rating_count << endl;
    }
}

// Method to display top-rated movies
void MovieHubManager::displayTopRated(int n)
{
    for (int i = 0; i < n && i < sorted_movies.size(); ++i)
    {
        cout << "ID: " << sorted_movies[i].id << ", Title: " << sorted_movies[i].title
             << ", Genres: " << sorted_movies[i].genres
             << ", Rating: " << sorted_movies[i].rating
             << ", Ratings Count: " << sorted_movies[i].rating_count << endl;
    }
}

void MovieHubManager::displayTopRatedByGenres(string genre, int n) // Added new method 
{
    // List of valid genres
    vector<string> validGenres = { "Unknown", "Action", "Adventure", "Animation", "Children's", "Comedy", "Crime", "Documentary", "Drama", "Fantasy", "Film-Noir", "Horror", "Musical", "Mystery", "Romance", "Sci-Fi", "Thriller", "War", "Western" };

    // Capitalize genre input
    genre = capitalize(genre); // Capitalize user input genre

    // Check if genre is valid
    if (!isValidGenre(genre, validGenres)) // Check if genre is valid 
    {
        cout << "Invalid genre: " << genre << endl;
        return; // Exit if genre is not valid
    }

    vector<Movie> topByGenre;
    for (const auto& movie : sorted_movies)
    {
        if (movie.genres.find(genre) != string::npos)
        {
            topByGenre.push_back(movie);
            if (topByGenre.size() == n)
                break;
        }
    }

    if (topByGenre.empty())
    {
        cout << "No movies found for the genre: " << genre << endl; // Display error if no movies found ***
    }
    else
    {
        for (const auto& movie : topByGenre)
        {
            cout << "ID: " << movie.id << ", Title: " << movie.title
                << ", Genres: " << movie.genres
                << ", Rating: " << movie.rating
                << ", Ratings Count: " << movie.rating_count << endl;
        }
    }
}

// New method to check if a movie exists by title
bool MovieHubManager::movieExists(const string &title) const
{
    vector<Movie> movies = table.getAllElements();
    for (const auto &movie : movies)
    {
        if (movie.title == title)
        {
            return true;
        }
    }
    return false;
}

// Helper function to capitalize the first letter of each word in a string
string capitalize(const string &str)
{
    stringstream ss(str);
    string word, result;
    while (ss >> word)
    {
        word[0] = toupper(word[0]);
        for (size_t i = 1; i < word.length(); ++i)
        {
            word[i] = tolower(word[i]);
        }
        if (!result.empty())
        {
            result += " ";
        }
        result += word;
    }
    return result;
}

// Helper function to check if a genre is valid
bool isValidGenre(const string &genre, const vector<string> &validGenres)
{
    return find(validGenres.begin(), validGenres.end(), genre) != validGenres.end();
}

// Function to load movies from a file and insert them into the hash table
void loadMovies(MovieHubManager &hashTable, const string &filename)
{
    ifstream file(filename); // Open the file

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return; // Exit the function if file cannot be opened
    }

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
        try
        {
            movie.id = stoi(token);
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid movie ID in file: " << token << endl;
            continue;
        }

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
void loadRatings(MovieHubManager &hashTable, const string &filename)
{
    ifstream file(filename); // Open the file

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return; // Exit the function if file cannot be opened
    }

    string line;

    // Read the file line by line
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;

        int user_id, item_id, rating;

        // Read the user ID
        getline(ss, token, '\t');
        try
        {
            user_id = stoi(token);
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid user ID in file: " << token << endl;
            continue;
        }

        // Read the item (movie) ID
        getline(ss, token, '\t');
        try
        {
            item_id = stoi(token);
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid movie ID in file: " << token << endl;
            continue;
        }

        // Read the rating
        getline(ss, token, '\t');
        try
        {
            rating = stoi(token);
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid rating in file: " << token << endl;
            continue;
        }

        // Update the movie's rating in the hash table
        hashTable.updateRating(item_id, rating);
    }
}

// Method to get movie input from the user
bool MovieHubManager::getMovieInput(Movie &newMovie)
{
    string title, genres, genre;
    double rating;

    while (true)
    {
        // Get movie title and capitalize it
        cout << "Enter movie title: ";
        getline(cin, title);
        title = capitalize(title);

        if (movieExists(title))
        {
            cout << "Movie already exists." << endl
                 << endl;
            return false; // Exit the loop and function if the movie exists
        }

        // Validate genres input
        bool isValidGenres = true;
        while (isValidGenres)
        {
            cout << "Enter movie genres (comma-separated): ";
            getline(cin, genres);
            stringstream genreStream(genres);
            vector<string> genreList;
            vector<string> validGenres = {"Action", "Adventure", "Animation", "Children's", "Comedy", "Crime", "Documentary", "Drama", "Fantasy", "Film-Noir", "Horror", "Musical", "Mystery", "Romance", "Sci-Fi", "Thriller", "War", "Western"};
            bool validGenresFlag = true;
            while (getline(genreStream, genre, ','))
            {
                genre = capitalize(genre);
                if (!isValidGenre(genre, validGenres))
                {
                    cout << "Invalid genre: " << genre << endl;
                    validGenresFlag = false;
                }
                genreList.push_back(genre);
            }
            if (!validGenresFlag)
            {
                cout << "Please re-enter the genres (e.g., Action, Drama, Comedy)." << endl
                     << endl;
                continue;
            }

            genres = accumulate(next(genreList.begin()), genreList.end(), genreList[0], [](const string &a, const string &b)
                                { return a + ", " + b; });

            isValidGenres = false;
        }

        // Validate rating input
        bool isValidRating = true;
        while (isValidRating)
        {
            cout << "Enter initial rating (1 to 5): ";
            cin >> rating;
            if (rating < 1 || rating > 5)
            {
                cout << "Invalid rating. Please enter a value between 1 and 5." << endl
                     << endl;
                cin.ignore();
                continue;
            }

            isValidRating = false;
        }

        cin.ignore();

        newMovie.title = title;
        newMovie.genres = genres;
        newMovie.rating = rating;
        newMovie.rating_count = 1;

        return true;
    }
}

// Method to add a new movie
bool MovieHubManager::addMovie(Movie &movie, const string &filename, const string &ratingFile)
{
    movie.id = getNextID(); // Automatically assign the next available ID

    // Add movie to hash table
    insert(movie);

    // Append movie details to the movie file
    ofstream movieFile(filename, ios::app);
    if (movieFile.is_open())
    {
        // Format: MovieID|Title|ReleaseDate|VideoReleaseDate|IMDbURL|genre1|genre2|...|genre19
        // Use "N/A" for ReleaseDate and VideoReleaseDate, and a placeholder for IMDbURL
        string releaseDate = "N/A";
        string videoReleaseDate = "N/A";
        string imdbURL = "http://us.imdb.com/M/title-exact?";

        movieFile << movie.id << "|" << movie.title << "|" << releaseDate << "|" << videoReleaseDate << "|" << imdbURL << "|";

        vector<string> genreNames = {"Unknown", "Action", "Adventure", "Animation", "Children's", "Comedy", "Crime", "Documentary", "Drama", "Fantasy", "Film-Noir", "Horror", "Musical", "Mystery", "Romance", "Sci-Fi", "Thriller", "War", "Western"};

        // Write genres to the file
        for (const auto &genreName : genreNames)
        {
            if (movie.genres.find(genreName) != string::npos)
            {
                movieFile << "1|";
            }
            else
            {
                movieFile << "0|";
            }
        }

        movieFile << endl;
        movieFile.close();
    }
    else
    {
        return false; // Failed to open movie file
    }

    // Append initial rating to the rating file
    ofstream ratingFileStream(ratingFile, ios::app);
    if (ratingFileStream.is_open())
    {
        ratingFileStream << "0\t" << movie.id << "\t" << movie.rating << "\t0" << endl; // user_id 0 as placeholder
        ratingFileStream.close();
    }
    else
    {
        return false; // Failed to open rating file
    }

    return true; // Movie successfully added
}

// Method to get the next available ID
int MovieHubManager::getNextID()
{
    int max_id = 0;
    for (const auto &movie : table.getAllElements())
    {
        if (movie.id > max_id)
        {
            max_id = movie.id;
        }
    }
    return max_id + 1;
}
