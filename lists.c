#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store book information
typedef struct Book {
    char title[100];
    char author[100];
    int year;
    struct Book* next;
} Book;

// Function to create a new book
Book* createBook(char* title, char* author, int year) {
    Book* newBook = (Book*) malloc(sizeof(Book));
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->year = year;
    newBook->next = NULL;
    return newBook;
}

// Function to insert a book into the list
void insertBook(Book** list, char* title, char* author, int year) {
    Book* newBook = createBook(title, author, year);
    newBook->next = *list;
    *list = newBook;
    printf("Book '%s' successfully inserted!\n", title);
}

// Function to remove a book from the list
void removeBook(Book** list, char* title) {
    Book* current = *list;
    Book* previous = NULL;

    while (current != NULL && strcmp(current->title, title) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Book '%s' not found!\n", title);
        return;
    }

    if (previous == NULL) {
        *list = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Book '%s' successfully removed!\n", title);
}

// Function to display all books in the list
void displayBooks(Book* list) {
    Book* current = list;

    if (current == NULL) {
        printf("No books in the list.\n");
        return;
    }

    while (current != NULL) {
        printf("Title: %s | Author: %s | Year: %d\n", current->title, current->author, current->year);
        current = current->next;
    }
}

// Function to search for a book in the list
void searchBook(Book* list, char* title) {
    Book* current = list;

    while (current != NULL && strcmp(current->title, title) != 0) {
        current = current->next;
    }

    if (current != NULL) {
        printf("Book found: Title: %s | Author: %s | Year: %d\n", current->title, current->author, current->year);
    } else {
        printf("Book '%s' not found.\n", title);
    }
}

// Function to sort the book list by year using Bubble Sort
void sortBooks(Book** list) {
    if (*list == NULL) {
        return;
    }

    int swapped;
    Book *ptr1;
    Book *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *list;

        while (ptr1->next != lptr) {
            if (ptr1->year > ptr1->next->year) {
                // Swap book data
                char tempTitle[100], tempAuthor[100];
                int tempYear;

                strcpy(tempTitle, ptr1->title);
                strcpy(tempAuthor, ptr1->author);
                tempYear = ptr1->year;

                strcpy(ptr1->title, ptr1->next->title);
                strcpy(ptr1->author, ptr1->next->author);
                ptr1->year = ptr1->next->year;

                strcpy(ptr1->next->title, tempTitle);
                strcpy(ptr1->next->author, tempAuthor);
                ptr1->next->year = tempYear;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("Book list sorted by year.\n");
}

int main() {
    Book* bookList = NULL;
    int option;
    char title[100], author[100];
    int year;

    do {
        printf("\nMenu:\n");
        printf("1. Insert book\n");
        printf("2. Remove book\n");
        printf("3. Display all books\n");
        printf("4. Search for a book\n");
        printf("5. Sort book list\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Title: ");
                scanf(" %[^\n]%*c", title);
                printf("Author: ");
                scanf(" %[^\n]%*c", author);
                printf("Year: ");
                scanf("%d", &year);
                insertBook(&bookList, title, author, year);
                break;
            case 2:
                printf("Title of the book to be removed: ");
                scanf(" %[^\n]%*c", title);
                removeBook(&bookList, title);
                break;
            case 3:
                displayBooks(bookList);
                break;
            case 4:
                printf("Title of the book to be searched: ");
                scanf(" %[^\n]%*c", title);
                searchBook(bookList, title);
                break;
            case 5:
                sortBooks(&bookList);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option!\n");
        }
    } while (option != 0);

    return 0;
}
