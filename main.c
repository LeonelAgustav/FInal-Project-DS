#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

#define ID_LENGTH 7
#define MAX_CHILDREN 200

char order[20];
char sortname[20];
char nameedit[100];
char idedit[7];
char edit[20];

struct Movie
{
    char name[100];
    char genre[50];
    int year;
    int rating;
    char url[200];
    char id[ID_LENGTH + 1];
};

struct TrieNode
{
    struct TrieNode *children[MAX_CHILDREN];
    int is_leaf;
    struct Movie *movie;
};

struct Trie
{
    struct TrieNode *root;
};

struct TrieNode *createNode()
{
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (newNode)
    {
        newNode->is_leaf = 0;
        newNode->movie = NULL;
        for (int i = 0; i < MAX_CHILDREN; i++)
        {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

void freeTrie(struct TrieNode *root)
{
    if (root == NULL)
        return;

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        freeTrie(root->children[i]);
    }

    free(root);
}

void insertTrie(struct Trie *trie, struct Movie *movie)
{
    struct TrieNode *currentNode = trie->root;
    for (int i = 0; movie->genre[i] != '\0'; i++)
    {
        int index = toupper(movie->genre[i]) - 'A';
        if (!currentNode->children[index])
        {
            currentNode->children[index] = createNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->is_leaf = 1;
    currentNode->movie = movie;
}

void searchByGenre();
void searchByName();
void searchByYear();
void searchByRating();
void search();
int main();
void sortorder(int *sortOrder);

void swapMovies(struct Movie *a, struct Movie *b)
{
    struct Movie temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortByMovieName(struct Movie movies[], int movieCount, int sortOrder)
{
    int swapped;
    for (int i = 0; i < movieCount - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < movieCount - i - 1; j++)
        {
            if ((sortOrder > 0 && strcmp(movies[j].name, movies[j + 1].name) > 0) ||
                (sortOrder < 0 && strcmp(movies[j].name, movies[j + 1].name) < 0))
            {
                swapMovies(&movies[j], &movies[j + 1]);
                swapped++;
            }
        }
        if (!swapped)
            break;
    }
}

void bubbleSortByMovieYear(struct Movie movies[], int movieCount, int sortOrder)
{
    for (int i = 0; i < movieCount - 1; i++)
    {
        int swapped = 0; // Reset swapped for each outer loop iteration
        for (int j = 0; j < movieCount - 1 - i; j++)
        {
            if ((sortOrder > 0 && movies[j].year < movies[j + 1].year) ||
                (sortOrder < 0 && movies[j].year > movies[j + 1].year))
            {
                swapMovies(&movies[j], &movies[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void bubbleSortByMovieRating(struct Movie movies[], int movieCount, int sortOrder)
{
    for (int i = 0; i < movieCount - 1; i++)
    {
        int swapped = 0; // Reset swapped for each outer loop iteration
        for (int j = 0; j < movieCount - 1 - i; j++)
        {
            if ((sortOrder > 0 && movies[j].rating < movies[j + 1].rating) ||
                (sortOrder < 0 && movies[j].rating > movies[j + 1].rating))
            {
                swapMovies(&movies[j], &movies[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void bubbleSortByMovieGenre(struct Movie movies[], int movieCount, int sortOrder)
{
    for (int i = 0; i < movieCount - 1; i++)
    {
        int swapped = 0; // Reset swapped for each outer loop iteration
        for (int j = 0; j < movieCount - 1 - i; j++)
        {
            if ((sortOrder > 0 && strcmp(movies[j].genre, movies[j + 1].genre) > 0) ||
                (sortOrder < 0 && strcmp(movies[j].genre, movies[j + 1].genre) < 0))
            {
                swapMovies(&movies[j], &movies[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void printSortedMovieList(struct Movie movies[], int movieCount)
{
    system("cls");
    printf("|==============================================================|\n");
    printf("|--------------------- Sorted Movie List ----------------------|\n");
    printf("|--------------------- by %-6s %-10s -------------------|\n", sortname, order);
    printf("|==============================================================|\n");
    for (int i = 0; i < movieCount; i++)
    {
        printf("|%-8s | %-50s |\n", "Name", movies[i].name);
        printf("|%-8s | %-50s |\n", "Genre", movies[i].genre);
        printf("|%-8s | %-50d |\n", "Released", movies[i].year);
        printf("|%-8s | %-50d |\n", "Rating", movies[i].rating);
        printf("|%-8s | %-50s |\n", "URL", movies[i].url);
        printf("|%-8s | %-50s |\n", "Id", movies[i].id);
        printf("|==============================================================|\n");
    }
    printf("|%-8s = %-48d |\n", "Total Film", movieCount);
    printf("|==============================================================|\n");
    printf("Press enter to continue...");
    getch();
}

void printMovieList(struct Movie movies[], int movieCount)
{
    for (int i = 0; i < movieCount; i++)
    {
        printf("|%-8s | %-50s |\n", "Name", movies[i].name);
        printf("|%-8s | %-50s |\n", "Genre", movies[i].genre);
        printf("|%-8s | %-50d |\n", "Released", movies[i].year);
        printf("|%-8s | %-50d |\n", "Rating", movies[i].rating);
        printf("|%-8s | %-50s |\n", "URL", movies[i].url);
        printf("|%-8s | %-50s |\n", "Id", movies[i].id);
        printf("|==============================================================|\n");
    }
}

void sortorder(int *sortOrder)
{
    system("cls");
    char sortChoice = 0;

    while (1)
    {
        printf("|=====================|\n");
        printf("|--Choose sort order--|\n");
        printf("|=====================|\n");
        printf("| A | %-15s |\n", "Ascending");
        printf("| B | %-15s |\n", "Descending");
        printf("|=====================|\n");
        printf(">>> ");
        scanf(" %c", &sortChoice);

        if (sortChoice == 'A' || sortChoice == 'a')
        {
            *sortOrder = 1;
            strcpy(order, "Ascending");
            break;
        }
        else if (sortChoice == 'B' || sortChoice == 'b')
        {
            *sortOrder = -1;
            strcpy(order, "Descending");
            break;
        }
        else
        {
            printf("Invalid choice. Please choose 'A' for Ascending or 'B' for Descending.\n");
        }
    }
}

void sortviewmovie(struct Movie movies[], int movieCount)
{
    int sortBy = 0;
    int sortOrder = 0;
    int continueSorting = 1;

    do
    {
        system("cls");

        printf("|=============================|\n");
        printf("|---------Choose Sort---------|\n");
        printf("|=============================|\n");
        printf("| 1 | %-23s |\n", "Sort By Name");
        printf("| 2 | %-23s |\n", "Sort By Genre");
        printf("| 3 | %-23s |\n", "Sort By Year Released");
        printf("| 4 | %-23s |\n", "Sort By Rating");
        printf("| 5 | %-23s |\n", "Back");
        printf("|=============================|\n");
        printf(">> ");

        while (getchar() != '\n')
            ;

        if (scanf("%d", &sortBy) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            getch();
            sortBy = 0;
        }

        if (sortBy == 1)
        {
            sortorder(&sortOrder);
            bubbleSortByMovieName(movies, movieCount, sortOrder);
            system("cls");
            printf("|==============================================================|\n");
            printf("|--------------------------Movie List--------------------------|\n");
            printf("|------------------ Sorted by Name %-10s -----------------|\n", order);
            printf("|==============================================================|\n");
            printMovieList(movies, movieCount);
            printf("|%-8s = %-48d |\n", "Total Film", movieCount);
            printf("|==============================================================|\n");
            printf("\nPress enter to continue...");
            getch();
            break;
        }
        else if (sortBy == 2)
        {
            sortorder(&sortOrder);
            bubbleSortByMovieGenre(movies, movieCount, sortOrder);
            system("cls");
            printf("|==============================================================|\n");
            printf("|--------------------------Movie List--------------------------|\n");
            printf("|----------------- Sorted by Genre %-10s -----------------|\n", order);
            printf("|==============================================================|\n");
            printMovieList(movies, movieCount);
            printf("|%-8s = %-48d |\n", "Total Film", movieCount);
            printf("|==============================================================|\n");
            printf("\nPress enter to continue...");
            getch();
            break;
        }
        else if (sortBy == 3)
        {
            sortorder(&sortOrder);
            bubbleSortByMovieYear(movies, movieCount, sortOrder);
            system("cls");
            printf("|==============================================================|\n");
            printf("|--------------------------Movie List--------------------------|\n");
            printf("|------------- Sorted by Year Released %-10s -------------|\n", order);
            printf("|==============================================================|\n");
            printMovieList(movies, movieCount);
            printf("|%-8s = %-48d |\n", "Total Film", movieCount);
            printf("|==============================================================|\n");
            printf("\nPress enter to continue...");
            getch();
            break;
        }
        else if (sortBy == 4)
        {
            sortorder(&sortOrder);
            bubbleSortByMovieRating(movies, movieCount, sortOrder);
            system("cls");
            printf("|==============================================================|\n");
            printf("|--------------------------Movie List--------------------------|\n");
            printf("|----------------- Sorted by Rating %-10s ----------------|\n", order);
            printf("|==============================================================|\n");
            printMovieList(movies, movieCount);
            printf("|%-8s = %-48d |\n", "Total Film", movieCount);
            printf("|==============================================================|\n");
            printf("\nPress enter to continue...");
            getch();
            break;
        }
        else if (sortBy == 5)
        {
            continueSorting = 0; // Set the flag to exit the loop
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }

    } while (continueSorting);

    return;
}

void searchByName()
{
    system("cls");
    char name[100];
    struct Movie movies[MAX_CHILDREN];
    int movieCount = 0;
    int sortOrder = 0;
    int chooseSort;

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    do
    {
        printf("|=============================|\n");
        printf("|---------Choose Sort---------|\n");
        printf("|=============================|\n");
        printf("| 1 | %-23s |\n", "Sort By Genre");
        printf("| 2 | %-23s |\n", "Sort By Year Released");
        printf("| 3 | %-23s |\n", "Sort By Rating");
        printf("| 4 | %-23s |\n", "Not Sorted");
        printf("|=============================|\n");
        printf(">> ");
        scanf("%d", &chooseSort);
        system("cls");
    } while (chooseSort != 1 && chooseSort != 2 && chooseSort != 3 && chooseSort != 4);

    printf("Enter movie name: ");
    scanf(" %[^\n]s", name);

    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^,], %7[^\n]\n",
                  movies[movieCount].name, movies[movieCount].genre,
                  &movies[movieCount].year, &movies[movieCount].rating,
                  movies[movieCount].url, movies[movieCount].id) != EOF)
    {
        if (strncasecmp(movies[movieCount].name, name, strlen(name)) == 0)
        {
            movieCount++;
        }
    }
    fclose(file);

    if (chooseSort == 1)
    {
        strcpy(sortname, "Genre");
        sortorder(&sortOrder);
        bubbleSortByMovieGenre(movies, movieCount, sortOrder);
        system("cls");
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 2)
    {
        strcpy(sortname, "Year");
        sortorder(&sortOrder);
        bubbleSortByMovieYear(movies, movieCount, sortOrder);
        system("cls");
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 3)
    {
        strcpy(sortname, "Rating");
        sortorder(&sortOrder);
        bubbleSortByMovieRating(movies, movieCount, sortOrder);
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 4)
    {
        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");

        printMovieList(movies, movieCount);

        if (!movieCount)
        {
            printf("|                 No movie found with name %s.                 |\n", name);
        }
        else
        {
            printf("|%-8s = %-48d |\n", "Total Film", movieCount);
            printf("|==============================================================|\n");
        }

        char pick;
        do
        {
            printf("\nDo You Want to Search Again?[Y/N]: ");
            scanf(" %c", &pick);
        } while (pick != 'y' && pick != 'Y' && pick != 'n' && pick != 'N');

        if (pick == 'Y' || pick == 'y')
        {
            search();
        }
        else if (pick == 'N' || pick == 'n')
        {
            printf("\nPress enter to continue...");
            getch();
        }
    }
}

void searchByGenre()
{
    system("cls");
    char genre[50];
    struct Movie movies[MAX_CHILDREN];
    int movieCount = 0;
    int sortOrder = 0;
    int chooseSort;

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    do
    {
        printf("|=============================|\n");
        printf("|---------Choose Sort---------|\n");
        printf("|=============================|\n");
        printf("| 1 | %-23s |\n", "Sort By Name");
        printf("| 2 | %-23s |\n", "Sort By Year Released");
        printf("| 3 | %-23s |\n", "Sort By Rating");
        printf("| 4 | %-23s |\n", "Not Sorted");
        printf("|=============================|\n");
        printf(">> ");
        scanf("%d", &chooseSort);
        system("cls");
    } while (chooseSort != 1 && chooseSort != 2 && chooseSort != 3 && chooseSort != 4);

    printf("Enter genre prefix (Drama, Crime, Action, Adventure, Sci-Fi, Thriller, Mystery, Biography, Musical, Comedy, Romance, Horror, Family, Animation, War, Western, Film-Noir): ");
    scanf("%s", genre);

    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^,], %7[^\n]\n",
                  movies[movieCount].name, movies[movieCount].genre,
                  &movies[movieCount].year, &movies[movieCount].rating,
                  movies[movieCount].url, movies[movieCount].id) != EOF)
    {
        if (strncasecmp(movies[movieCount].genre, genre, strlen(genre)) == 0)
        {
            movieCount++;
        }
    }
    fclose(file);

    if (chooseSort == 1)
    {
        strcpy(sortname, "Name");
        sortorder(&sortOrder);
        bubbleSortByMovieName(movies, movieCount, sortOrder);
        system("cls");
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 2)
    {
        strcpy(sortname, "Year");
        sortorder(&sortOrder);
        bubbleSortByMovieYear(movies, movieCount, sortOrder);
        system("cls");
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 3)
    {
        strcpy(sortname, "Rating");
        sortorder(&sortOrder);
        bubbleSortByMovieRating(movies, movieCount, sortOrder);
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 4)
    {
        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");

        printMovieList(movies, movieCount);

        if (!movieCount)
        {
            printf("|               No movie found with genre %s.                 |\n", genre);
        }
        else
        {
            printf("|%-8s = %-48d |\n", "Total Film", movieCount);
            printf("|==============================================================|\n");
        }

        char pick;
        do
        {
            printf("\nDo You Want to Search Again?[Y/N]: ");
            scanf(" %c", &pick);
        } while (pick != 'y' && pick != 'Y' && pick != 'n' && pick != 'N');

        if (pick == 'Y' || pick == 'y')
        {
            search();
        }
        else if (pick == 'N' || pick == 'n')
        {
            printf("\nPress enter to continue...");
            getchar();
        }
    }
}

void searchByYear()
{
    system("cls");
    int year;
    struct Movie movies[MAX_CHILDREN];
    int movieCount = 0;
    int sortOrder = 0;
    int chooseSort;

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    do
    {
        printf("|=============================|\n");
        printf("|---------Choose Sort---------|\n");
        printf("|=============================|\n");
        printf("| 1 | %-23s |\n", "Sort By Name");
        printf("| 2 | %-23s |\n", "Sort By Genre");
        printf("| 3 | %-23s |\n", "Sort By Rating");
        printf("| 4 | %-23s |\n", "Not Sorted");
        printf("|=============================|\n");
        printf(">> ");
        scanf("%d", &chooseSort);
        system("cls");
    } while (chooseSort != 1 && chooseSort != 2 && chooseSort != 3 && chooseSort != 4);

    do
    {
        printf("Enter year of release (1900 to 2024): ");
        scanf("%d", &year);
    } while (year < 1900 || year > 2024);

    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^,], %7[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url, movies[movieCount].id) != EOF)
    {
        if (movies[movieCount].year == year)
        {
            movieCount++;
        }
    }
    fclose(file);

    if (chooseSort == 1)
    {
        strcpy(sortname, "Name");
        sortorder(&sortOrder);
        bubbleSortByMovieName(movies, movieCount, sortOrder);
        system("cls");
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 2)
    {
        strcpy(sortname, "Genre");
        sortorder(&sortOrder);
        bubbleSortByMovieGenre(movies, movieCount, sortOrder);
        system("cls");
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 3)
    {
        strcpy(sortname, "Rating");
        sortorder(&sortOrder);
        bubbleSortByMovieRating(movies, movieCount, sortOrder);
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 4)
    {
        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");

        printMovieList(movies, movieCount);

        if (!movieCount)
        {
            printf("|               No movie found released in %d.                 |\n", year);
        }
        else
        {
            printf("|%-8s = %-48d |\n", "Total Film", movieCount);
            printf("|==============================================================|\n");
        }

        char pick;
        do
        {
            printf("\nDo You Want to Search Again?[Y/N]: ");
            scanf(" %c", &pick);
        } while (pick != 'y' && pick != 'Y' && pick != 'n' && pick != 'N');

        if (pick == 'Y' || pick == 'y')
        {
            search();
        }
        else if (pick == 'N' || pick == 'n')
        {
            printf("\nPress enter to continue...");
            getch();
        }
    }
}

void searchByRating()
{
    system("cls");
    int rating;
    struct Movie movies[MAX_CHILDREN];
    int movieCount = 0;
    int sortOrder = 0;
    int chooseSort;

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    do
    {
        printf("|=============================|\n");
        printf("|---------Choose Sort---------|\n");
        printf("|=============================|\n");
        printf("| 1 | %-23s |\n", "Sort By Name");
        printf("| 2 | %-23s |\n", "Sort By Genre");
        printf("| 3 | %-23s |\n", "Sort By Yeas Release");
        printf("| 4 | %-23s |\n", "Not Sorted");
        printf("|=============================|\n");
        printf(">> ");
        scanf("%d", &chooseSort);
        system("cls");
    } while (chooseSort != 1 && chooseSort != 2 && chooseSort != 3 && chooseSort != 4);

    do
    {
        printf("Enter rating (1 to 5): ");
        scanf("%d", &rating);
    } while (rating < 1 || rating > 5);

    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^,], %7[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url, movies[movieCount].id) != EOF)
    {
        if (movies[movieCount].rating == rating)
        {
            movieCount++;
        }
    }
    fclose(file);

    if (chooseSort == 1)
    {
        strcpy(sortname, "Name");
        sortorder(&sortOrder);
        bubbleSortByMovieName(movies, movieCount, sortOrder);
        system("cls");
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 2)
    {
        strcpy(sortname, "Genre");
        sortorder(&sortOrder);
        bubbleSortByMovieGenre(movies, movieCount, sortOrder);
        system("cls");
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 3)
    {
        strcpy(sortname, "Year");
        sortorder(&sortOrder);
        bubbleSortByMovieYear(movies, movieCount, sortOrder);
        printSortedMovieList(movies, movieCount);
    }
    else if (chooseSort == 4)
    {
        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");
        printMovieList(movies, movieCount);

        if (!movieCount)
        {
            printf("|                 No movie found with rating %d.                |\n", rating);
            printf("|==============================================================|\n");
        }
        else
        {
            printf("|%-8s = %-48d |\n", "Total Film", movieCount);
            printf("|==============================================================|\n");
        }

        char pick;
        do
        {
            printf("\nDo You Want to Search Again?[Y/N]: ");
            scanf(" %c", &pick);
        } while (pick != 'y' && pick != 'Y' && pick != 'n' && pick != 'N');

        if (pick == 'Y' || pick == 'y')
        {
            search();
        }
        else if (pick == 'N' || pick == 'n')
        {
            printf("\nPress enter to continue...");
            getch();
        }
    }

    fclose(file);
}

void ViewMovie()
{
    system("cls");
    struct Movie movies[MAX_CHILDREN];
    int movieCount = 0;

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^,], %7[^\n]\n",
                  movies[movieCount].name,
                  movies[movieCount].genre,
                  &movies[movieCount].year,
                  &movies[movieCount].rating,
                  movies[movieCount].url, movies[movieCount].id) != EOF)
    {
        movieCount++;
    }

    char input;

    do
    {
        printf("\nDo You Want Sorting?[y/n]: ");
        scanf(" %c", &input);
    } while (input != 'y' && input != 'Y' && input != 'n' && input != 'N');

    if (input == 'y' || input == 'Y')
    {
        sortviewmovie(movies, movieCount);
    }
    else if (input == 'N' || input == 'n')
    {
        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");

        printMovieList(movies, movieCount);

        printf("|%-8s = %-48d |\n", "Total Film", movieCount);
        printf("|==============================================================|\n");
        printf("\nPress enter to continue...");
        getch();
    }

    fclose(file);
}

void generateID(const char *name, int number, char *id)
{
    char prefix[4] = "___";
    strncpy(prefix, name, 3);
    prefix[3] = '\0';
    for (int i = 0; i < 3; i++)
    {
        if (prefix[i] == ' ' || prefix[i] == ',' || prefix[i] == '\0')
        {
            prefix[i] = '_';
        }
    }
    sprintf(id, "%.3s%03d", prefix, number); // Format XXX000
}

int getRandomIDNumber()
{
    srand(time(NULL));
    return rand() % 1000;
}

void insertMovie(struct Trie *trie)
{
    system("cls");
    struct Movie *newMovie = (struct Movie *)malloc(sizeof(struct Movie));

    do
    {
        printf("Enter movie name: ");
        scanf(" %[^\n]", newMovie->name);
    } while (strlen(newMovie->name) > 100);

    printf("Enter genre: ");
    scanf(" %[^\n]", newMovie->genre);

    do
    {
        printf("Enter year of release: ");
        scanf("%d", &newMovie->year);
    } while (newMovie->year < 1900 || newMovie->year > 2024);

    do
    {
        printf("Enter rating (1 to 5): ");
        scanf("%d", &newMovie->rating);
    } while (newMovie->rating < 1 || newMovie->rating > 5);

    printf("Enter trailer URL: ");
    scanf(" %[^\n]", newMovie->url);

    int randomIDNumber = getRandomIDNumber();
    generateID(newMovie->name, randomIDNumber, newMovie->id);

    FILE *file = fopen("Film.txt", "a");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s, %s, %d, %d, %s, %s\n", newMovie->name, newMovie->genre, newMovie->year, newMovie->rating, newMovie->url, newMovie->id);

    insertTrie(trie, newMovie);

    printf("Movie added successfully.\n");

    fclose(file);

    printf("\nPress enter to continue...");
    getch();
}

void deleteMovie()
{
    system("cls");
    char id[100];
    printf("Enter movie ID to delete: ");
    scanf(" %99[^\n]", id);

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    struct Movie movies[MAX_CHILDREN];
    int movieCount = 0;
    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^,], %7[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url, movies[movieCount].id) != EOF)
    {
        if (strncasecmp(movies[movieCount].id, id, strlen(id)) == 0)
        {
            movieCount++;
        }
    }
    fclose(file);

    if (movieCount == 0)
    {
        printf("|==============================================================|\n");
        printf("|              No Movie Found With id %-12s             |\n", id);
        printf("|==============================================================|\n");
        printf("\nPress enter to continue...");
        getch();
        return;
    }

    printf("|==============================================================|\n");
    printf("|                          Movie List                          |\n");
    printf("|==============================================================|\n");
    for (int i = 0; i < movieCount; i++)
    {
        printf("|%-8s | %-50s |\n", "Name", movies[i].name);
        printf("|%-8s | %-50s |\n", "Genre", movies[i].genre);
        printf("|%-8s | %-50d |\n", "Released", movies[i].year);
        printf("|%-8s | %-50d |\n", "Rating", movies[i].rating);
        printf("|%-8s | %-50s |\n", "URL", movies[i].url);
        printf("|%-8s | %-50s |\n", "Id", movies[i].id);
        printf("|==============================================================|\n");
    }
    printf("|%-8s = %-48d |\n", "Total Film", movieCount);
    printf("|==============================================================|\n");

    char confirm[4];
    if (movieCount == 1)
    {
        do
        {
            printf("Are you sure you want to delete this movie? (yes/no): ");
            scanf(" %3s", confirm);
        } while (strcasecmp(confirm, "yes") != 0 && strcasecmp(confirm, "no") != 0);

        if (strcasecmp(confirm, "yes") != 0)
        {
            printf("Deletion canceled.\n");
            printf("\nPress enter to continue...");
            getch();
            return;
        }
        strcpy(id, movies[0].id);
    }
    else
    {
        printf("\nChoose Movie ID to Delete: ");
        scanf(" %99[^\n]", id);
    }

    FILE *tempFile = fopen("Temp.txt", "w");
    if (!tempFile)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    file = fopen("Film.txt", "r");
    struct Movie tempMovie;
    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^,], %7[^\n]\n", tempMovie.name, tempMovie.genre, &tempMovie.year, &tempMovie.rating, tempMovie.url, tempMovie.id) != EOF)
    {
        if (strncasecmp(tempMovie.id, id, strlen(id)) != 0)
        {
            fprintf(tempFile, "%s, %s, %d, %d, %s, %s\n", tempMovie.name, tempMovie.genre, tempMovie.year, tempMovie.rating, tempMovie.url, tempMovie.id);
        }
    }
    fclose(file);
    fclose(tempFile);

    remove("Film.txt");
    rename("Temp.txt", "Film.txt");
    printf("Movie deleted successfully.\n");

    printf("\nPress enter to continue...");
    getch();
}

void search()
{
    int choice;
    int sortBy;
    system("cls");
    printf("|===================================|\n");
    printf("|-Search your movies by Name, Genre-|\n");
    printf("|-------Year Release, Rating--------|\n");
    printf("|===================================|\n");
    printf("| 1 | %-29s |\n", "Search by Name");
    printf("| 2 | %-29s |\n", "Search by Genre");
    printf("| 3 | %-29s |\n", "Search by Year Release");
    printf("| 4 | %-29s |\n", "Search by Rating");
    printf("| 5 | %-29s |\n", "Back to Menu");
    printf("|===================================|\n");
    printf(">> ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        searchByName();
        break;
    case 2:
        searchByGenre();
        break;
    case 3:
        searchByYear();
        break;
    case 4:
        searchByRating();
        break;
    case 5:
        break;
    default:
        printf("Invalid input!\n");
        printf("Press enter to continue...");
        getch();
        break;
    }
}

void editfile()
{
    struct Movie movies[MAX_CHILDREN];
    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    int movieCount = 0;
    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^,], %7[^\n]\n",
                  movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year,
                  &movies[movieCount].rating, movies[movieCount].url, movies[movieCount].id) != EOF)
    {
        movieCount++;
    }
    fclose(file);

    char new[100];
    printf("Enter %s Movie to edit: ", edit);
    scanf(" %99[^\n]", new);

    FILE *tempFile = fopen("Temp.txt", "w");
    if (!tempFile)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    for (int i = 0; i < movieCount; i++)
    {
        if (strcasecmp(movies[i].id, idedit) == 0)
        {
            if (strcasecmp(edit, "Name") == 0)
            {
                strcpy(movies[i].name, new);
            }
            else if (strcasecmp(edit, "Genre") == 0)
            {
                strcpy(movies[i].genre, new);
            }
            else if (strcasecmp(edit, "Year") == 0)
            {
                movies[i].year = atoi(new);
            }
            else if (strcasecmp(edit, "Rating") == 0)
            {
                movies[i].rating = atoi(new);
            }
            else if (strcasecmp(edit, "URL") == 0)
            {
                strcpy(movies[i].url, new);
            }
        }
        fprintf(tempFile, "%s, %s, %d, %d, %s, %s\n", movies[i].name, movies[i].genre, movies[i].year, movies[i].rating, movies[i].url, movies[i].id);
    }

    fclose(tempFile);
    remove("Film.txt");
    rename("Temp.txt", "Film.txt");
    printf("Movie edited successfully.\n");

    printf("\nPress enter to continue...");
    getch();
}

void pickedit()
{
    int choice;

    do {
        system("cls"); // Clear screen
        printf("|================================|\n");
        printf("|------- Edit Name, Genre, ------|\n");
        printf("|-- Year Release, Rating, URL  --|\n");
        printf("|================================|\n");
        printf("| 1 | %-26s |\n", "Edit Name");
        printf("| 2 | %-26s |\n", "Edit Genre");
        printf("| 3 | %-26s |\n", "Edit Year Release");
        printf("| 4 | %-26s |\n", "Edit Rating");
        printf("| 5 | %-26s |\n", "Edit URL Trailer");
        printf("| 6 | %-26s |\n", "Back to Menu");
        printf("|================================|\n");
        printf("| %-10s = %-17s |\n", "Movie ID", idedit);
        printf("| %-10s = %-17s |\n", "Movie Name", nameedit);
        printf("|================================|\n");
        printf(">> ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 6) {
            printf("Invalid input!\n");
        }
    } while (choice < 1 || choice > 6);

    if (choice >= 1 && choice <= 5) {
        switch (choice) {
            case 1:
                strcpy(edit, "Name");
                break;
            case 2:
                strcpy(edit, "Genre");
                break;
            case 3:
                strcpy(edit, "Year");
                break;
            case 4:
                strcpy(edit, "Rating");
                break;
            case 5:
                strcpy(edit, "URL");
                break;
            default:
                break;
        }
        editfile();
        return;
    } else if (choice == 6) {
        printf("\nReturning to main menu...\n");
        printf("\nPress enter to continue...");
        getch();
    }
} 


void editMovie()
{
    system("cls");
    struct Movie movies[MAX_CHILDREN];
    char id[ID_LENGTH + 1];
    int movieCount = 0;
    char confirm[4];

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    do
    {
        printf("Enter movie ID (1-7 characters): ");
        scanf(" %7s", id);
    } while (strlen(id) > 7 || strlen(id) < 1);

    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^,], %7[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url, movies[movieCount].id) != EOF)
    {
        if (strncasecmp(movies[movieCount].id, id, strlen(id)) == 0)
        {
            strcpy(idedit, movies[movieCount].id);
            strcpy(nameedit, movies[movieCount].name);
            movieCount++;
        }
    }

    fclose(file);

    if (movieCount > 1)
    {
        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");
        printMovieList(movies, movieCount);
        printf("|%-8s = %-48d |\n", "Total Film", movieCount);
        printf("|==============================================================|\n");
        printf("Choose the movie ID you want to edit: ");
        scanf(" %7s", id);
        int found = 0;
        for (int i = 0; i < movieCount; i++)
        {
            if (strncasecmp(movies[i].id, id, strlen(id)) == 0)
            {
                found = 1;
            }
        }
        if (found)
        {
            pickedit();
        }
        else
        {
            printf("Movie not found.\n");
            printf("\nPress enter to continue...");
            getch();
            return;
        }
    }
    else if (movieCount == 1)
    {
        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");
        printMovieList(movies, movieCount);
        printf("|%-8s = %-48d |\n", "Total Film", movieCount);
        printf("|==============================================================|\n");
        printf("Do you want to edit this movie? (yes/no): ");
        scanf(" %3s", confirm);

        if (strcasecmp(confirm, "yes") == 0)
        {
            pickedit();
        }
        else
        {
            printf("Edit canceled.\n");
            printf("\nPress enter to continue...");
            getch();
            return;
        }
    }
    else
    {
        printf("Movie not found.\n");
        printf("Press enter to continue...");
        getch();
        return;
    }
}

int main()
{
    struct Trie trie;
    trie.root = createNode();

    int input;

    do
    {
        system("cls");
        printf("|===================================|\n");
        printf("|---WELCOME TO TLR Movie Searcher---|\n");
        printf("|===================================|\n");
        printf("| 1 | %-29s |\n", "View Movies");
        printf("| 2 | %-29s |\n", "Insert New Movie");
        printf("| 3 | %-29s |\n", "Search Movie");
        printf("| 4 | %-29s |\n", "Delete Movie");
        printf("| 5 | %-29s |\n", "Edit Movie");
        printf("| 6 | %-29s |\n", "Exit");
        printf("|===================================|\n");
        printf(">> ");
        scanf(" %d", &input);
        printf("\n");

        switch (input)
        {
        case 1:
            ViewMovie();
            break;
        case 2:
            insertMovie(&trie);
            break;
        case 3:
            search();
            break;
        case 4:
            deleteMovie();
            break;
        case 5:
            editMovie();
            break;
        case 6:
            system("cls");
            printf("Thank you for using TLR Movie Searcher!\nHave a nice day :)\n");
            printf("Press enter to exit...");
            getch();
            system("cls");
            break;
        default:
            printf("Invalid input!\n");
            printf("Press enter to continue...");
            getch();
            break;
        }
    } while (input != 6);

    return 0;
}