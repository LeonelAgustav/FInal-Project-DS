#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define MAX_CHILDREN 26

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

void searchByGenre()
{
    system("cls");
    char genre[50];
    printf("Enter genre prefix (Action, Comedy, Adventure): ");
    scanf("%s", genre);

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    struct Movie movie;
    int found = 0;

    printf("|==============================================================|\n");
    printf("|                          Movie List                          |\n");
    printf("|==============================================================|\n");

    while (fscanf(file, "%[^,], %[^,], %d, %d, %[^\n]\n", movie.name, movie.genre, &movie.year, &movie.rating, movie.url) == 5)
    {
        if (strncasecmp(movie.genre, genre, strlen(genre)) == 0)
        {
            printf("|%-8s | %-50s |\n", "Name", movie.name);
            printf("|%-8s | %-50s |\n", "Genre", movie.genre);
            printf("|%-8s | %-50d |\n", "Released", movie.year);
            printf("|%-8s | %-50d |\n", "Rating", movie.rating);
            printf("|%-8s | %-50s |\n", "URL", movie.url);
            printf("|==============================================================|\n");
            found++;
        }
    }

    if (!found)
    {
        printf("No movie found released in %s.\n", genre);
    } else
    {
        printf("|%-8s = %-48d |\n", "Total Film", found);
        printf("|==============================================================|\n");
    }

    char pick;
    printf("Do You Want to Search Again?[Y/N]: ");
    scanf(" %c", &pick);

    if (pick == 'Y' || pick == 'y')
    {
        search();
    } else if (pick == 'N' || pick == 'n')
    {
        printf("\nPress enter to continue...");
        getch();
    }
}

void searchByName()
{
    system("cls");
    char name[100];
    printf("Enter movie name: ");
    scanf("%s", name);

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    struct Movie movie;
    int found = 0;

    printf("|==============================================================|\n");
    printf("|                          Movie List                          |\n");
    printf("|==============================================================|\n");

    while (fscanf(file, "%[^,], %[^,], %d, %d, %[^\n]\n", movie.name, movie.genre, &movie.year, &movie.rating, movie.url) == 5)
    {
        if (strncasecmp(movie.name, name, strlen(name)) == 0)
        {
            printf("|%-8s | %-50s |\n", "Name", movie.name);
            printf("|%-8s | %-50s |\n", "Genre", movie.genre);
            printf("|%-8s | %-50d |\n", "Released", movie.year);
            printf("|%-8s | %-50d |\n", "Rating", movie.rating);
            printf("|%-8s | %-50s |\n", "URL", movie.url);
            printf("|==============================================================|\n");
            found++;
        }
    }

    if (!found)
    {
        printf("No movie found released in %s.\n", name);
    } else
    {
        printf("|%-8s = %-48d |\n", "Total Film", found);
        printf("|==============================================================|\n");
    }

    fclose(file);

    char pick;
    printf("Do You Want to Search Again?[Y/N]: ");
    scanf(" %c", &pick);

    if (pick == 'Y' || pick == 'y')
    {
        search();
    } else if (pick == 'N' || pick == 'n')
    {
        printf("\nPress enter to continue...");
        getch();
    }
}

void searchByYear()
{
    system("cls");
    int year;
    do
    {
        printf("Enter year of release (1900 to 2024): ");
        scanf("%d", &year);
    } while (year < 1900 || year > 2024);

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    struct Movie movie;
    int found = 0;

    printf("|==============================================================|\n");
    printf("|                          Movie List                          |\n");
    printf("|==============================================================|\n");

    while (fscanf(file, "%[^,], %[^,], %d, %d, %[^\n]\n", movie.name, movie.genre, &movie.year, &movie.rating, movie.url) != EOF)
    {
        if (movie.year == year)
        {
            printf("|%-8s | %-50s |\n", "Name", movie.name);
            printf("|%-8s | %-50s |\n", "Genre", movie.genre);
            printf("|%-8s | %-50d |\n", "Released", movie.year);
            printf("|%-8s | %-50d |\n", "Rating", movie.rating);
            printf("|%-8s | %-50s |\n", "URL", movie.url);
            printf("|==============================================================|\n");
            found++;
        }
    }

    if (!found)
    {
        printf("No movie found released in %d.\n", year);
    } else
    {
        printf("|%-8s = %-48d |\n", "Total Film", found);
        printf("|==============================================================|\n");
    }

    fclose(file);

    char pick;
    printf("Do You Want to Search Again?[Y/N]: ");
    scanf(" %c", &pick);

    if (pick == 'Y' || pick == 'y')
    {
        search();
    } else if (pick == 'N' || pick == 'n')
    {
        printf("\nPress enter to continue...");
        getch();
    }
}

void searchByRating()
{
    system("cls");
    int rating;

    do
    {
        printf("Enter rating (1 to 5): ");
        scanf("%d", &rating);
    } while (rating < 1 || rating > 5);

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    struct Movie movie;
    int found = 0;

    printf("|==============================================================|\n");
    printf("|                          Movie List                          |\n");
    printf("|==============================================================|\n");

    while (fscanf(file, "%[^,], %[^,], %d, %d, %[^\n]\n", movie.name, movie.genre, &movie.year, &movie.rating, movie.url) != EOF)
    {
        if (movie.rating == rating)
        {
            printf("|%-8s | %-50s |\n", "Name", movie.name);
            printf("|%-8s | %-50s |\n", "Genre", movie.genre);
            printf("|%-8s | %-50d |\n", "Released", movie.year);
            printf("|%-8s | %-50d |\n", "Rating", movie.rating);
            printf("|%-8s | %-50s |\n", "URL", movie.url);
            printf("|==============================================================|\n");
            found++;
        }
    }

    if (!found)
    {
        printf("No movie found with rating %d.\n", rating);
    }
    else
    {
        printf("|%-8s = %-48d |\n", "Total Film", found);
        printf("|==============================================================|\n");
    }

    fclose(file);

    char pick;
    printf("Do You Want to Search Again?[Y/N]: ");
    scanf(" %c", &pick);

    if (pick == 'Y' || pick == 'y')
    {
        search();
    } else if (pick == 'N' || pick == 'n')
    {
        printf("\nPress enter to continue...");
        getch();
    }
}

void ViewMovie()
{
    system("cls");

    FILE *file = fopen("Film.txt", "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    struct Movie movie;
    int found = 0;

    printf("|==============================================================|\n");
    printf("|                          Movie List                          |\n");
    printf("|==============================================================|\n");

    while (fscanf(file, "%99[^,], %49[^,], %d, %d, %199[^\n]\n", movie.name, movie.genre, &movie.year, &movie.rating, movie.url) != EOF)
    {
        found++;
        printf("|%-8s | %-50s |\n", "Name", movie.name);
        printf("|%-8s | %-50s |\n", "Genre", movie.genre);
        printf("|%-8s | %-50d |\n", "Released", movie.year);
        printf("|%-8s | %-50d |\n", "Rating", movie.rating);
        printf("|%-8s | %-50s |\n", "URL", movie.url);
        printf("|==============================================================|\n");
    }

    printf("|%-8s = %-48d |\n", "Total Film", found);
    printf("|==============================================================|\n");

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
    printf("=====================================\n");
    printf("--Search your movies by Name, Genre--\n");
    printf("--------Year Release, Rating---------\n");
    printf("=====================================\n");
    printf("1. Search by Name\n");
    printf("2. Search by Genre\n");
    printf("3. Search by Year Release\n");
    printf("4. Search by Rating\n");
    printf("5. Back to Menu\n");
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
        printf("=====================================\n");
        printf("----WELCOME TO TLR Movie Searcher----\n");
        printf("=====================================\n");
        printf("1. View Movies\n");
        printf("2. Insert New Movie\n");
        printf("3. Search Movie\n");
        printf("4. Delete Movie\n");
        printf("5. Exit\n");
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
            printf("Thank you for using TLR Movie Searher!\nHave a nice day :)\n");
            printf("Press enter to continue...");
            getch();
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