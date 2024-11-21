#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_BOOKS 10000

// Define the structure for books
struct Library {
    int book_id;
    char book_name[50];
    char author[50];
    int pages;
    float price;
};

// Function declarations
void addBook(struct Library lib[], int *count);
void displayBooks(struct Library lib[], int count);
void listBooksByAuthor(struct Library lib[], int count);
void totalCount(int count);
void searchByTitle(struct Library lib[], int count);
void issueBook(struct Library lib[], int *count);
void saveToFile(struct Library lib[], int count);
void loadFromFile(struct Library lib[], int *count);
void toLowerCase(const char *source, char *destination);

// Utility functions
void flushInput();
int getValidatedChoice();
void printSeparator();

// Main function
int main() {
    struct Library lib[MAX_BOOKS];
    int count = 0;
    int choice;

    printf("Loading data from file...\n");
    loadFromFile(lib, &count);
    printf("Loaded %d books from file.\n", count);

    while (1) {
        printf("\n\n** Welcome to Library Management System **\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. List Books by Author\n");
        printf("4. Show Total Book Count\n");
        printf("5. Search Book by Title\n");
        printf("6. Issue Book\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        choice = getValidatedChoice();

        switch (choice) {
            case 1:
                addBook(lib, &count);
                saveToFile(lib, count);
                break;
            case 2:
                displayBooks(lib, count);
                break;
            case 3:
                listBooksByAuthor(lib, count);
                break;
            case 4:
                totalCount(count);
                break;
            case 5:
                searchByTitle(lib, count);
                break;
            case 6:
                issueBook(lib, &count);
                saveToFile(lib, count);
                break;
            case 7:
                saveToFile(lib, count);
                printf("Data saved. Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Function to add a book
void addBook(struct Library lib[], int *count) {
    if (*count >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    lib[*count].book_id = *count + 1;

    printf("\nEnter book name: ");
    flushInput();
    fgets(lib[*count].book_name, 50, stdin);
    lib[*count].book_name[strcspn(lib[*count].book_name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter author name: ");
    fgets(lib[*count].author, 50, stdin);
    lib[*count].author[strcspn(lib[*count].author, "\n")] = '\0';

    printf("Enter number of pages: ");
    scanf("%d", &lib[*count].pages);

    printf("Enter price: ");
    scanf("%f", &lib[*count].price);

    (*count)++;
    printf("Book added successfully!\n");
}

// Function to display all books
void displayBooks(struct Library lib[], int count) {
    if (count == 0) {
        printf("No books available in the library.\n");
        return;
    }

    printf("\n%-10s | %-30s | %-30s | %-10s | %-10s\n", "Book ID", "Book Name", "Author", "Pages", "Price (Rs)");
    printSeparator();
    for (int i = 0; i < count; i++) {
        printf("%-10d | %-30s | %-30s | %-10d | Rs%-9.2f\n",
               lib[i].book_id, lib[i].book_name, lib[i].author, lib[i].pages, lib[i].price);
    }
}

// Function to list books by a specific author
void listBooksByAuthor(struct Library lib[], int count) {
    char author[50], lowerInput[50], lowerAuthor[50];
    int found = 0;

    printf("\nEnter author name: ");
    flushInput();
    fgets(author, 50, stdin);
    author[strcspn(author, "\n")] = '\0';
    toLowerCase(author, lowerInput);

    printf("\nBooks by '%s':\n", author);
    printf("\n%-10s | %-30s | %-30s | %-10s | %-10s\n", "Book ID", "Book Name", "Author", "Pages", "Price (Rs)");
    printSeparator();

    for (int i = 0; i < count; i++) {
        toLowerCase(lib[i].author, lowerAuthor);
        if (strcmp(lowerInput, lowerAuthor) == 0) {
            printf("%-10d | %-30s | %-30s | %-10d | Rs%-9.2f\n",
                   lib[i].book_id, lib[i].book_name, lib[i].author, lib[i].pages, lib[i].price);
            found = 1;
        }
    }

    if (!found) {
        printf("No books found by author '%s'.\n", author);
    }
}

// Function to show the total count of books
void totalCount(int count) {
    printf("\nTotal number of books in the library: %d\n", count);
}

// Function to search a book by its title
void searchByTitle(struct Library lib[], int count) {
    char title[50], lowerInput[50], lowerTitle[50];
    int found = 0;

    printf("\nEnter book title to search: ");
    flushInput();
    fgets(title, 50, stdin);
    title[strcspn(title, "\n")] = '\0';
    toLowerCase(title, lowerInput);

    printf("\n%-10s | %-30s | %-30s | %-10s | %-10s\n", "Book ID", "Book Name", "Author", "Pages", "Price (Rs)");
    printSeparator();

    for (int i = 0; i < count; i++) {
        toLowerCase(lib[i].book_name, lowerTitle);
        if (strcmp(lowerInput, lowerTitle) == 0) {
            printf("%-10d | %-30s | %-30s | %-10d | Rs%-9.2f\n",
                   lib[i].book_id, lib[i].book_name, lib[i].author, lib[i].pages, lib[i].price);
            found = 1;
        }
    }
    if (!found) {
        printf("No book found with title '%s'.\n", title);
    }
}

// Function to issue a book
void issueBook(struct Library lib[], int *count) {
    char title[50], lowerInput[50], lowerTitle[50];
    int found = 0;

    printf("\nEnter book title to issue: ");
    flushInput();
    fgets(title, 50, stdin);
    title[strcspn(title, "\n")] = '\0';
    toLowerCase(title, lowerInput);

    for (int i = 0; i < *count; i++) {
        toLowerCase(lib[i].book_name, lowerTitle);
        if (strcmp(lowerInput, lowerTitle) == 0) {
            found = 1;

            // Shift all books after the issued book one position left
            for (int j = i; j < *count - 1; j++) {
                lib[j] = lib[j + 1];
            }
            (*count)--;

            // Reset book IDs
            for (int k = 0; k < *count; k++) {
                lib[k].book_id = k + 1;
            }

            printf("Book with title '%s' issued successfully.\n", title);
            break;
        }
    }

    if (!found) {
        printf("No book found with title '%s'.\n", title);
    }
}

// Function to save library data to a file
void saveToFile(struct Library lib[], int count) {
    FILE *fp = fopen("library_data.txt", "w");
    if (!fp) {
        perror("Error saving data to file");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%d,%.2f\n",
                lib[i].book_id,
                lib[i].book_name,
                lib[i].author,
                lib[i].pages,
                lib[i].price);
    }

    fclose(fp);
    printf("Library data saved to file successfully.\n");
}

// Function to load library data from a file
void loadFromFile(struct Library lib[], int *count) {
    FILE *fp = fopen("library_data.txt", "r");
    if (!fp) {
        printf("No existing data file found. Starting fresh.\n");
        return;
    }

    *count = 0;
    while (fscanf(fp, "%d,%49[^,],%49[^,],%d,%f\n",
                  &lib[*count].book_id,
                  lib[*count].book_name,
                  lib[*count].author,
                  &lib[*count].pages,
                  &lib[*count].price) != EOF) {
        (*count)++;
    }

    fclose(fp);
    printf("Library data loaded successfully.\n");
}

// Function to convert a string to lowercase
void toLowerCase(const char *source, char *destination) {
    while (*source) {
        *destination = tolower(*source);
        source++;
        destination++;
    }
    *destination = '\0';
}

// Function to flush input buffer
void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to get validated integer input for menu choice
int getValidatedChoice() {
    int choice;
    if (scanf("%d", &choice) != 1) {
        flushInput();
        return -1; // Return invalid choice
    }
    return choice;
}

// Function to print a separator for table formatting
void printSeparator() {
    printf("---------------------------------------------------------------------------------------------\n");
}
