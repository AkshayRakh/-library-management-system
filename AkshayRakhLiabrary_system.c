#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int id;
    char title[100];
    char author[100];
    int available;
    struct Book *next;
} Book;

Book* create_node(int id, const char *title, const char *author, int available) {
    Book *n = (Book*)malloc(sizeof(Book));
    if(!n) return NULL;
    n->id = id;
    strncpy(n->title, title, sizeof(n->title)-1);
    n->title[sizeof(n->title)-1] = '\0';
    strncpy(n->author, author, sizeof(n->author)-1);
    n->author[sizeof(n->author)-1] = '\0';
    n->available = available;
    n->next = NULL;
    return n;
}

void add_book(Book **head) {
    int id;
    char title[100], author[100];
    printf("Enter Book ID: ");
    if(scanf("%d", &id)!=1) { 
        while(getchar()!='\n'); 
        return; 
    }
    while(getchar()!='\n');
    
    printf("Enter Title: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';
    
    printf("Enter Author: ");
    fgets(author, sizeof(author), stdin);
    author[strcspn(author, "\n")] = '\0';
    
    Book *n = create_node(id, title, author, 1);
    if(!*head) { 
        *head = n; 
        printf("Book added successfully.\n");
        return; 
    }
    
    Book *p = *head;
    while(p->next) p = p->next;
    p->next = n;
    printf("Book added successfully.\n");
}

void display_books(Book *head) {
    if(!head) { 
        printf("No books in the library.\n"); 
        return; 
    }
    printf("\nID\tTitle\t\t\tAuthor\t\t\tStatus\n");
    printf("-------------------------------------------------------------------------\n");
    while(head) {
        printf("%d\t%-20s\t%-20s\t%s\n", head->id, head->title, head->author, 
               head->available ? "Available" : "Issued");
        head = head->next;
    }
    printf("\n");
}

void delete_book(Book **head) {
    if(!*head) { 
        printf("List empty.\n"); 
        return; 
    }
    
    int id;
    printf("Enter Book ID to delete: ");
    if(scanf("%d", &id)!=1) { 
        while(getchar()!='\n'); 
        return; 
    }
    while(getchar()!='\n');
    
    Book *p = *head, *prev = NULL;
    while(p && p->id != id) { 
        prev = p; 
        p = p->next; 
    }
    
    if(!p) { 
        printf("Book not found.\n"); 
        return; 
    }
    
    if(!prev) 
        *head = p->next; 
    else 
        prev->next = p->next;
    
    free(p);
    printf("Book deleted successfully.\n");
}

void search_by_id(Book *head) {
    if(!head) { 
        printf("Library empty.\n"); 
        return; 
    }
    
    int id;
    printf("Enter Book ID to search: ");
    if(scanf("%d", &id)!=1) { 
        while(getchar()!='\n'); 
        return; 
    }
    while(getchar()!='\n');
    
    while(head) {
        if(head->id == id) {
            printf("Found: %d | %s | %s | %s\n", head->id, head->title, head->author,
                   head->available ? "Available" : "Issued");
            return;
        }
        head = head->next;
    }
    printf("Book not found.\n");
}

void search_by_title(Book *head) {
    if(!head) { 
        printf("Library empty.\n"); 
        return; 
    }
    
    char title[100];
    printf("Enter title to search: ");
    while(getchar()!='\n');
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';
    
    int found = 0;
    while(head) {
        if(strstr(head->title, title) != NULL) {
            printf("Found: %d | %s | %s | %s\n", head->id, head->title, head->author,
                   head->available ? "Available" : "Issued");
            found = 1;
        }
        head = head->next;
    }
    
    if(!found) {
        printf("Book not found.\n");
    }
}

void issue_book(Book *head) {
    if(!head) { 
        printf("Library empty.\n"); 
        return; 
    }
    
    int id;
    printf("Enter Book ID to issue: ");
    if(scanf("%d", &id)!=1) { 
        while(getchar()!='\n'); 
        return; 
    }
    while(getchar()!='\n');
    
    while(head) {
        if(head->id == id) {
            if(head->available) { 
                head->available = 0; 
                printf("Book issued successfully.\n"); 
            }
            else 
                printf("Book already issued.\n");
            return;
        }
        head = head->next;
    }
    printf("Book not found.\n");
}

void return_book(Book *head) {
    if(!head) { 
        printf("Library empty.\n"); 
        return; 
    }
    
    int id;
    printf("Enter Book ID to return: ");
    if(scanf("%d", &id)!=1) { 
        while(getchar()!='\n'); 
        return; 
    }
    while(getchar()!='\n');
    
    while(head) {
        if(head->id == id) {
            if(!head->available) { 
                head->available = 1; 
                printf("Book returned successfully.\n"); 
            }
            else 
                printf("Book already available.\n");
            return;
        }
        head = head->next;
    }
    printf("Book not found.\n");
}

void free_list(Book *head) {
    Book *t;
    while(head) { 
        t = head; 
        head = head->next; 
        free(t); 
    }
}

int main() {
    Book *head = NULL;
    int choice;
    
    printf("===== LIBRARY MANAGEMENT SYSTEM =====\n\n");
    
    while(1) {
        printf("\n1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Display Books\n");
        printf("4. Search by ID\n");
        printf("5. Search by Title\n");
        printf("6. Issue Book\n");
        printf("7. Return Book\n");
        printf("8. Exit\n");
        printf("Choose an option: ");
        
        if(scanf("%d", &choice)!=1) { 
            while(getchar()!='\n'); 
            printf("Invalid input. Please enter a number.\n");
            continue; 
        }
        
        switch(choice) {
            case 1: add_book(&head); break;
            case 2: delete_book(&head); break;
            case 3: display_books(head); break;
            case 4: search_by_id(head); break;
            case 5: search_by_title(head); break;
            case 6: issue_book(head); break;
            case 7: return_book(head); break;
            case 8: 
                free_list(head); 
                printf("Thank you for using Library Management System!\n");
                exit(0);
            default: 
                printf("Invalid choice. Please choose 1-8.\n");
        }
    }
    return 0;
}