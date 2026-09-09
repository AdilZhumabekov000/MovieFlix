# MovieFlix
C++ implementation and performance analysis of Quicksort pivot selection strategies

The program generates a dataset of movies with unique IDs and random ratings, sorts the movies by rating in descending order, and compares the execution time of different QuickSort strategies.

Features:

1. Generates random movie datasets with ratings from 1.0 to 10.0

2. Sorts movies by rating in descending order

3. Implements QuickSort using Hoare partitioning

4. Compares three pivot selection strategies:

5. First element pivot

6. Median-of-three pivot

7. Random pivot

8. Measures execution time in microseconds

9. Supports datasets of up to 1,000,000 movies

10. Allows users to view both generated and sorted data


How It Works:

The program implements QuickSort manually rather than using the built-in sorting function.

For each partition, one of three pivot strategies can be used. The same movie dataset can then be tested with each strategy to compare execution times.

The program menu allows the user to:

View the generated movie dataset

View movies sorted by rating

Compare QuickSort pivot strategies

Exit the program


Technologies:

C++

STL Vector

Random number generation

Hoare partitioning



Purpose:

This project was created to explore the QuickSort algorithm and compare how different pivot selection techniques can influence sorting performance.
