#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    string emailAddress;
    string notes;
    string group;
    string birthday;
};

vector<Contact> contacts;
const string FILE_NAME = "Contacts.Save";

// Save contacts to file
void saveContacts(const string& filename = FILE_NAME) {
    ofstream file("Contacts.Save");
    if (file.is_open()) {
        for (size_t i = 0; i < contacts.size(); ++i) {
    const Contact& contact = contacts[i];
    file << contact.name << "," << contact.phoneNumber << "," << contact.emailAddress << "," << contact.notes << "," << contact.group << "," << contact.birthday << endl;
}
        file.close();
        cout << "Contacts saved successfully.\n";
    } else {
        cout << "Unable to save contacts to file.\n";
    }
}

// Load contacts from file
void loadContacts(const string& filename = FILE_NAME) {
    ifstream file("Contacts.Save");
    if (file.is_open()) {
        contacts.clear();
        string line;
        while (getline(file, line)) {
            Contact contact;
            size_t pos = 0;
            pos = line.find(",");
            contact.name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            contact.phoneNumber = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            contact.emailAddress = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            contact.notes = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            contact.group = line.substr(0, pos);
            line.erase(0, pos + 1);
            contact.birthday = line;
            contacts.push_back(contact);
        }
        file.close();
        cout << "Contacts loaded successfully.\n";
    } else {
        cout << "Unable to load contacts from file.\n";
    }
}

// Function to add a new contact
void addContact() {
	cout << "Please press enter for furtur process." << endl;
    cin.ignore();
    Contact newContact;
    cout << "Enter name: ";
    getline(cin, newContact.name);
    cout << "Enter phone number: ";
    getline(cin, newContact.phoneNumber);
    cout << "Enter email address: ";
    getline(cin, newContact.emailAddress);
    cout << "Enter notes: ";
    getline(cin, newContact.notes);
    cout << "Enter group: ";
    getline(cin, newContact.group);
    cout << "Enter birthday (DD/MM/YYYY): ";
    getline(cin, newContact.birthday);
    contacts.push_back(newContact);
    cout << "Contact added successfully.\n";
}

// Function to view all contacts
void viewContacts() {
    if (contacts.empty()) {
        cout << "No Contacts found" << endl;
        return;
    }
    cout << "Contacts" << endl;
    for (int i = 0; i < contacts.size(); ++i) { 
        cout << "Name: " << contacts[i].name << endl;
        cout << "Phone Number: " << contacts[i].phoneNumber << endl;
        cout << "Email Address: " << contacts[i].emailAddress << endl; 
        cout << "Notes: " << contacts[i].notes << endl;
        cout << "Group: " << contacts[i].group << endl; 
        cout << "Birthday: " << contacts[i].birthday << endl;
    }
}
//Fuction to edit contacts
void editContacts(const string& name) {
    bool found = false;
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].name == name) {
            Contact& contact = contacts[i]; // Get reference to the contact to modify
            cout << "Enter new phone number: ";
            getline(cin, contact.phoneNumber);
            cout << "Enter new email address: ";
            getline(cin, contact.emailAddress);
            cout << "Enter new notes: ";
            getline(cin, contact.notes);
            cout << "Enter new group: ";
            getline(cin, contact.group);
            cout << "Enter new birthday (DD/MM/YYYY): ";
            getline(cin, contact.birthday);
            cout << "Contact updated successfully.\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Contact not found" << endl;
    }
}

// Function to search contacts by name
void searchContactsByName() {
    string searchName;
    cout << "Enter the name to search: ";
    getline(cin, searchName);
    
    bool found = false;
    for (size_t i = 0; i < contacts.size(); ++i) {
        if (contacts[i].name.find(searchName) != -1) {
            const Contact& contact = contacts[i];
            cout << "Name: " << contact.name << endl;
            cout << "Phone Number: " << contact.phoneNumber << endl;
            cout << "Email Address: " << contact.emailAddress << endl;
            cout << "Notes: " << contact.notes << endl;
            cout << "Group: " << contact.group << endl;
            cout << "Birthday: " << contact.birthday << endl;
            cout << "---------------------------" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Contact not found.\n";
    }
}

// Function to delete a contact
void deleteContacts(const string& name) {
    bool found = false;
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].name == name) {
            found = true;

            contacts.erase(contacts.begin() + i); // Remove contact at index i

            cout << "Contact deleted successfully" << endl;
            break;
        }
    }
    if (!found) {
        cout << "Contact not found" << endl;
    }
}

//Function to veiw contacts by group
void viewContactsByGroup(const string& group) {
    if (contacts.empty()) {
        cout << "No contacts found." << endl;
        return;
    }
    cout << "Contacts in Group '" << group << "':" << endl;
   	for (size_t i = 0; i < contacts.size(); ++i) {
    	const Contact& contact = contacts[i];
    	if (contact.group == group) {
            cout << "Name: " << contact.name << endl;
            cout << "Phone Number: " << contact.phoneNumber << endl;
            cout << "Email Address: " << contact.emailAddress << endl;
            cout << "Notes: " << contact.notes << endl;
            cout << "Birthday: " << contact.birthday << endl;
            cout << "---------------------------" << endl;
        }
    }
}

// Function to export contacts to a CSV file
void exportContacts(const string& filename = FILE_NAME) {
    ofstream file("Contacts.Save");
    if (file.is_open()) {
        file << "Name,Phone Number,Email Address,Notes,Group,Birthday\n";
        for (size_t i = 0; i < contacts.size(); ++i) {
    const Contact& contact = contacts[i];
    file << contact.name << "," << contact.phoneNumber << "," << contact.emailAddress << "," << contact.notes << "," << contact.group << "," << contact.birthday << endl;
}
        file.close();
        cout << "Contacts exported to CSV file successfully.\n";
    } else {
        cout << "Unable to export contacts to CSV file.\n";
    }
}

// Function to import contacts 
void importContacts() {
    ifstream file("Contacts.csv");
    if (!file) {
        cout << "Unable to open file.\n"; 
        return;
    }

    vector<Contact> contacts;
    string name, phoneNumber, emailAddress, notes, group, birthday;
    getline(file, name);
    while (getline(file, name, ',')) { 
        getline(file, phoneNumber, ','); 
        getline(file, emailAddress, ','); 
        getline(file, notes, ','); 
        getline(file, group, ','); 
        getline(file, birthday);

        Contact newContact; 
        newContact.name = name; 
        newContact.phoneNumber = phoneNumber; 
        newContact.emailAddress = emailAddress; 
        newContact.notes = notes; 
        newContact.group = group; 
        newContact.birthday = birthday; 
        
        contacts.push_back(newContact);
    }

    
    file.close(); 

    cout << "Contacts imported successfully.\n"; 
}

// Function to display bday reminders
void displayBirthdayReminders() {
    for (vector<Contact>::const_iterator it = contacts.begin(); it != contacts.end(); ++it) {
        const Contact& contact = *it; 
        if (!contact.birthday.empty()) {
            cout << "Reminder: " << contact.name << "'s birthday is on " << contact.birthday << "!\n";
        }
    }
}

int main() {
    int choice;
    string name;

    do {
        cout << "\nContact Management System\n";
        cout << "---------------------------\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Export Contacts\n";
        cout << "6. Import Contacts\n";
        cout << "7. View Contacts by Group\n";
        cout << "8. Search Contacts by Name\n";
        cout << "9. View Birthday Reminders\n";
        cout << "10. Exit\n";
        cout << "----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
           case 3:
    			cout << "Enter the name of the contact to edit: ";
    			getline(cin, name);
    			editContacts(name);
    			break;
            case 4:
                {
                string name;
				cout << "Enter the name of the contact to delete: ";
                getline(cin, name);
                deleteContacts(name);
                }
                break;
            case 5:
                exportContacts();
                break;
            case 6:
                importContacts();
                break;
            case 7:
                {
                string group;
                cout << "Enter the group name: ";
                getline(cin, group);
                viewContactsByGroup(group);
                }
                break;
            case 8:
                searchContactsByName();
                break;
            case 9:
                displayBirthdayReminders();
                break;
            case 10:
                saveContacts(); // Save contacts before exiting
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);

    return 0;
}




