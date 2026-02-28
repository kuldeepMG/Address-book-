#include <stdio.h>
#include <stdlib.h>
#include "addressbook_header.h"

int main()
{
    struct addressbook book;
    book.count = 0;

    load_contact(&book); // Load contacts at startup
   

    int choice;

    while (1) {
        printf("\n===== Address Book Menu =====\n");
        printf("1. Create Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Edit Contact\n");
        printf("6. save contact and Exit\n"); // Only exit (auto-save)
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_contact(&book); break;
            case 2: display_contact(book); break;
            case 3: search_contact(&book); break;
            case 4: delete_contact(&book); break;
            case 5: edit_contact(&book); break;
            case 6: 
                save_contact(&book); // Auto-save
                printf("Exiting...\n"); 
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
