#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define MAX_CHILDREN 200

struct Movie
{
    char name[100];
    char genre[50];
    int year;
    int rating;
    char url[200];
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

void insertTrie(struct Trie *trie, struct Movie *movie, char *genre)
{
    struct TrieNode *currentNode = trie->root;
    for (int i = 0; genre[i] != '\0'; i++)
    {
        int index = toupper(genre[i]) - 'A';
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
void sort();

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
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

void bubbleSortByMovieYear(struct Movie movies[], int movieCount, int sortOrder)
{
    int swapped;
    for (int i = 0; i < movieCount - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < movieCount - i - 1; j++)
        {
            if ((sortOrder > 0 && movies[j].year > movies[j + 1].year) ||
                (sortOrder < 0 && movies[j].year < movies[j + 1].year))
            {
                swapMovies(&movies[j], &movies[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

void bubbleSortByMovieRating(struct Movie movies[], int movieCount, int sortOrder)
{
    int swapped;
    for (int i = 0; i < movieCount - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < movieCount - i - 1; j++)
        {
            if ((sortOrder > 0 && movies[j].rating > movies[j + 1].rating) ||
                (sortOrder < 0 && movies[j].rating < movies[j + 1].rating))
            {
                swapMovies(&movies[j], &movies[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

void bubbleSortByMovieGenre(struct Movie movies[], int movieCount, int sortOrder)
{

    int swapped;
    for (int i = 0; i < movieCount - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < movieCount - i - 1; j++)
        {
            if ((sortOrder > 0 && strcmp(movies[j].genre, movies[j + 1].genre) > 0) ||
                (sortOrder < 0 && strcmp(movies[j].genre, movies[j + 1].genre) < 0))
            {
                swapMovies(&movies[j], &movies[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
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
        printf("|==============================================================|\n");
    }
    printf("|%-8s = %-48d |\n", "Total Film", movieCount);
    printf("|==============================================================|\n");
}

void sort(struct Movie movies[], int movieCount)
{
    int sortChoice, sortOrder;
    int input;

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
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            do
            {
                system("cls");
                printf("|=====================|\n");
                printf("|- Choose Sort Order -|\n");
                printf("|=====================|\n");
                printf("| 1 | %-15s |\n", "Ascending");
                printf("| 2 | %-15s |\n", "Descending");
                printf("|=====================|\n");
                printf(">> ");
                scanf("%d", &sortChoice);

                if (sortChoice == 1)
                {
                    system("cls");
                    sortOrder = 1;
                    printf("|==============================================================|\n");
                    printf("|--------------------------Movie List--------------------------|\n");
                    printf("|-------------------Sorted by Name Ascending-------------------|\n");
                    printf("|==============================================================|\n");
                    bubbleSortByMovieName(movies, movieCount, sortOrder);
                    printMovieList(movies, movieCount);
                    printf("Press enter to continue...");
                    getch();
                    break;
                }
                else if (sortChoice == 2)
                {
                    system("cls");
                    sortOrder = -1;
                    printf("|==============================================================|\n");
                    printf("|--------------------------Movie List--------------------------|\n");
                    printf("|------------------Sorted by Name Descending-------------------|\n");
                    printf("|==============================================================|\n");
                    bubbleSortByMovieName(movies, movieCount, sortOrder);
                    printMovieList(movies, movieCount);
                    printf("Press enter to continue...");
                    getch();
                    break;
                }
            } while (sortChoice != 1 && sortChoice != 2);
            break;
        case 2:
            do
            {
                system("cls");
                printf("|=====================|\n");
                printf("|- Choose Sort Order -|\n");
                printf("|=====================|\n");
                printf("| 1 | %-15s |\n", "Ascending");
                printf("| 2 | %-15s |\n", "Descending");
                printf("|=====================|\n");
                printf(">> ");
                scanf("%d", &sortChoice);

                if (sortChoice == 1)
                {
                    system("cls");
                    sortOrder = 1;
                    printf("|==============================================================|\n");
                    printf("|--------------------------Movie List--------------------------|\n");
                    printf("|------------------Sorted by Genre Ascending-------------------|\n");
                    printf("|==============================================================|\n");
                    bubbleSortByMovieGenre(movies, movieCount, sortOrder);
                    printMovieList(movies, movieCount);
                    printf("Press enter to continue...");
                    getch();
                    break;
                }
                else if (sortChoice == 2)
                {
                    system("cls");
                    sortOrder = -1;
                    printf("|==============================================================|\n");
                    printf("|--------------------------Movie List--------------------------|\n");
                    printf("|-----------------Sorted by Genre Descending-------------------|\n");
                    printf("|==============================================================|\n");
                    bubbleSortByMovieGenre(movies, movieCount, sortOrder);
                    printMovieList(movies, movieCount);
                    printf("Press enter to continue...");
                    getch();
                    break;
                }
            } while (sortChoice != 1 && sortChoice != 2);
            break;
        case 3:
            do
            {
                system("cls");
                printf("|=====================|\n");
                printf("|- Choose Sort Order -|\n");
                printf("|=====================|\n");
                printf("| 1 | %-15s |\n", "Ascending");
                printf("| 2 | %-15s |\n", "Descending");
                printf("|=====================|\n");
                printf(">> ");
                scanf("%d", &sortChoice);

                if (sortChoice == 1)
                {
                    system("cls");
                    sortOrder = 1;
                    printf("|==============================================================|\n");
                    printf("|--------------------------Movie List--------------------------|\n");
                    printf("|--------------Sorted by Year Released Ascending---------------|\n");
                    printf("|==============================================================|\n");
                    bubbleSortByMovieYear(movies, movieCount, sortOrder);
                    printMovieList(movies, movieCount);
                    printf("Press enter to continue...");
                    getch();
                    break;
                }
                else if (sortChoice == 2)
                {
                    system("cls");
                    sortOrder = -1;
                    printf("|==============================================================|\n");
                    printf("|--------------------------Movie List--------------------------|\n");
                    printf("|-------------Sorted by Year Released Descending---------------|\n");
                    printf("|==============================================================|\n");
                    bubbleSortByMovieYear(movies, movieCount, sortOrder);
                    printMovieList(movies, movieCount);
                    printf("Press enter to continue...");
                    getch();
                    break;
                }
            } while (sortChoice != 1 && sortChoice != 2);
            break;
        case 4:
            do
            {
                system("cls");
                printf("|=====================|\n");
                printf("|- Choose Sort Order -|\n");
                printf("|=====================|\n");
                printf("| 1 | %-15s |\n", "Ascending");
                printf("| 2 | %-15s |\n", "Descending");
                printf("|=====================|\n");
                printf(">> ");
                scanf("%d", &sortChoice);

                if (sortChoice == 1)
                {
                    system("cls");
                    sortOrder = 1;
                    printf("|==============================================================|\n");
                    printf("|--------------------------Movie List--------------------------|\n");
                    printf("|------------------Sorted by Rating Ascending------------------|\n");
                    printf("|==============================================================|\n");
                    bubbleSortByMovieRating(movies, movieCount, sortOrder);
                    printMovieList(movies, movieCount);
                    printf("Press enter to continue...");
                    getch();
                    break;
                }
                else if (sortChoice == 2)
                {
                    system("cls");
                    sortOrder = -1;
                    printf("|==============================================================|\n");
                    printf("|--------------------------Movie List--------------------------|\n");
                    printf("|-----------------Sorted by Rating Descending------------------|\n");
                    printf("|==============================================================|\n");
                    bubbleSortByMovieRating(movies, movieCount, sortOrder);
                    printMovieList(movies, movieCount);
                    printf("Press enter to continue...");
                    getch();
                    break;
                }
            } while (sortChoice != 1 && sortChoice != 2);
            break;
        case 5:
        
            break;
        default:
            printf("Press enter to continue...");
            getch();
            break;
        }
    } while (input != 5);
}

void searchByGenre()
{
    system("cls");
    char genre[50];
    struct Movie movies[MAX_CHILDREN];
    int movieCount = 0;

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    char input;
    printf("\nDo You Want Sorting?[y/n]: ");
    scanf(" %c", &input);

    printf("Enter genre prefix (Drama, Crime, Action, Adventure, Sci-Fi, Thriller, Mystery, Biography, Musical, Comedy, Romance, Horror, Family, Animation, War, Western, Film-Noir): ");
    scanf("%s", genre);

    if (input == 'y' || input == 'Y')
    {
        while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url) != EOF)
        {
            if (strncasecmp(movies[movieCount].genre, genre, strlen(genre)) == 0)
            {
                movieCount++;
            }
        }

        sort(movies, movieCount);
    }
    else if (input == 'n' || input == 'N')
    {
        system("cls");

        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");

        while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url) != EOF)
        {
            if (strncasecmp(movies[movieCount].genre, genre, strlen(genre)) == 0)
            {
                movieCount++;
                printf("|%-8s | %-50s |\n", "Name", movies[movieCount].name);
                printf("|%-8s | %-50s |\n", "Genre", movies[movieCount].genre);
                printf("|%-8s | %-50d |\n", "Released", movies[movieCount].year);
                printf("|%-8s | %-50d |\n", "Rating", movies[movieCount].rating);
                printf("|%-8s | %-50s |\n", "URL", movies[movieCount].url);
            }
            printf("|==============================================================|\n");
        }
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
        printf("\nDo You Want to Search Again?[Y/N]: ");
        scanf(" %c", &pick);

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

void searchByName()
{
    system("cls");
    char name[100];
    struct Movie movies[MAX_CHILDREN];
    int movieCount = 0;

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    char input;
    printf("\nDo You Want Sorting?[y/n]: ");
    scanf(" %c", &input);

    printf("Enter movie name: ");
    scanf("%99s", name);

    if (input == 'y' || input == 'Y')
    {
        while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url) != EOF)
        {
            if (strncasecmp(movies[movieCount].name, name, strlen(name)) == 0)
            {
                movieCount++;
            }
        }

        sort(movies, movieCount);
    }
    else if (input == 'n' || input == 'N')
    {
        system("cls");

        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");

        while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url) != EOF)
        {
            if (strncasecmp(movies[movieCount].name, name, strlen(name)) == 0)
            {
                movieCount++;
                printf("|%-8s | %-50s |\n", "Name", movies[movieCount].name);
                printf("|%-8s | %-50s |\n", "Genre", movies[movieCount].genre);
                printf("|%-8s | %-50d |\n", "Released", movies[movieCount].year);
                printf("|%-8s | %-50d |\n", "Rating", movies[movieCount].rating);
                printf("|%-8s | %-50s |\n", "URL", movies[movieCount].url);
            }
            printf("|==============================================================|\n");
        }
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
        printf("\nDo You Want to Search Again?[Y/N]: ");
        scanf(" %c", &pick);

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

void searchByYear()
{
    system("cls");
    int year;
    struct Movie movies[MAX_CHILDREN];
    int movieCount = 0;

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    char input;
    printf("\nDo You Want Sorting?[y/n]: ");
    scanf(" %c", &input);

    do
    {
        printf("Enter year of release (1900 to 2024): ");
        scanf("%d", &year);
    } while (year < 1900 || year > 2024);;

    if (input == 'y' || input == 'Y')
    {
        while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url) != EOF)
        {
            if (movies[movieCount].year == year)
            {
                movieCount++;
            }
        }

        sort(movies, movieCount);
    }
    else if (input == 'n' || input == 'N')
    {
        system("cls");

        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");

        while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url) != EOF)
        {
            if (movies[movieCount].year == year)
            {
                movieCount++;
                printf("|%-8s | %-50s |\n", "Name", movies[movieCount].name);
                printf("|%-8s | %-50s |\n", "Genre", movies[movieCount].genre);
                printf("|%-8s | %-50d |\n", "Released", movies[movieCount].year);
                printf("|%-8s | %-50d |\n", "Rating", movies[movieCount].rating);
                printf("|%-8s | %-50s |\n", "URL", movies[movieCount].url);
            }
            printf("|==============================================================|\n");
        }
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
        printf("\nDo You Want to Search Again?[Y/N]: ");
        scanf(" %c", &pick);

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

void searchByRating()
{
    system("cls");
    int rating;
    struct Movie movies[MAX_CHILDREN];
    int movieCount = 0;

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    char input;
    printf("\nDo You Want Sorting?[y/n]: ");
    scanf(" %c", &input);

    do
    {
        printf("Enter rating (1 to 5): ");
        scanf("%d", &rating);
    } while (rating < 1 || rating > 5);

    if (input == 'y' || input == 'Y')
    {
        while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url) != EOF)
        {
            if (movies[movieCount].rating == rating)
            {
                movieCount++;
            }
        }

        sort(movies, movieCount);
    }
    else if (input == 'n' || input == 'N')
    {
        system("cls");

        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");

        while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^\n]\n", movies[movieCount].name, movies[movieCount].genre, &movies[movieCount].year, &movies[movieCount].rating, movies[movieCount].url) != EOF)
        {
            if (movies[movieCount].rating == rating)
            {
                movieCount++;
                printf("|%-8s | %-50s |\n", "Name", movies[movieCount].name);
                printf("|%-8s | %-50s |\n", "Genre", movies[movieCount].genre);
                printf("|%-8s | %-50d |\n", "Released", movies[movieCount].year);
                printf("|%-8s | %-50d |\n", "Rating", movies[movieCount].rating);
                printf("|%-8s | %-50s |\n", "URL", movies[movieCount].url);
            }
            printf("|==============================================================|\n");
        }
        if (!movieCount)
        {
            printf("|                 No movie found with rating %d.                |\n", rating);
        }
        else
        {
            printf("|%-8s = %-48d |\n", "Total Film", movieCount);
            printf("|==============================================================|\n");
        }
        char pick;
        printf("\nDo You Want to Search Again?[Y/N]: ");
        scanf(" %c", &pick);

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
    struct Movie movies[MAX_CHILDREN]; // Assuming MAX_CHILDREN is defined somewhere
    int movieCount = 0;

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^\n]\n",
                  movies[movieCount].name,
                  movies[movieCount].genre,
                  &movies[movieCount].year,
                  &movies[movieCount].rating,
                  movies[movieCount].url) == 5)
    {
        movieCount++;
    }

    char input;

    printf("\nDo You Want Sorting?[y/n]: ");
    scanf(" %c", &input);

    if (input == 'y' || input == 'Y')
    {
        sort(movies, movieCount);
    }
    else if (input == 'N' || input == 'n')
    {
        printf("|==============================================================|\n");
        printf("|                          Movie List                          |\n");
        printf("|==============================================================|\n");

        // Print movies from the array
        for (int i = 0; i < movieCount; i++)
        {
            printf("|%-8s | %-50s |\n", "Name", movies[i].name);
            printf("|%-8s | %-50s |\n", "Genre", movies[i].genre);
            printf("|%-8s | %-50d |\n", "Released", movies[i].year);
            printf("|%-8s | %-50d |\n", "Rating", movies[i].rating);
            printf("|%-8s | %-50s |\n", "URL", movies[i].url);
            printf("|==============================================================|\n");
        }

        printf("|%-8s = %-48d |\n", "Total Film", movieCount);
        printf("|==============================================================|\n");
    }

    fclose(file);

    printf("\nPress enter to continue...");
    getch();
}

void insertMovie()
{
    system("cls");
    struct Movie newMovie;

    do
    {
        printf("Enter movie name: ");
        scanf(" %[^\n]", newMovie.name);
    } while (strlen(newMovie.name) > 100);

    printf("Enter genre: ");
    scanf(" %[^\n]", newMovie.genre);

    do
    {
        printf("Enter year of release: ");
        scanf("%d", &newMovie.year);
    } while (newMovie.year < 1900 || newMovie.year > 2024);

    do
    {
        printf("Enter rating (1 to 5): ");
        scanf("%d", &newMovie.rating);
    } while (newMovie.rating < 1 || newMovie.rating > 5);

    printf("Enter trailer URL: ");
    scanf(" %[^\n]", newMovie.url);

    FILE *file = fopen("Film.txt", "a");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s, %s, %d, %d, %s\n", newMovie.name, newMovie.genre, newMovie.year, newMovie.rating, newMovie.url);

    printf("Movie added successfully.\n");

    fclose(file);

    printf("\nPress enter to continue...");
    getch();
}

void deleteMovie()
{
    system("cls");
    char name[100];
    printf("Enter movie name to delete: ");
    getchar();
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("Temp.txt", "w");
    if (!tempFile)
    {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    struct Movie movie;
    int found = 0;
    while (fscanf(file, "%[^,], %[^,], %d, %d, %[^\n]\n", movie.name, movie.genre, &movie.year, &movie.rating, movie.url) == 5)
    {
        if (strcmp(movie.name, name) != 0)
        {
            fprintf(tempFile, "%s, %s, %d, %d, %s\n", movie.name, movie.genre, movie.year, movie.rating, movie.url);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("Film.txt");
        rename("Temp.txt", "Film.txt");
        printf("Movie deleted successfully.\n");
    }
    else
    {
        remove("Temp.txt");
        printf("No movie found with name %s.\n", name);
    }

    printf("\nPress enter to continue...");
    getch();
}

void search()
{
    int choice;
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

int main()
{
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    trie->root = createNode();

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
        printf("| 5 | %-29s |\n", "Exit");
        printf("|===================================|\n");
        printf(">> ");
        scanf("%d", &input);
        printf("\n");

        switch (input)
        {
        case 1:
            ViewMovie();
            break;
        case 2:
            insertMovie();
            break;
        case 3:
            search();
            break;
        case 4:
            deleteMovie();
            break;
        case 5:
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
    } while (input != 5);

    return 0;
}