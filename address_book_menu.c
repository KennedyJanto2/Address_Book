#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"
//#include "abk.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	int found = 0;
	ContactInfo contact;
	switch(field){
		case 1://search by name
			for(int i = 0; i < address_book->count; i++){
				ContactInfo contact = address_book->list[i];

				for(int k = 0; k < NAME_COUNT; k++){
					if(strcmp(str, &contact.name[k][0]) == 0)// check name
					{
						found = 1;
						k = NAME_COUNT;
						i = address_book->count;
						break;
					}
				}
			}
			break;
		case 2://search by phone
			for(int i = 0; i < address_book->count; i++){
				ContactInfo contact = address_book->list[i];

				for(int k = 0; k < PHONE_NUMBER_COUNT; k++){
					if(strcmp(str, &contact.phone_numbers[k][0]) == 0)// check phone number
					{
						found = 1;
						k = NAME_COUNT;
						i = address_book->count;
						break;
					}
				}
			}
			break;
		case 3://search by email
			for(int i = 0; i < address_book->count; i++){
				ContactInfo contact = address_book->list[i];

				for(int k = 0; k < EMAIL_ID_COUNT; k++){
					if(strcmp(str, &contact.email_addresses[k][0]) == 0)// check email id
					{
						found = 1;
						k = NAME_COUNT;
						i = address_book->count;
						break;
					}
				}
			}
			break;
		case 4:
			for(int i = 0; i < address_book->count; i++){
				ContactInfo contact = address_book->list[i];

					if(loop_count == contact.si_no) //check serial number
					{
						found = 1;
						i = address_book->count;
						break;
					}
			}
			break;
		default:
			break;
	}

	//printing results
	menu_header("Search Results: ");
	if(found == 0){
		printf("Contact was not found.\n");
	}
	printf("==================================================================================================================\n");
	printf(": S.No : Name                          : Phone No                          : Email ID                          \n:");
	printf(": %-5i : %-20s : %-20i : %-20s :\n", contact.si_no, &contact.name[0][0], &contact.phone_numbers[0][0], &contact.email_addresses[0][0]);
	printf(":      :                               : %-20i : %-20s :\n", &contact.phone_numbers[0][1], &contact.email_addresses[0][1]);
	printf(":      :                               : %-20i : %-20s :\n", &contact.phone_numbers[0][2], &contact.email_addresses[0][2]);
	printf(":      :                               : %-20i : %-20s :\n", &contact.phone_numbers[0][3], &contact.email_addresses[0][3]);
	printf(":      :                               : %-20i : %-20s :\n", &contact.phone_numbers[0][4], &contact.email_addresses[0][4]);
	printf("==================================================================================================================\n");
}

Status search_contact(AddressBook *address_book)
{
	int option;
	char searchWord;

	do{
		menu_header("Search Contact by: ");
		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone No\n");
		printf("3. Email ID\n");
		printf("4. Serial No\n");
		printf("\n");
		printf("Please select an option: ");
		
		option = get_option(NUM, "");
		if((address_book-> count == 0) && (option != e_first_opt))
		{
			get_option(NONE, "No entries found!");
		}

		switch(option){
			case e_back://back
				option = e_exit;
				break;
			case e_second_opt://name
				printf("Enter the Name: ");
				scanf("%s", searchWord);
				search(searchWord, address_book, address_book-> count, 1, searchWord, e_search);
				break;
			case e_third_opt://phone number
				printf("Enter the Phone Number: ");
				scanf("%s", searchWord);
				search(searchWord, address_book, address_book-> count, 2, searchWord, e_search);
				break;
			case e_fourth_opt://email ID
				printf("Enter the Email ID: ");
				scanf("%s", searchWord);
				search(searchWord, address_book, address_book-> count, 3, searchWord, e_search);
				break;
			case e_fifth_opt://Serial number
				printf("Enter the Serial No: ");
				scanf("%s", searchWord);
				search(searchWord, address_book, address_book-> count, 4, searchWord, e_search);
				break;
			case e_no_opt://no option
				break;
		}

	}while(option != e_exit);

	return e_success;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
