#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fptr=fopen("contacts.txt","w");//The write mode before everyone is deleted wrote it new. 
    fprintf(fptr,"#%d\n",addressBook->contactCount);//skip that the value of the file
    //list all contact save in the the one file
    for(int i=0;i<addressBook->contactCount;i++)
    {
            fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);  
}
//if is read only contact take the the list contact exit after 
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fptr=fopen("contacts.txt","r");//it is program is exit it is stored  in the read mode
    if(fptr==NULL)//file is empty not possible to read
    {
        printf("No exisiting contact file\n");
        return;
    }
    fscanf(fptr,"#%d\n",&addressBook->contactCount);//it is an firstly declared count of the address book contact

    for(int i=0;i<addressBook->contactCount;i++)
    {
//it is an skip that comma name and phone and loaded information
        fscanf(fptr," %[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);

}
