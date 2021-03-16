//Author: Owen Senowitz
// Program to implement a phone directory

#include <iostream>

using namespace std;

const int NAMESIZE = 20;    // Maximum size for a name
const int PHONESIZE = 13;    // Maximum size for a phone number
const int CAPACITY = 10;    // Maximum capacity for the directory

// Structure used to define a phone directory entry
struct PDEntry {
	char name[NAMESIZE];
	char phone[PHONESIZE];
};

/*
* Prints out the entire directory to the screen
* dir = directory to be printed
* usedSize = number of entries in the directory
*/
void printDirectory(const PDEntry dir[], int usedSize);

/*
* Adds a new entry to the directory
* dir = directory in which the entry is to be added
* usedSize = number of entries in the directory
* nm = name to be added
* ph = phone number to be added
* Returns true if entry was able to be added, and false if there's no room in
* the directory to add any new entries. If the entry was added, usedSize will
* reflect the updated number of entries in the directory
*/
bool addEntry(PDEntry dir[], int& usedSize, const char nm[], const char ph[]);


/*
* Updates a single phone directory entry
* entry = the directory entry to be updated
* nm = name to change the entry to
* ph = phone number to change the entry to
* Upon completion, entry will be changed to the new phone number
*/
void updateEntry(PDEntry& entry, const char nm[], const char ph[]);


/*
* Gets a name and number from the user.  If the name already exists in the
* directory, the entry will be updated with the new number.  If the name is
* not already in the directory, a new entry will be added if there is room
* in the directory to add the name.
* dir = directory in which the entry is to be added/changed
* usedSize = number of entries in the directory
* If the entry was added, usedSize will
* reflect the updated number of entries in the directory
*/
void doAddChangeEntry(PDEntry dir[], int& usedSize);

/*
* Gets a name from the user.  If the name exists in the
* directory, the entry will deleted.
* dir = directory from which the entry should be removed
* usedSize = number of entries in the directory
* If the entry is deleted, usedSize will
* reflect the updated number of entries in the directory
*/
void removeEntry(PDEntry dir[], int& usedSize);

/*
* Searches a directory to try to find a specified name.
* dir = directory to be searched
* usedSize = number of entries in the directory
* nm = name to search for
* If the entry is found, the position number of where the name
* is stored in the directory will be returned.  If the entry is
* not found, the value -1 will be returned instead.
*/
int find(const PDEntry dir[], int usedSize, const char nm[]);

int main() {
	PDEntry dir[CAPACITY];
	int choice, usedSize = 0;

	/*
	Add a couple of starter entries for testing purposes
	Change usedSize = to number of entries
	*/
	addEntry(dir, usedSize, "John Doe", "252-555-1212");
	addEntry(dir, usedSize, "Jane Doe", "252-555-1313");

	do {
		cout << "1. Add/Change Entry\n";
		cout << "2. Print Directory\n";
		cout << "3. Remove Entry\n";
		cout << "4. Exit\n";
		cout << endl;
		cout << "Select: ";

		// Gets the numeric entry from the menu
		cin >> choice;

		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		cin.ignore();

		switch (choice) {
		case 1:
			doAddChangeEntry(dir, usedSize);
			break;
		case 2:
			printDirectory(dir, usedSize);
			break;
		case 3:
			removeEntry(dir, usedSize);
			break;

		}

	} 
	
	while (choice != 4);

	return 0;

}

int find(const PDEntry dir[], int usedSize, const char nm[]) {
	// TODO: Add the find code
	// Added the find function to find an entry in the phone directory
	for (int i = 0; i < usedSize; i++) {

		if (strcmp(nm, dir[i].name) == 0) {

			return i;

		}

	}

	return -1;

}


void removeEntry(PDEntry dir[], int& usedSize) {
	// TODO: Add the remove Entry code
	char name[NAMESIZE];

	printDirectory(dir, usedSize);

	cout << "Enter name: ";
	cin.getline(name, NAMESIZE);

	int arrayPos = find(dir, usedSize, name);

	/*
	An if else statement and for loop to delete a name or say if a name
	could not be found in the phone direectory
	*/
	if (arrayPos >= 0) {
		for (int i = arrayPos; i < usedSize - 1; i++) {

			dir[i] = dir[i + 1];
		}

		usedSize -= 1;

		cout << "Entry was deleted.\n";
	}

	else {

		cout << "Entry was not found." << endl;

	}

}

void doAddChangeEntry(PDEntry dir[], int& usedSize) {
	// TODO: Add the doAddChangeEntry code
	char nameNew[NAMESIZE], phoneNew[PHONESIZE];

	cout << "Enter name: ";
	cin.getline(nameNew, NAMESIZE);

	cout << "Enter number: ";
	cin.getline(phoneNew, PHONESIZE);

	int findTest = find(dir, usedSize, nameNew);

	//Uses a if else statement to add and update the phone directory
	if (findTest == -1) {
		if (usedSize >= CAPACITY) {

			printf("\nError: Directory is full.\n");

		}

		else {

			addEntry(dir, usedSize, nameNew, phoneNew);
			printf("\nEntry was added.\n");

		}

	}

	else {

		updateEntry(dir[findTest], nameNew, phoneNew);
		printf("\nEntry was updated.\n");

	}

}

bool addEntry(PDEntry dir[], int& usedSize, const char nm[], const char ph[]) {
	// TODO: Add the addEntry code
	//Uses a if staement to add to the phone directory
	if (usedSize < CAPACITY) {

		updateEntry(dir[usedSize], nm, ph);
		usedSize++;

		return true;
	}

	return false;
}

void updateEntry(PDEntry& entry, const char nm[], const char ph[]) {
	// TODO: Add the updateEntry code
	// Updates the phone directory with a new name and phone number
	snprintf(entry.name, sizeof(entry.name), nm);
	snprintf(entry.phone, sizeof(entry.phone), ph);

}

void printDirectory(const PDEntry dir[], int usedSize) {
	// TODO: Add the printDirectory code
	// Prints the directory of the phone directory
	cout << "Directory:\n";
	cout << "\n";

	for (int x = 0; x < usedSize; x++) {

		printf("\t%s", dir[x].name);
		printf("   %.3s-%.3s%-.5s\n", dir[x].phone, dir[x].phone + 4, dir[x].phone + 7);
	}

	printf("\n");

}