#include <stdio.h>
#include "contact.h"
#include <ctype.h>

int main() 
{
    int choice;
    AddressBook addressBook;
    addressBook.contactCount=0;
    initialize(&addressBook); // Initialize the address book

    do 
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        // printf("7. Exit\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);//call the create contact function
                break;
            case 2:
                searchContact(&addressBook);//call the search contact function
                break;
            case 3:
            int ret=searchContact(&addressBook);//call the search contact function
                 editContact(&addressBook,ret);//search contact choose call the edit contact function
                 break;
             case 4:
             int ret1=searchContact(&addressBook);//call the search contact function
                 deleteContact(&addressBook,ret1);//search contact choose call the delete contact function
               break;
            case 5:          
                 listContacts(&addressBook);//call the list alphabetic order contact function
                 break;
             case 6:
                  printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);//save contact exit the program save it
                    break;
            default:
                printf("Invalid choice. Please try again.\n");
    } 
}while (choice !=6);
    
    return 0;
}
