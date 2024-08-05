MovieHubManager
This project implements a movie management system using a custom hash table. It allows users to display all movies, display top-rated movies, search for a movie by ID, and add new movies.

Table of Contents
•	Features
•	Installation
•	Usage
•	File Structure
•	Contributors

Features
•	Display All Movies: Lists all movies stored in the system.
•	Top Rated Movies: Displays the top N rated movies.
•	Search Movie by ID: Finds and displays movie details by its ID.
•	Add New Movie: Allows users to add a new movie with title, genres, and rating.

Installation
1.	Clone the repository:
git clone https://github.com/amorelesamaro/GatorMovieHub.git

2.	Navigate to the project directory:
cd GatorMovieHub

3.	Compile the code: Ensure you have a C++ compiler installed. Run the following command to compile the code:
g++ --std=c++14 -Werror -Wuninitialized -o main.out src/*.cpp

Usage
1.	Run the program:
./main.out

3.	Commands:
display_all :  Display all movies.
top_rated <n>: Display top N rated movies.
search <id>: Search for a movie by ID.
add_movie: Add a new movie.
exit: Exit the program.

File Structure
•	main.cpp: The main program file containing the command-line interface.
•	MovieHubManager.h: Header file for the MovieHubManager class.
•	MovieHubManager.cpp: Implementation file for the MovieHubManager class.
•	ml-100k/: Directory containing movie and ratings data files.

Contributors
•	Alexis Morales: Implemented the Hash Table and prepared the dataset, project leader, and integrated all components.
•	Daniel Kim: Implemented Merge Sort and analyzed performance.
•	Jeffrey Smith: Designed the command line interface and integrated components.
