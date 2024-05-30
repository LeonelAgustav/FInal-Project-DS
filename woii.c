#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define MAX_CHILDREN 26

struct Movie {
    char name[100];
    char genre[50];
    int year;
    int rating;
    char url[200];
};

struct TrieNode {
    struct TrieNode* children[MAX_CHILDREN];
    int is_leaf;
    struct Movie* movie;
};

struct Trie {
    struct TrieNode* root;
};

struct TrieNode* createNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (newNode) {
        newNode->is_leaf = 0;
        newNode->movie = NULL;
        for (int i = 0; i < MAX_CHILDREN; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

void insertTrie(struct Trie* trie, struct Movie* movie, char* genre) {
    struct TrieNode* currentNode = trie->root;
    for (int i = 0; genre[i] != '\0'; i++) {
        int index = toupper(genre[i]) - 'A';
        if (!currentNode->children[index]) {
            currentNode->children[index] = createNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->is_leaf = 1;
    currentNode->movie = movie;
}

void search_trie(struct TrieNode* node, char* prefix, char* buffer, int depth) {
    if (node == NULL) return;
    if (node->is_leaf) {
        buffer[depth] = '\0';
        printf("Movie found:\n");
        printf("Name: %s\n", node->movie->name);
        printf("Genre: %s\n", node->movie->genre);
        printf("Year: %d\n", node->movie->year);
        printf("Rating: %d\n", node->movie->rating);
        printf("URL: %s\n\n", node->movie->url);
    }
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            buffer[depth] = 'A' + i;
            search_trie(node->children[i], prefix, buffer, depth + 1);
        }
    }
}

void searchByGenre(struct Trie* trie) {
    system("cls");
    char genre[50];
    printf("Enter genre prefix (Action, Comedy, Adventure): ");
    scanf("%s", genre);

    struct TrieNode* currentNode = trie->root;
    for (int i = 0; genre[i] != '\0'; i++) {
        int index = toupper(genre[i]) - 'A';
        if (!currentNode->children[index]) {
            printf("No movie found with genre prefix %s.\n", genre);
            printf("\nPress enter to continue...");
            getch();
            return;
        }
        currentNode = currentNode->children[index];
    }

    char buffer[100];
    search_trie(currentNode, genre, buffer, 0);

    printf("\nPress enter to continue...");
    getch();
}

void searchByName() {
    system("cls");
    char name[100];
    printf("Enter movie name: ");
    scanf("%s", name);

    FILE* file = fopen("Film.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    struct Movie movie;
    int found = 0;
    while (fscanf(file, "%[^,], %[^,], %d, %d, %[^\n]\n", movie.name, movie.genre, &movie.year, &movie.rating, movie.url) == 5) {
        if (strncasecmp(movie.name, name, strlen(name)) == 0) {
            printf("Movie found:\n");
            printf("Name: %s\n", movie.name);
            printf("Genre: %s\n", movie.genre);
            printf("Year: %d\n", movie.year);
            printf("Rating: %d\n", movie.rating);
            printf("URL: %s\n\n", movie.url);
            found = 1;
        }
    }

    if (!found) {
        printf("No movie found with name prefix %s.\n", name);
    }

    fclose(file);

    printf("\nPress enter to continue...");
    getch();
}

void searchByYear() {
    system("cls");
    int year;
    printf("Enter year of release (1999 to 2024): ");
    scanf("%d", &year);

    FILE* file = fopen("Film.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    struct Movie movie;
    int found = 0;
    while (fscanf(file, "%[^,], %[^,], %d, %d, %[^\n]\n", movie.name, movie.genre, &movie.year, &movie.rating, movie.url) == 5) {
        if (movie.year == year) {
            printf("Movie found:\n");
            printf("Name: %s\n", movie.name);
            printf("Genre: %s\n", movie.genre);
            printf("Year: %d\n", movie.year);
            printf("Rating: %d\n", movie.rating);
            printf("URL: %s\n\n", movie.url);
            found = 1;
        }
    }

    if (!found) {
        printf("No movie found released in %d.\n", year);
    }

    fclose(file);

    printf("\nPress enter to continue...");
    getch();
}

void searchByRating() {
    system("cls");
    int rating;

    do {
        printf("Enter rating (1 to 5): ");
        scanf("%d", &rating);
    } while (rating < 1 || rating > 5);

    FILE* file = fopen("Film.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    struct Movie movie;
    int found = 0;
    while (fscanf(file, "%[^,], %[^,], %d, %d, %[^\n]\n", movie.name, movie.genre, &movie.year, &movie.rating, movie.url) == 5) {
        if (movie.rating == rating) {
            printf("Movie found:\n");
            printf("Name: %s\n", movie.name);
            printf("Genre: %s\n", movie.genre);
            printf("Year: %d\n", movie.year);
            printf("Rating: %d\n", movie.rating);
            printf("URL: %s\n\n", movie.url);
            found = 1;
        }
    }

    if (!found) {
        printf("No movie found with rating %d.\n", rating);
    }

    fclose(file);

    printf("\nPress enter to continue...");
    getch();
}

void insertMovie() {
    system("cls");
    struct Movie newMovie;

    printf("Enter movie name: ");
    getchar(); 
    fgets(newMovie.name, 100, stdin);
    newMovie.name[strcspn(newMovie.name, "\n")] = '\0';

    printf("Enter genre: ");
    fgets(newMovie.genre, 50, stdin);
    newMovie.genre[strcspn(newMovie.genre, "\n")] = '\0';

    printf("Enter year of release: ");
    scanf("%d", &newMovie.year);

    do {
        printf("Enter rating (1 to 5): ");
        scanf("%d", &newMovie.rating);
    } while (newMovie.rating < 1 || newMovie.rating > 5);

    printf("Enter trailer URL: ");
    getchar(); 
    fgets(newMovie.url, 200, stdin);
    newMovie.url[strcspn(newMovie.url, "\n")] = '\0';

    FILE* file = fopen("Film.txt", "a");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s, %s, %d, %d, %s\n", newMovie.name, newMovie.genre, newMovie.year, newMovie.rating, newMovie.url);
    fclose(file);

    printf("Movie added successfully.\n");

    printf("\nPress enter to continue...");
    getch();
}

void deleteMovie() {
    system("cls");
    char name[100];
    printf("Enter movie name to delete: ");
    getchar(); 
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';

    FILE* file = fopen("Film.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    FILE* tempFile = fopen("Temp.txt", "w");
    if (!tempFile) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    struct Movie movie;
    int found = 0;
    while (fscanf(file, "%[^,], %[^,], %d, %d, %[^\n]\n", movie.name, movie.genre, &movie.year, &movie.rating, movie.url) == 5) {
        if (strcmp(movie.name, name) != 0) {
            fprintf(tempFile, "%s, %s, %d, %d, %s\n", movie.name, movie.genre, movie.year, movie.rating, movie.url);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("Film.txt");
        rename("Temp.txt", "Film.txt");
        printf("Movie deleted successfully.\n");
    } else {
        remove("Temp.txt");
        printf("No movie found with name %s.\n", name);
    }

    printf("\nPress enter to continue...");
    getch();
}

int main() {
    struct Trie* trie = (struct Trie*)malloc(sizeof(struct Trie));
    trie->root = createNode();

    int input;

    do {
        system("cls");
        printf("=====================================\n");
        printf("----WELCOME TO TLR MOVIE SEARCHER----\n");
        printf("--Search your movies by Name, Genre--\n");
        printf("=====================================\n");
        printf("1. Insert New Movie\n");
        printf("2. Search by Name\n");
        printf("3. Search by Genre\n");
        printf("4. Search by Year Release\n");
        printf("5. Search by Rating\n");
        printf("6. Delete Movie\n");
        printf("7. Exit\n");
        printf(">> ");
        scanf("%d", &input);
        printf("\n");

        switch (input) {
            case 1:
                insertMovie();
                break;
            case 2:
                searchByName();
                break;
            case 3:
                searchByGenre(trie);
                break;
            case 4:
                searchByYear();
                break;
            case 5:
                searchByRating();
                break;
            case 6:
                deleteMovie();
                break;
            case 7:
                printf("Thank you for using TLR Movie Searcher.. Have a nice day! :)\n");
                printf("Press enter to continue...");
                getch();
                system("cls");
                break;
            default:
                printf("Invalid input!\n");
                printf("Press enter to continue...");
                getch();
                break;
        }
    } while (input != 7);

    return 0;
}
