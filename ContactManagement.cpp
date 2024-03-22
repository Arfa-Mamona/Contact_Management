#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <map>


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

map<string, string> users;

// Function to initialize users 
void initializeUsers() {
    users["user1"] = "password1";
    users["user2"] = "password2";
}

// Function to authenticate the user or create new
bool authenticateUser() {
    string username, password;
    char choice;
    bool newUser = false;

    cout << "Do you have an existing account? (y/n): ";
    cin >> choice;

    if (choice == 'n' || choice == 'N') {
        cin.ignore();
        cout << "Create a new account:\n";
        cout << "Enter a username: ";
        cin.ignore();
        getline(cin, username);
        cout << "Enter a password: ";
        cin >> password;
        
        users[username] = password; 
        newUser = true;
    } else {
        cout << "Enter username: ";
        getline(cin, username);
        cin.ignore();
        cout << "Enter password: ";
        getline(cin, password);
        cin.ignore();
    }

    // Authenticate the user
    if (users.find(username) != users.end() && users[username] == password) {
        if (newUser) {
            cout << "Account created successfully.\n";
        } else {
            cout << "Authentication successful.\n";
        }
        return true;
    } else {
        cout << "Invalid username or password.\n";
        return false;
    }
}



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
            Contact& contact = contacts[i]; 
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


// Function to export contacts 
void exportContacts(const string& filename = FILE_NAME) {
    ofstream file("Contacts.Save");
    if (file.is_open()) {
        file << "Name,Phone Number,Email Address,Notes,Group,Birthday\n";
        for (size_t i = 0; i < contacts.size(); ++i) {
    const Contact& contact = contacts[i];
    file << contact.name << "," << contact.phoneNumber << "," << contact.emailAddress << "," << contact.notes << "," << contact.group << "," << contact.birthday << endl;
}
        file.close();
        cout << "Contacts exported to file successfully.\n";
    } else {
        cout << "Unable to export contacts to file.\n";
    }
}


// Function to import contacts 
void importContacts() {
    // Authentication
    if (!authenticateUser()) {
        cout << "Authentication failed. Contacts not imported.\n";
        return;
    }
    
    ifstream file("Contacts.Save");
    if (!file) {
        cout << "Unable to open file.\n"; 
        return;
    }

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

    initializeUsers();
    
    do {
        cout << "\nContact Management System\n";
        cout << "---------------------------\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Save Contacts\n";
        cout << "4. Edit Contact\n";
        cout << "5. Delete Contact\n";
        cout << "6. Export Contacts\n";
        cout << "7. Import Contacts\n";
        cout << "8. View Contacts by Group\n";
        cout << "9. Search Contacts by Name\n";
        cout << "10. View Birthday Reminders\n";
        cout << "11. Exit\n";
        cout << "----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
            	saveContacts();
            	break;
           case 4:
    			cout << "Enter the name of the contact to edit: ";
    			getline(cin, name);
    			editContacts(name);
    			break;
            case 5:
                {
                string name;
				cout << "Enter the name of the contact to delete: ";
                getline(cin, name);
                deleteContacts(name);
                }
                break;
            case 6:
                exportContacts();
                break;
            case 7:
                importContacts();
                break;
            case 8:
                {
                string group;
                cout << "Enter the group name: ";
                getline(cin, group);
                viewContactsByGroup(group);
                }
                break;
            case 9:
                searchContactsByName();
                break;
            case 10:
                displayBirthdayReminders();
                break;
            case 11:
                cout << "Exiting Program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);

    return 0;
}






