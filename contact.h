#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
//which information want to the address book
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];//The strcture is stored in the array
    int contactCount;//how many contact stored it
} AddressBook;//every information stored in the address

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook,int ret);
void deleteContact(AddressBook *addressBook,int ret1);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
