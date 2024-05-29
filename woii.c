#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define MAX_CHILDREN 256

struct Movie {
    char name[100];
    char genre[50];
    int year;
    int rating;
    char url[200];
};

struct TrieNode {
    struct TrieNode* children[26];
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
        for (int i = 0; i < 26; i++) {
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

int search_trie(struct TrieNode* root, char* word) {
    struct TrieNode* temp = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int position = toupper(word[i]) - 'A';
        if (temp->children[position] == NULL)
            return 0;
        temp = temp->children[position];
    }
    if (temp != NULL && temp->is_leaf == 1)
        return 1;
    return 0;
}


void searchByGenre(struct Trie* trie) {
    system("cls");
    char genre[50];
    printf("Enter genre (Action, Comedy, Adventure): ");
    scanf("%s", genre);

    if (!search_trie(trie->root, genre)) {
        printf("No movie found with genre %s.\n", genre);
    } else {
        printf("Movie found:\n");
        printf("Name: %s\n", trie->root->movie->name);
        printf("Genre: %s\n", trie->root->movie->genre);
        printf("Year: %d\n", trie->root->movie->year);
        printf("Rating: %d\n", trie->root->movie->rating);
        printf("URL: %s\n", trie->root->movie->url);
    }

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
        if (strcmp(movie.name, name) == 0) {
            printf("Movie found:\n");
            printf("Name: %s\n", movie.name);
            printf("Genre: %s\n", movie.genre);
            printf("Year: %d\n", movie.year);
            printf("Rating: %d\n", movie.rating);
            printf("URL: %s\n", movie.url);
            found = 1;
        }
    }

    if (!found) {
        printf("No movie found with name %s.\n", name);
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
            printf("URL: %s\n", movie.url);
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
            printf("URL: %s\n", movie.url);
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

int main() {
    struct Trie* trie = (struct Trie*)malloc(sizeof(struct Trie));
    trie->root = createNode();

    int input;

    do {
        system("cls");
        printf("=====================================\n");
        printf("----WELCOME TO TLR Movie Searcher----\n");
        printf("--Search your movies by Name, Genre--\n");
        printf("=====================================\n");
        printf("1. Search by Name\n");
        printf("2. Search by Genre\n");
        printf("3. Search by Year Release\n");
        printf("4. Search by Rating\n");
        printf("5. Exit\n");
        printf(">> ");
        scanf("%d", &input);
        printf("\n");

        switch (input) {
            case 1:
                searchByName();
                printf("\nPress enter to continue...");
                getch();
                break;
            case 2:
                searchByGenre(trie);
                printf("\nPress enter to continue...");
                getch();
                break;
            case 3:
                searchByYear();
                printf("\nPress enter to continue...");
                getch();
                break;
            case 4:
                searchByRating();
                printf("\nPress enter to continue...");
                getch();
                break;
            case 5:
                printf("Thank you... Have a nice day :)\n");
                printf("Press enter to continue...");
                getch();
                system("cls");
                break;
            default:
                printf("Invalid input..!\n");
                printf("Press enter to continue...");
                getch();
                break;
        }
    } while (input != 5);

    return 0;
}

