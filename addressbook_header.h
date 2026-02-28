#ifndef ADDRESSBOOK_HEADER_H
#define ADDRESSBOOK_HEADER_H

// --- Structure definitions ---
struct contact {
    char name[50];
    char mobile[20];
    char mail[50];
};

struct addressbook {
    struct contact arr[100];//original variable
    int count;   
};

// --- Function prototypes ---
// Core operations
void create_contact(struct addressbook *ptr);
void display_contact(struct addressbook var);
void search_contact(struct addressbook *ptr);
void delete_contact(struct addressbook *ptr);
void edit_contact(struct addressbook *ptr);
void save_contact(struct addressbook *ptr);
void load_contact(struct addressbook *ptr);

// Validation functions
int validate_name(const char *name);
int validate_mobile(const char *mobile);
int validate_email(const char *email);

#endif
