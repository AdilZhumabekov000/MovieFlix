#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

struct Movie
{
    string movieId;
    double rating;
};

enum PivotType
{
    FIRST_PIVOT,
    MEDIAN_PIVOT,
    RANDOM_PIVOT
};

random_device rd;
mt19937 rng(rd());

string generateMovieId(int value);
vector<Movie> createDataset(int size);

// References:
// Islam, Mostakim & Murad (2023) "A Study of Pivot Positioning Methods for Quicksort Algorithm"
// Kurosawa (2016) "Quicksort with Median of Medians Is Considered Practical"

double selectPivotValue(
    const vector<Movie>& data,
    int low,
    int high,
    PivotType strategy);

// References:
// Hoare (1962) "Quicksort"
// Fouz, Kufleitner, Manthey & Zeini Jahromi (2012) "On Smoothed Analysis of Quicksort and Hoare's Find"

int hoarePartition(
    vector<Movie>& data,
    int low,
    int high,
    PivotType strategy);

// Reference:
// Hoare (1962) "Quicksort"

void quickSort(
    vector<Movie>& data,
    int low,
    int high,
    PivotType strategy);

void quickSort(
    vector<Movie>& data,
    PivotType strategy);

long long measureExecutionTime(
    vector<Movie> data,
    PivotType strategy);

void printMovies(
    const vector<Movie>& data,
    int limit = 50);

void compareStrategies(
    const vector<Movie>& data);

string generateMovieId(int value)
{
    string id = to_string(value);

    while(id.length() < 7)
        id = "0" + id;

    return "MOV" + id;
}

vector<Movie> createDataset(int size)
{
    vector<Movie> movies;
    movies.reserve(size);

    uniform_real_distribution<double>
        ratingGenerator(1.0,10.0);

    for(int i=1;i<=size;i++)
    {
        Movie item;

        item.movieId =
            generateMovieId(i);

        item.rating =
            round(
                ratingGenerator(rng)
                *10.0)/10.0;

        movies.push_back(item);
    }

    shuffle(
        movies.begin(),
        movies.end(),
        rng);

    return movies;
}

double selectPivotValue(
    const vector<Movie>& data,
    int low,
    int high,
    PivotType strategy)
{
    if(strategy == FIRST_PIVOT)
        return data[low].rating;

    if(strategy == RANDOM_PIVOT)
    {
        uniform_int_distribution<int>
            randomIndex(low,high);

        return data[
            randomIndex(rng)
        ].rating;
    }

    int middle =
        low + (high-low)/2;

    double first =
        data[low].rating;

    double center =
        data[middle].rating;

    double last =
        data[high].rating;

    if((first<=center&&center<=last)||
       (last<=center&&center<=first))
        return center;

    if((center<=first&&first<=last)||
       (last<=first&&first<=center))
        return first;

    return last;
}

int hoarePartition(
    vector<Movie>& data,
    int low,
    int high,
    PivotType strategy)
{
    double pivot =
        selectPivotValue(
            data,
            low,
            high,
            strategy);

    int left = low - 1;
    int right = high + 1;

    while(true)
    {
        do
        {
            left++;
        }
        while(data[left].rating > pivot);

        do
        {
            right--;
        }
        while(data[right].rating < pivot);

        if(left >= right)
            return right;

        swap(
            data[left],
            data[right]);
    }
}
// Reference:
// Hoare (1962) "Quicksort"

void quickSort(
    vector<Movie>& data,
    int low,
    int high,
    PivotType strategy)
{
    if(low < high)
    {
        int splitPoint =
            hoarePartition(
                data,
                low,
                high,
                strategy);

        quickSort(
            data,
            low,
            splitPoint,
            strategy);

        quickSort(
            data,
            splitPoint + 1,
            high,
            strategy);
    }
}

// Reference:
// Hoare (1962) "Quicksort"

void quickSort(
    vector<Movie>& data,
    PivotType strategy)
{
    if(!data.empty())
    {
        quickSort(
            data,
            0,
            data.size()-1,
            strategy);
    }
}

long long measureExecutionTime(
    vector<Movie> data,
    PivotType strategy)
{
    auto start =
        high_resolution_clock::now();

    quickSort(
        data,
        strategy);

    auto finish =
        high_resolution_clock::now();

    return duration_cast<microseconds>
           (finish-start).count();
}

void printMovies(
    const vector<Movie>& data,
    int limit)
{
    cout << left
         << setw(15) << "Movie ID"
         << setw(10) << "Rating"
         << endl;

    cout << "------------------------\n";

    int rows =
        min((int)data.size(),
            limit);

    for(int i=0;i<rows;i++)
    {
        cout << left
             << setw(15)
             << data[i].movieId
             << fixed
             << setprecision(1)
             << data[i].rating
             << endl;
    }
}

void compareStrategies(
    const vector<Movie>& data)
{
    long long firstResult =
        measureExecutionTime(
            data,
            FIRST_PIVOT);

    long long medianResult =
        measureExecutionTime(
            data,
            MEDIAN_PIVOT);

    long long randomResult =
        measureExecutionTime(
            data,
            RANDOM_PIVOT);

    cout << "\nExecution Results\n\n";

    cout << left
         << setw(20) << "Strategy"
         << setw(15) << "Time (us)"
         << endl;

    cout << "---------------------------------\n";

    cout << setw(20)
         << "First Pivot"
         << firstResult
         << endl;

    cout << setw(20)
         << "Median Pivot"
         << medianResult
         << endl;

    cout << setw(20)
         << "Random Pivot"
         << randomResult
         << endl;
}

int main()
{
    int movieCount;

    cout << "Enter number of movies: ";
    cin >> movieCount;

    if(movieCount <= 0 ||
       movieCount > 1000000)
    {
        cout << "Invalid input\n";
        return 0;
    }

    vector<Movie> movies =
        createDataset(
            movieCount);

    vector<Movie> sortedMovies;

    int menuChoice;

    do
    {
        cout << "\n===== MovieFlix Menu =====\n";
        cout << "1. View Generated Data\n";
        cout << "2. View Sorted Data\n";
        cout << "3. Compare Pivot Strategies\n";
        cout << "4. Exit\n";
        cout << "Select: ";

        cin >> menuChoice;

        switch(menuChoice)
        {
            case 1:

                printMovies(
                    movies);

                break;

            case 2:

                sortedMovies =
                    movies;

                quickSort(
                    sortedMovies,
                    MEDIAN_PIVOT);

                printMovies(
                    sortedMovies);

                break;

            case 3:

                compareStrategies(
                    movies);

                break;

            case 4:

                cout << "Program closed\n";

                break;

            default:

                cout << "Invalid option\n";
        }

    }
    while(menuChoice != 4);

    return 0;
}
