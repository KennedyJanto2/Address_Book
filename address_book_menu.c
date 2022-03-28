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
	if (type == CHAR) // for csv file "save" feature, read character
	{
		return fgetc(stdin);
	}
	else if (type == NUM)
	{
		int on;
		scanf("%i", &on); // User Input, read number
		return on;
	}
	else
	{
		fgetc(stdin);
		return -1;
	}
}

MenuFeatures menu_option() // Feature Menu for Corressponding Number Selection
{
	switch (get_option(NUM, "")) // Menu Option Input from integer input to associated function
	{
	case 0:
		return e_exit;
	case 1:
		return e_add_contact;
	case 2: 
		return e_search_contact;
	case 3:
		return e_edit_contact;
	case 4:
		return e_delete_contact;
	case 5:
		return e_list_contacts;
	case 6:
		return e_save;
	}
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
	int option;
	int loc = *index;

	menu_header("All Contacts: ");
	printf("(Page %d of %d):\n", (index+1), (address_book->count));

		printf("===============================================================================================================\n");
		printf(": S.No  : Name                            : Phone No                        : Email ID                        :\n");
		printf("===============================================================================================================\n");

		printf(": %d", address_book->list[loc].si_no);
		if (address_book->list[loc].si_no < 10) 
		{
			for (int i = 0; i < 5; i++)
				printf(" ");
		} 
		else
		{
			for (int i = 0; i < 4; i++)
				printf(" ");
		}
		printf(":%s", &address_book->list[loc].name[0][0]);
		for (int i = 32 - strlen(&address_book->list[loc].name[0][0]); i > 0; i--) 
		{
			printf(" ");
		}

		int PhoneNum = sizeof address_book->list[loc].phone_numbers / sizeof *address_book->list[loc].phone_numbers;
		int phonesPrinted = 0;
		int EmailNum = sizeof address_book->list[loc].email_addresses / sizeof *address_book->list[loc].email_addresses;
		int emailsPrinted = 0;
	
		if (PhoneNum > 0) //more than 1 phone
		{
			printf(":%s", &address_book->list[loc].phone_numbers[0][0]);
			phonesPrinted++;
			for (int i = 32 - strlen(&address_book->list[loc].phone_numbers[0][0]); i > 0; i--)
					printf(" ");
		} 
		else //online 1 phone
		{	
			for (int i = 32 ; i > 0; i--) 
			{
				printf(" ");
			}
		}

		if (EmailNum > 0) //more than 1 email
		{
			printf(":%s", &address_book->list[loc].email_addresses[0][0]);
			emailsPrinted++;
			for (int i = 32 - strlen(&address_book->list[loc].email_addresses[0][0]); i > 0; i--)
				printf(" ");
		} 
		else //only 1 email
		{ 
			for (int i = 32 ; i > 0; i--) 
			{
				printf(" ");
			}
		}
		printf(":\n");

		for (int i = 0; i < 4; i++)
		{
			printf(":      :                                ");

			if (phonesPrinted < PhoneNum) {
				printf(":%s", &address_book->list[loc].phone_numbers[phonesPrinted][0]);
				for (int m = 32 - strlen(&address_book->list[loc].phone_numbers[phonesPrinted][0]); m > 0; m--){
					printf(" ");
				}
				phonesPrinted++;
			} 
			else{
				for (int n = 32 ; n > 0; n--){
					printf(" ");
				}	
			}
				
			if (emailsPrinted < EmailNum) 
			{
				printf(":%s", &address_book->list[loc].email_addresses[emailsPrinted][0]);
				for (int l = 32 - strlen(&address_book->list[loc].email_addresses[emailsPrinted][0]); l > 0; l--){
					printf(" ");
				}
				emailsPrinted++;
			} 
			else{
				for (int p = 32 ; p > 0; p--){
					printf(" ");
				}
			}	
			printf(":\n");
		}

		printf("===========================================================================================================\n");

	int pageMove = 0;
	do {
		printf("Exit: [0] | Next Page: [2] | Previous Page: [1]:   ");
		option = get_option(NUM, "");
		printf("%d\n", option);

		if(option == 0) 
		{
			menu(address_book);
		} 
		else if(option == 2) 
		{
			if(loc < (address_book->count-1)) 
			{
				index++;
				list_contacts(address_book, "", index, "", e_list_contacts);
			} 
			else 
			{
				printf("Already on last page.\n");
			}
		} 
		else if(option == 1)
		{
			if (loc > 0) 
			{
				index--;
				list_contacts(address_book, "", index, "", e_list_contacts);
			} 
			else 
			{
				printf("Already on first page.\n");
			}
		}
	} while(pageMove == 0);

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("cls");

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

		//option = get_option(NUM, "");
		option = menu_option();

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				add_contacts(address_book);
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
				list_contacts(address_book, "", 0, "", e_list_contacts);
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
	int opt = 0;
	int phn = 0; 
	int eml = 0;
	ContactInfo ci;
	strncpy(*ci.email_addresses, " ", sizeof(ci.email_addresses));
	do
	{
		menu_header("Add Contact:\n");
		printf("0. Back");
		printf("\n");
		printf("1. Name		: %s", ci.name[0]);
		printf("\n2. Phone No 1	: %s", ci.phone_numbers[0]);
		printf("\n3. Email ID 1	: %s", ci.email_addresses[0]);
		printf("\n\nPlease select an option: ");
		opt = get_option(NUM, "");
		switch (opt)
		{
			case e_first_opt: // Back Option
				menu(address_book); // Back to Menu
				break;
			case e_second_opt: // Name Option
				printf("Enter name: ");
				scanf("%s", &ci.name[0][0]); // Name Input
				break;
			case e_third_opt: // Phone Number Option
//				printf("AT PHONE NUMBER");
				if (phn < PHONE_NUMBER_COUNT)
				{
					printf("Enter Phone Number %d: [Please reenter the same option of alternate Phone Number]: ", phn + 1);
					scanf("%s", &ci.phone_numbers[phn][0]); // Phone Number Input
					phn++;
				}
				else
				{
					printf("Maximum Phone Number Amount. Press ENTER: ");
					getchar();
				}
				break;
			case e_fourth_opt: // Email Option
// 				printf("AT EMAIL");
				if (eml < EMAIL_ID_COUNT)
				{
					printf("Enter Email ID %d: [Please reenter the same option of the alternate Email ID]: ", eml + 1);
					scanf("%s", &ci.email_addresses[eml][0]); // Email Input
					eml++;
				}
				else
				{
					printf("Maximum Email Amount. Press Enter: ");
					getchar();
				}
				break;
			}
			getchar();
		} while (opt != 0);
		ci.si_no = address_book->count + 1;
		address_book->list[address_book->count] = ci;
		address_book->count++;
		return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	ContactInfo contact;
	int found = 0;
	
	switch(field)
	{
		case 1://search by name
			for(int i = 0; i < address_book->count; i++)
			{
				ContactInfo contact = address_book->list[i];

				for(int k = 0; k < NAME_COUNT; k++)
				{
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
			for(int i = 0; i < address_book->count; i++)
			{
				ContactInfo contact = address_book->list[i];

				for(int k = 0; k < PHONE_NUMBER_COUNT; k++)
				{
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
			for(int i = 0; i < address_book->count; i++)
			{
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
			for(int i = 0; i < address_book->count; i++)
			{
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

	//printing output
	menu_header("Search Results: ");
	if(found == 0){
		printf("\nContact was not found.\n");
		return e_no_match;
	}
	else{
		printf("===============================================================================================================\n");
		printf(": S.No  : Name                            : Phone No                        : Email ID                        :\n");
		printf("===============================================================================================================\n");
		printf(":%d", contact.si_no);
		if (contact.si_no < 10)
		{
			for (int i = 0; i < 5; i++)
				printf(" ");
		}
		else
		{
			for (int i = 0; i < 4; i++)
				printf(" ");
		}
		printf(": %s", &contact.name[0][0]);
		for (int i = 32 - strlen(&contact.name[0][0]); i > 0; i--)
		{
			printf(" ");
		}

		int PhoneNum = sizeof contact.phone_numbers / sizeof *contact.phone_numbers;
		int EmailNum = sizeof contact.email_addresses / sizeof *contact.email_addresses;
		int phonesPrinted = 0;
		int emailsPrinted = 0;

		if (PhoneNum > 0)
		{
			printf(":%s", &contact.phone_numbers[0][0]);
			phonesPrinted++;
			for (int i = 32 - strlen(&contact.phone_numbers[0][0]); i > 0; i--)
				printf(" ");
		}
		else
			for (int i = 32 ; i > 0; i--)
				printf(" ");

		if (EmailNum > 0)
		{
			printf(":%s", &contact.email_addresses[0][0]);
			emailsPrinted++;
			for (int i = 32 - strlen(&contact.email_addresses[0][0]); i > 0; i--)
				printf(" ");
		}
		else
			for (int i = 32 ; i > 0; i--)
				printf(" ");
		printf(":\n"); 

		for (int k = 0; k < 4; k++)
		{
			printf(":      :                                ");

			if (phonesPrinted < PhoneNum)
			{
				printf(":%s", &contact.phone_numbers[phonesPrinted][0]);
				for (int m = 32 - strlen(&contact.phone_numbers[phonesPrinted][0]); m > 0; m--)
					printf(" ");
				phonesPrinted++;
			}
			else
				for (int n = 32 ; n > 0; n--)
					printf(" ");

			if (emailsPrinted < EmailNum)
			{
				printf(":%s", &contact.email_addresses[emailsPrinted][0]);
				for (int l = 32 - strlen(&contact.email_addresses[emailsPrinted][0]); l > 0; l--)
					printf(" ");
				emailsPrinted++;
			}
			else
				for (int p = 32 ; p > 0; p--)
					printf(" ");
			printf(":\n");
		}

		printf("===========================================================================================================\n");
		return e_success;
	}
	
}

Status search_contact(AddressBook *address_book)
{
	int option;
	char searchWord[NAME_LEN];

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
				search(searchWord, address_book, address_book-> count, 1, "", e_search);
				break;
			case e_third_opt://phone number
				printf("Enter the Phone Number: ");
				scanf("%s", searchWord);
				search(searchWord, address_book, address_book-> count, 2, "", e_search);
				break;
			case e_fourth_opt://email ID
				printf("Enter the Email ID: ");
				scanf("%s", searchWord);
				search(searchWord, address_book, address_book-> count, 3, "", e_search);
				break;
			case e_fifth_opt://Serial number
				printf("Enter the Serial No: ");
				scanf("%s", searchWord);
				search(searchWord, address_book, address_book-> count, 4, "", e_search);
				break;
			case e_no_opt://no option
				break;

			default:
				printf("\nIncorrect input.");
				return e_back;
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
