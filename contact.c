#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
#include <ctype.h>
//Function to validate a NAME
int validateName(const char *name)
{
    int i;
    for(i=0;name[i]!=0;i++)
    {
        if(!(('A'<=name[i]&&name[i]<='Z')||('a'<=name[i]&&name[i]<='z')))//it is condition not in alpahbets not validate
        {
            return 0;
        }
    }
    return 1;
}
//function to validate a NUMBER
int validatePhone(const char *phone)
{
    int i;
    for(i=0;phone[i]!=0;i++)
    {
        if('0'>phone[i]||phone[i]>'9')//it is only validate number 
        {
            return 0;
        }
    }
    if(i!=10)//it is take 10 number only validate
    {
    return 0;
    }
    return 1;
}
//function to validate a EMAIL
int validateEmail(const char *email)
{
    const char *at=strchr(email,'@');//only present in the '@' gmail only vailidate 
    const char *dot=strrchr(email,'.');
    if(!at||!dot)//if there not any one is present not validate
    {
         return 0;
    }
    if(at>dot)//
    {
        return 0;
    }
    if(strchr(email,' '))//no spaces 
    {
        return 0;
    }
    if(strlen(email)<6)//length of the string minimam 6 letters
    {
        return 0;
    }
    //'@gmail' only validate
        if(strcmp(at,"@gmail.com")!=0&&strcmp(at,"@gmail.org")!=0&&strcmp(at,"@gmail.net")!=0&&strcmp(at,"@gmail.in")!=0)
        {
            return 0;
        }
    
    return 1;
}
//List the all contacts
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    for(int i=0;i<addressBook->contactCount;i++)
    {
        for(int j=i+1;j<addressBook->contactCount;j++)
        {
            //list the contact only alphabets aranged
            if(strcasecmp(addressBook->contacts[i].name,addressBook->contacts[j].name)>0)
            {
                Contact temp;
                temp=addressBook->contacts[i];
                addressBook->contacts[i]=addressBook->contacts[j];
                addressBook->contacts[j]=temp;
            }
        }
    }
    printf("Total count=%d\n",addressBook->contactCount);//the count of the contact 
    if(addressBook->contactCount==0)//no contacts present in the file
    {
        printf("\nNo contact found!\n");
        return;
    }
    printf("\n-----------------contactlist-----------------------------\n");
    printf("%-5s %-20s %-15s %-30s\n","S.NO","NAME","PHONE","EMAIL");
    printf("----------------------------------------------------------\n");
    int i;
    for(i=0;i<addressBook->contactCount;i++)//list the contacts in dispaly it
    {
        printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        printf("----------------------------------------------------------\n");
    }
    printf("Total count=%d\n",addressBook->contactCount);//count contact display it
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

 void saveAndExit(AddressBook *addressBook) {
     saveContactsToFile(addressBook); // Save contacts to file

     exit(EXIT_SUCCESS); // Exit the program
}
//CREATE A CONTACT
void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount>=MAX_CONTACTS)//contact book reached maximam create contact is not possible 
    {
        printf("Address book full\n");
        return;
    }
    Contact newContact;//it is create contact so strruct name change newcontact
    int t;
    printf("How many contacts you want to create:\n");
    scanf("%d",&t);
    int k=1;
    //CREATE NAME
    while(k<=t)//how many contact you want to create based this condition
    {
    do
    {
    printf("Enter name(min 3 letters,only alphabets&spaces&dots):");
    scanf(" %[^\n]",newContact.name);
    if(validateName(newContact.name)==0)//call the function validate or not name
    {
        printf("Invalid name.Try again\n");
    }
	}while(validateName(newContact.name)==0);//it is not validate again and again take name
    //CREATE PHONENUMBER
    int flag;
    do
    {
        flag=0;
    printf("Enter phonenumber(only 10 digits,only numbers&unique):");
    scanf("%s",newContact.phone);
    if(validatePhone(newContact.phone)==0)//call the function validate or not phonenumber
    {
        printf("Invalid phonenumber.Try again\n");
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,newContact.phone)==0)
        {
         printf("Error:phone number already exists!\n");
         flag=1;
         //break;
         }
        }
	}while(validatePhone(newContact.phone)==0||flag==1);//the condition check valiate or duplicate or not phone number
    //CREATE EMAIL
     do
    {
        flag=0;
    printf("Enter the email id(must @,.com,onlylowercase,numbers is valid,start with lowercase):\n");
    scanf("%s",newContact.email);
    if(validateEmail(newContact.email)==0)//call the function validate or not email
    {
        printf("Invalid email format.Try again\n");
        
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,newContact.email)==0)
        {
         printf("Error:Email already exists!\n");
         flag=1;
        }

	}
}while(validateEmail(newContact.email)==0||flag==1);//the condition check valiate or duplicate or not phone number
    addressBook->contacts[addressBook->contactCount++]=newContact;//The contact is add to the list
    printf("%d Contact added successfully!\n",k);
    k++;
}
}
//SEARCH THE CONTACT
 int searchContact(AddressBook *addressBook) 
 {
    if(addressBook->contactCount==0)//no contact is present no search 
    {
        printf("no contacts are available to search\n");
        return 0;
    }
    int schoice,k;
    char query[50];
    while(1)
    {
     printf("search by\n");
     printf("1.NAME\n2.PHONE\n3.MAIL\n4.EXIT\n");
     printf("Enter the search choice:\n");
     scanf("%d",&schoice);
    //   if(!isdigit(schoice))
    //     {
    //         printf("Invalid input.only choice using number only");
    //         return 0;
    //     }
    switch(schoice)
    {
        //NAME to search contact
        case 1:
        {
            printf("enter the name to search:");
            scanf(" %[^\n]",query);
           int found=0;
           int s;
           int count=0;
        printf("\n-----------------contactlist-----------------------------\n");
        printf("%-5s %-20s %-15s %-30s\n","S.no","NAME","PHONE","EMAIL");
          printf("----------------------------------------------------------\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {    
        if(strcasecmp(addressBook->contacts[i].name,query)==0)
        {
         printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        printf("----------------------------------------------------------\n");
        found=1;
        count++;
        k=i;
        }
    }
    if(found==0)//search a contact name not present in the name
    {
       printf("The name is not matched\n");
       break;
    } 
    if(count==1)
    {
    return k;//one contact is name unique name
    }
    if(count>1)//The contdtion is greater than one contact same NAME
    {
        //two or more contact  
        printf("enter the serial no:\n");
        scanf("%d",&s);
        for(int i=0;i<addressBook->contactCount;i++)
        {
        if(i==s)//serial number is check same diaplay it
        {
             printf("\n-----------------contactlist-----------------------------\n");
        printf("%-5s %-20s %-15s %-30s\n","S.NO","NAME","PHONE","EMAIL");
          printf("----------------------------------------------------------\n");
           printf("%-5d %-20s %-15s %-30s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email); 
            printf("----------------------------------------------------------\n");
            return i;
        }
    }
}
    break;
    }
    //PHONE NUMBER to search contact
    case 2:
        {
            printf("enter the phone number to search:");
            scanf("%s",query);
        for(int i=0;i<addressBook->contactCount;i++)
        {    
        if(strcasecmp(addressBook->contacts[i].phone,query)==0)//check phone number is matched or not 
        {
         printf("\n-----------------contactlist-----------------------------\n");
        printf("%-5s %-20s %-15s %-30s\n","S.NO","NAME","PHONE","EMAIL");
          printf("----------------------------------------------------------\n");
          printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        printf("----------------------------------------------------------\n");
        return i;//search the contact datail is return depends phone number
        }
    }
    printf("The number is not matched\n");
    break;
    }
    case 3:
        {
            printf("enter the email to search:");
            scanf("%s",query);
        for(int i=0;i<addressBook->contactCount;i++)
        {    
        if(strcasecmp(addressBook->contacts[i].email,query)==0)//check email is matched or not 
        {
         printf("\n-----------------contactlist-----------------------------\n");
        printf("%-5s %-20s %-15s %-30s\n","S.NO","NAME","PHONE","EMAIL");
          printf("----------------------------------------------------------\n");
          printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        printf("----------------------------------------------------------\n");
        return i;//search the contact datail is return depends email
        }
    }
    printf("The email is not matched\n");
    break;
    }
    case 4:
    {
        return 0; //exit to the searh contact
    }
    default:
    {
        printf("Invalid input");
        return 0;
    }
    }
}  
 }
 /* Define the logic for Editcontact */
 void editContact(AddressBook *addressBook,int i)
 {
    int choice;
        printf("which want to Edited  by\n");
     printf("1.NAME\n2.PHONE\n3.MAIL\n");//
     printf("Enter the edited choice:\n");
     scanf("%d",&choice);
     switch(choice)
     {
     case 1:
     {
        char namestr[50];
        do
        {
     printf("enter the editing name:\n");
     scanf(" %[^\n]",namestr);
     if(validateName(namestr)==0)//it is check validate or not in name
     {
        printf("Invalid name.Try again\n");
     }
     strcpy(addressBook->contacts[i].name,namestr);//strcpy edited to the name particular name
     }while(validateName(namestr)==0);
     printf("Name update succesflully");
     break;
    }
    case 2:
    {
        char phonestr[50];
        do
        {
     printf("enter the editing phonenumber:\n");
     scanf("%s",phonestr);
     if(validatePhone(phonestr)==0)//it is check validate or not in phone
     {
        printf("Invalid name.Try again\n");
     }
     }while(validatePhone(phonestr)==0);
     strcpy(addressBook->contacts[i].phone,phonestr);//strcpy edited to the  particular phone 
     printf("phone number update succesflully");
     break;
    }   
    case 3:
     {
        char emailstr[50];
        do
        {
     printf("enter the editing email:\n");
     scanf("%s",emailstr);
     if(validateEmail(emailstr)==0)//it is check validate or not in email
     {
        printf("Invalid name.Try again\n");
     }
    }while(validateEmail(emailstr)==0);
    strcpy(addressBook->contacts[i].email,emailstr);//strcpy edited to the  particular email
    printf("email update succesflully");
     break;
     }
     default:
     {
        printf("Invalid input");
        return;
     }
    }
    /* Define the logic for Editcontact */
 }

 void deleteContact(AddressBook *addressBook,int i)
{
char choice;
    printf("Are you sure to delete(Y/N):\n");//if that want to which person delete the contact
    scanf(" %c",&choice);
    if((choice=='y')||(choice=='Y'))
    {
        for(int j=i;j<addressBook->contactCount;j++)//search contact which contact deleted
        {
            addressBook->contacts[j]=addressBook->contacts[j+1];//it is push that in array strcture deleted it
        }
        addressBook->contactCount--;
        printf("delted succesflully\n");
    }
    else
    {
        printf("deleted is unsuccesfull");
    }
    }
	/* Define the logic for deletecontact */



