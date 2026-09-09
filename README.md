# MovieFlix
C++ implementation and performance analysis of Quicksort pivot selection strategies
Each movie contains a unique movie ID and a rating. The program automatically generates a dataset of movies with random ratings and then sorts the dataset in descending order.

How It Works

The program uses the QuickSort algorithm with Hoare's partitioning scheme.

Three different pivot selection strategies are implemented:

First Pivot — uses the first element of the current partition as the pivot.
Median-of-Three Pivot — selects the median value from the first, middle, and last elements.
Random Pivot — randomly selects an element from the current partition.

The program measures the execution time of each strategy in microseconds, allowing their performance to be compared on the same dataset.

Features
Generates random movie datasets
Creates unique movie IDs
Generates movie ratings between 1.0 and 10.0
Sorts movies by rating in descending order
Implements QuickSort manually
Uses Hoare partitioning
Supports three different pivot strategies
Measures execution time using std::chrono
Supports datasets of up to 1,000,000 movies
Displays generated and sorted movie data
Program Menu

The application provides the following options:

View Generated Data
Displays the original randomly generated movie dataset.
View Sorted Data
Sorts the movies by rating using the median-of-three pivot strategy and displays the result.
Compare Pivot Strategies
Runs QuickSort using all three pivot strategies and displays their execution times.
Exit
Closes the program.
Example

The program may display a comparison similar to:

Execution Results

Strategy            Time (us)
---------------------------------
First Pivot         850
Median Pivot        720
Random Pivot        760

Execution times will vary depending on the dataset and the computer running the program.

Technologies Used
C++
STL vector
<algorithm>
<random>
<chrono>
<iomanip>
Compile and Run

Using g++:

g++ main.cpp -o quicksort
./quicksort

After starting the program, enter the number of movies you want to generate and select an option from the menu.

Purpose

The purpose of this project is to demonstrate how different pivot selection strategies can affect the performance of the QuickSort algorithm while applying the algorithm to a simple movie-rating dataset.
