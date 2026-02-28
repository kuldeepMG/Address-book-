#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "addressbook_header.h"

// =================== Validation Functions ===================
int validate_name(const char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ') 
        {
            printf("Invalid name! Only letters and spaces allowed.\n");
            return 0;
        }
    }
    return 1;
}

int validate_mobile(const char *mobile)
{
    if (strlen(mobile) != 10) 
    {
        printf("Invalid mobile! Must be 10 digits.\n");
        return 0;
    }
    for (int i = 0; mobile[i] != '\0'; i++) 
    {
        if (!isdigit(mobile[i])) 
        {
            printf("Invalid mobile! Only digits allowed.\n");
            return 0;
        }
    }
    return 1;
}

int validate_email(const char *email)
{
    int i = 0, at_found = 0;

    while (email[i] != '\0') 
    {
        if (email[i] == '@') 
        {
            at_found = 1;
            break;
        }
        if (!islower(email[i]) && !isdigit(email[i])) 
        {
            printf("Invalid email! Only lowercase letters or digits before '@'.\n");
            return 0;
        }
        i++;
    }

    if (!at_found || i == 0) 
    {
        printf("Invalid email! Must contain '@' and local part.\n");
        return 0;
    }

    i++; // skip '@'
    if (!islower(email[i])) 
    {
        printf("Invalid email! Domain must be in lowercase letter.\n");
        return 0;
    }

    while (email[i] != '\0' && strncmp(&email[i], ".com", 4) != 0) 
    {
        if (!islower(email[i])) 
        {
            printf("Invalid email! Domain must have only lowercase letters.\n");
            return 0;
        }
        i++;
    }

    if (strcmp(&email[i], ".com") != 0) 
    {
        printf("Invalid email! Must end with '.com'.\n");
        return 0;
    }

    return 1;
}

//*******************END OF ALL VALIDATION**********************************

// =================== Core Functions ===================
void create_contact(struct addressbook *book)
{
    if (book->count >= 100) 
    {
        printf("Address book full!\n");
        return;
    }

    struct contact c; // temporary variable to hold new contact

    printf("Enter Name: ");
    scanf(" %[^\n]", c.name); // read full name including spaces
    if (!validate_name(c.name)) return;

    printf("Enter Mobile: ");
    scanf(" %[^\n]", c.mobile);
    if (!validate_mobile(c.mobile)) return;

    printf("Enter Email: ");
    scanf(" %[^\n]", c.mail);
    if (!validate_email(c.mail)) return;

    book->arr[book->count++] = c; // add contact to array & increment count
    printf("Contact added successfully!\n");
}

void display_contact(struct addressbook book)
{
    if (book.count == 0) 
    {
        printf("No contacts to display.\n");
        return;
    }

    printf("\n----- Contact List -----\n");
    for (int i = 0; i < book.count; i++) 
    {
        printf("Name: %s\n", book.arr[i].name);
        printf("Mobile: %s\n", book.arr[i].mobile);
        printf("Email: %s\n\n", book.arr[i].mail);
    }
}

void search_contact(struct addressbook *book) 
{
    int choice;
    char key[50];
    int found = 0;

    // --- Main search menu ---
    printf("\n=== Search Contact ===\n");
    printf("1. Search by Name\n2. Search by Mobile\n3. Search by Email\nEnter your choice: ");
    scanf("%d", &choice);
    getchar(); // clear newline

    switch(choice) 
    {
        //---CASE 1: Search by NAME ---
        case 1: 
        {
            printf("Enter name: ");
            scanf(" %[^\n]", key);

            int match_indexes[100];  // store indexes of matched contacts
            int match_count = 0;     // number of matches found

            // find all contacts with the same name
            for (int i = 0; i < book->count; i++) 
            {
                if (strcmp(book->arr[i].name, key) == 0)
                    match_indexes[match_count++] = i;
            }

            // if no contact found
            if (match_count == 0) 
            {
                printf("Contact not found.\n");
                return;
            } 
            // if exactly one contact found
            else if (match_count == 1) 
            {
                int idx = match_indexes[0];//assign the index
                printf("\nContact Details:\nName: %s\nMobile: %s\nEmail: %s\n",
                       book->arr[idx].name, book->arr[idx].mobile, book->arr[idx].mail);
                return;
            }

            // multiple contacts found with same name
            printf("\nMultiple contacts found with name '%s'.\n", key);
            printf("1. Search by Mobile\n2. Search by Email\nEnter choice: ");
            int sub_choice;
            scanf("%d", &sub_choice);
            getchar();

            char sub_key[50];
            int match_found = 0; // flag to check second-level match

            switch (sub_choice) 
            {
                //  Search by mobile if different people have same name 
                case 1:
                    printf("Enter mobile: ");
                    scanf(" %[^\n]", sub_key);
                    for (int j = 0; j < match_count; j++) 
                    {
                        int idx = match_indexes[j];//assign the index of  same name
                        if (strcmp(book->arr[idx].mobile, sub_key) == 0) 
                        {
                            printf("\nContact Details:\nName: %s\nMobile: %s\nEmail: %s\n",
                                   book->arr[idx].name, book->arr[idx].mobile, book->arr[idx].mail);
                            match_found = 1;
                            break;
                        }
                    }
                    if (!match_found)
                        printf("No match found for that mobile.\n");
                    break;

                //  Search by mail if different people have same name 
                case 2:
                    printf("Enter email: ");
                    scanf(" %[^\n]", sub_key);
                    for (int j = 0; j < match_count; j++) 
                    {
                        int idx = match_indexes[j];//assign the index of  same name
                        if (strcmp(book->arr[idx].mail, sub_key) == 0) 
                        {
                            printf("\nContact Details:\nName: %s\nMobile: %s\nEmail: %s\n",
                                   book->arr[idx].name, book->arr[idx].mobile, book->arr[idx].mail);
                            match_found = 1;
                            break;
                        }
                    }
                    if (!match_found)
                        printf("No match found for that email.\n");
                    break;

                default:
                    printf("Invalid choice.\n");
            }
            break;
        }

        // ---- CASE 2: Search by MOBILE ----
        case 2: 
        {
            printf("Enter mobile: ");
            scanf(" %[^\n]", key);
            for (int i = 0; i < book->count; i++) 
            {
                if (strcmp(book->arr[i].mobile, key) == 0) 
                {
                    printf("\nContact Details:\nName: %s\nMobile: %s\nEmail: %s\n",
                           book->arr[i].name, book->arr[i].mobile, book->arr[i].mail);
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("Contact not found.\n");
            break;
        }

        // ---- CASE 3: Search by EMAIL ----
        case 3: {
            printf("Enter email: ");
            scanf(" %[^\n]", key);
            for (int i = 0; i < book->count; i++) 
            {
                if (strcmp(book->arr[i].mail, key) == 0) 
                {
                    printf("\nContact Details:\nName: %s\nMobile: %s\nEmail: %s\n",
                           book->arr[i].name, book->arr[i].mobile, book->arr[i].mail);
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("Contact not found.\n");
            break;
        }

        // ---- DEFAULT CASE ----
        default:
            printf("Invalid choice!\n");
    }
}

void delete_contact(struct addressbook *book)
{
    int choice;
    char key[50];

    printf("\n=== Delete Contact ===\n");
    printf("1. Delete by Name\n");
    printf("2. Delete by Mobile\n");
    printf("3. Delete by Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // clear newline

    switch(choice)
    {
        // ====== CASE 1: Delete by NAME ======
        case 1: 
        {
            printf("Enter name: ");
            scanf(" %[^\n]", key);

            int match_indexes[100], match_count = 0;

            // find all contacts with the same name
            for(int i = 0; i < book->count; i++) 
            {
                if(strcmp(book->arr[i].name, key) == 0)
                    match_indexes[match_count++] = i;
            }

            if(match_count == 0) 
            {
                printf(" Contact not found.\n");
                return;
            } 
            else if(match_count == 1) 
            {
                int idx = match_indexes[0];
                printf("Are you sure you want to delete '%s'? (y/n): ", book->arr[idx].name);
                char confirm;
                scanf(" %c", &confirm);
                if(confirm != 'y' && confirm != 'Y') 
                {
                    printf("Deletion cancelled.\n");
                    return;
                }

                // shift contacts to delete
                for(int j = idx; j < book->count - 1; j++)
                    book->arr[j] = book->arr[j + 1];
                book->count--;
                printf(" Contact deleted successfully!\n");
                return;
            }

            // multiple contacts with same name
            printf("\nMultiple contacts found with name '%s'.\n", key);
            printf("1. Delete by Mobile\n2. Delete by Email\nEnter choice: ");
            int sub_choice;
            scanf("%d", &sub_choice);
            getchar();

            char sub_key[50];
            int match_found = 0;

            switch(sub_choice) 
            {
                case 1: // delete by mobile
                    printf("Enter mobile: ");
                    scanf(" %[^\n]", sub_key);
                    for(int j = 0; j < match_count; j++) 
                    {
                        int idx = match_indexes[j];
                        if(strcmp(book->arr[idx].mobile, sub_key) == 0) 
                        {
                            printf("Are you sure you want to delete '%s'? (y/n): ", book->arr[idx].name);
                            char confirm;
                            scanf(" %c", &confirm);
                            if(confirm != 'y' && confirm != 'Y') 
                            {
                                printf("Deletion cancelled.\n");
                                return;
                            }
                            for(int k = idx; k < book->count - 1; k++)
                                book->arr[k] = book->arr[k + 1];
                            book->count--;
                            printf(" Contact deleted successfully!\n");
                            match_found = 1;
                            break;
                        }
                    }
                    if(!match_found)
                        printf(" No match found for that mobile.\n");
                    break;

                case 2: // delete by email
                    printf("Enter email: ");
                    scanf(" %[^\n]", sub_key);
                    for(int j = 0; j < match_count; j++) 
                    {
                        int idx = match_indexes[j];
                        if(strcmp(book->arr[idx].mail, sub_key) == 0) 
                        {
                            printf("Are you sure you want to delete '%s'? (y/n): ", book->arr[idx].name);
                            char confirm;
                            scanf(" %c", &confirm);
                            if(confirm != 'y' && confirm != 'Y') 
                            {
                                printf("Deletion cancelled.\n");
                                return;
                            }
                            for(int k = idx; k < book->count - 1; k++)
                                book->arr[k] = book->arr[k + 1];
                            book->count--;
                            printf(" Contact deleted successfully!\n");
                            match_found = 1;
                            break;
                        }
                    }
                    if(!match_found)
                        printf(" No match found for that email.\n");
                    break;

                default:
                    printf(" Invalid choice.\n");
            }
            break;
        }

        // ====== CASE 2: Delete by MOBILE ======
        case 2: 
        {
            printf("Enter mobile: ");
            scanf(" %[^\n]", key);
            int deleted = 0;
            for(int i = 0; i < book->count; i++) 
            {
                if(strcmp(book->arr[i].mobile, key) == 0) 
                {
                    printf("Are you sure you want to delete '%s'? (y/n): ", book->arr[i].name);
                    char confirm;
                    scanf(" %c", &confirm);
                    if(confirm != 'y' && confirm != 'Y') 
                    {
                        printf("Deletion cancelled.\n");
                        return;
                    }
                    for(int j = i; j < book->count - 1; j++)
                        book->arr[j] = book->arr[j + 1];
                    book->count--;
                    printf(" Contact deleted successfully!\n");
                    deleted = 1;
                    break;
                }
            }
            if(!deleted)
                printf(" Contact not found.\n");
            break;
        }

        // ====== CASE 3: Delete by EMAIL ======
        case 3: 
        {
            printf("Enter email: ");
            scanf(" %[^\n]", key);
            int deleted = 0;
            for(int i = 0; i < book->count; i++) 
            {
                if(strcmp(book->arr[i].mail, key) == 0) 
                {
                    printf("Are you sure you want to delete '%s'? (y/n): ", book->arr[i].name);
                    char confirm;
                    scanf(" %c", &confirm);
                    if(confirm != 'y' && confirm != 'Y') 
                    {
                        printf("Deletion cancelled.\n");
                        return;
                    }
                    for(int j = i; j < book->count - 1; j++)
                        book->arr[j] = book->arr[j + 1];
                    book->count--;
                    printf(" Contact deleted successfully!\n");
                    deleted = 1;
                    break;
                }
            }
            if(!deleted)
                printf(" Contact not found.\n");
            break;
        }

        default:
            printf(" Invalid choice!\n");
    }
}

void edit_contact(struct addressbook *book)  
{
    int choice;
    char key[50];

    printf("\n=== Edit Contact ===\n");
    printf("1. Edit by Name\n2. Edit by Mobile\n3. Edit by Email\nEnter your choice: ");
    scanf("%d", &choice);
    getchar(); // clear newline

    switch(choice)
    {
        // ====== CASE 1: Edit by NAME ======
        case 1: 
        {
            printf("Enter name: ");
            scanf(" %[^\n]", key);

            int match_indexes[100], match_count = 0;

            for(int i = 0; i < book->count; i++)
                if(strcmp(book->arr[i].name, key) == 0)
                    match_indexes[match_count++] = i;

            if(match_count == 0) 
            {
                printf(" Contact not found.\n");
                return;
            } 
            else if(match_count == 1) 
            {
                int idx = match_indexes[0];

                // ---- Temporary buffers (fix) ----
                char new_name[50], new_mobile[15], new_email[50];

                printf("Editing Contact:\nOld Name: %s\n", book->arr[idx].name);

                printf("New Name: "); 
                scanf(" %[^\n]", new_name);
                if(!validate_name(new_name)) return;

                printf("New Mobile: "); 
                scanf(" %[^\n]", new_mobile);
                if(!validate_mobile(new_mobile)) return;

                printf("New Email: "); 
                scanf(" %[^\n]", new_email);
                if(!validate_email(new_email)) return;

                // All valid → update struct
                strcpy(book->arr[idx].name, new_name);
                strcpy(book->arr[idx].mobile, new_mobile);
                strcpy(book->arr[idx].mail, new_email);

                printf(" Contact updated successfully!\n");
                return;
            }

            // ===== Multiple contacts with same name =====
            printf("\nMultiple contacts found with name '%s'.\n", key);
            printf("1. Edit by Mobile\n2. Edit by Email\nEnter choice: ");
            int sub_choice;
            scanf("%d", &sub_choice);
            getchar();

            char sub_key[50];
            int match_found = 0;

            switch(sub_choice) 
            {
                // ===== Edit by Mobile =====
                case 1:
                {
                    printf("Enter mobile: ");
                    scanf(" %[^\n]", sub_key);

                    for(int j = 0; j < match_count; j++) 
                    {
                        int idx = match_indexes[j];

                        if(strcmp(book->arr[idx].mobile, sub_key) == 0) 
                        {
                            // temp buffers
                            char new_name[50], new_mobile[15], new_email[50];

                            printf("Editing Contact:\nOld Name: %s\n", book->arr[idx].name);

                            printf("New Name: "); 
                            scanf(" %[^\n]", new_name);
                            if(!validate_name(new_name)) return;

                            printf("New Mobile: "); 
                            scanf(" %[^\n]", new_mobile);
                            if(!validate_mobile(new_mobile)) return;

                            printf("New Email: "); 
                            scanf(" %[^\n]", new_email);
                            if(!validate_email(new_email)) return;

                            strcpy(book->arr[idx].name, new_name);
                            strcpy(book->arr[idx].mobile, new_mobile);
                            strcpy(book->arr[idx].mail, new_email);

                            printf(" Contact updated successfully!\n");
                            match_found = 1;
                            break;
                        }
                    }

                    if(!match_found)
                        printf(" No match found for that mobile.\n");
                    break;
                }

                // ===== Edit by Email =====
                case 2:
                {
                    printf("Enter email: ");
                    scanf(" %[^\n]", sub_key);

                    for(int j = 0; j < match_count; j++) 
                    {
                        int idx = match_indexes[j];

                        if(strcmp(book->arr[idx].mail, sub_key) == 0) 
                        {
                            char new_name[50], new_mobile[15], new_email[50];

                            printf("Editing Contact:\nOld Name: %s\n", book->arr[idx].name);

                            printf("New Name: "); 
                            scanf(" %[^\n]", new_name);
                            if(!validate_name(new_name)) return;

                            printf("New Mobile: "); 
                            scanf(" %[^\n]", new_mobile);
                            if(!validate_mobile(new_mobile)) return;

                            printf("New Email: "); 
                            scanf(" %[^\n]", new_email);
                            if(!validate_email(new_email)) return;

                            strcpy(book->arr[idx].name, new_name);
                            strcpy(book->arr[idx].mobile, new_mobile);
                            strcpy(book->arr[idx].mail, new_email);

                            printf(" Contact updated successfully!\n");
                            match_found = 1;
                            break;
                        }
                    }

                    if(!match_found)
                        printf(" No match found for that email.\n");
                    break;
                }

                default:
                    printf(" Invalid choice.\n");
            }
            break;
        }

        // ====== CASE 2: Edit by Mobile ======
        case 2:
        {
            printf("Enter mobile: ");
            scanf(" %[^\n]", key);

            for(int i = 0; i < book->count; i++) 
            {
                if(strcmp(book->arr[i].mobile, key) == 0) 
                {
                    char new_name[50], new_mobile[15], new_email[50];

                    printf("Editing Contact:\nOld Name: %s\n", book->arr[i].name);

                    printf("New Name: "); 
                    scanf(" %[^\n]", new_name);
                    if(!validate_name(new_name)) return;

                    printf("New Mobile: "); 
                    scanf(" %[^\n]", new_mobile);
                    if(!validate_mobile(new_mobile)) return;

                    printf("New Email: "); 
                    scanf(" %[^\n]", new_email);
                    if(!validate_email(new_email)) return;

                    strcpy(book->arr[i].name, new_name);
                    strcpy(book->arr[i].mobile, new_mobile);
                    strcpy(book->arr[i].mail, new_email);

                    printf(" Contact updated successfully!\n");
                    return;
                }
            }

            printf(" Contact not found.\n");
            break;
        }

        // ====== CASE 3: Edit by Email ======
        case 3:
        {
            printf("Enter email: ");
            scanf(" %[^\n]", key);

            for(int i = 0; i < book->count; i++) 
            {
                if(strcmp(book->arr[i].mail, key) == 0) 
                {
                    char new_name[50], new_mobile[15], new_email[50];

                    printf("Editing Contact:\nOld Name: %s\n", book->arr[i].name);

                    printf("New Name: "); 
                    scanf(" %[^\n]", new_name);
                    if(!validate_name(new_name)) return;

                    printf("New Mobile: "); 
                    scanf(" %[^\n]", new_mobile);
                    if(!validate_mobile(new_mobile)) return;

                    printf("New Email: "); 
                    scanf(" %[^\n]", new_email);
                    if(!validate_email(new_email)) return;

                    strcpy(book->arr[i].name, new_name);
                    strcpy(book->arr[i].mobile, new_mobile);
                    strcpy(book->arr[i].mail, new_email);

                    printf(" Contact updated successfully!\n");
                    return;
                }
            }

            printf(" Contact not found.\n");
            break;
        }

        default:
            printf(" Invalid choice!\n");
    }
}



// =================== Save Contacts to File ===================
void save_contact(struct addressbook *book)
{
    FILE *fp = fopen("contacts.csv", "w");
    if(!fp) //if(fp==NULL)
    { 
        printf("Error saving file.\n"); 
        return; 
    }

    fprintf(fp,"# %d\n",book->count);
    for(int i = 0; i < book->count; i++) 
    {
        fprintf(fp, "%s,%s,%s\n", book->arr[i].name, book->arr[i].mobile, book->arr[i].mail);
    }

    fclose(fp);
    printf("Contacts saved to file successfully!\n");
}

// =================== Load Contacts from File ===================


void load_contact(struct addressbook *book)
{
    FILE *fp = fopen("contacts.csv", "r");
    if(!fp) 
    {
        printf("No previous contacts found. Starting fresh.\n");
        return;
    }

    fscanf(fp, "#%d\n",&book->count);
    for(int i = 0; i < book->count; i++) 
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n", book->arr[i].name, book->arr[i].mobile, book->arr[i].mail);
    }

    fclose(fp);
    printf("Loaded %d contacts from file.\n", book->count);
}


