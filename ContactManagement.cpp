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

// Function to check if the entered username and password are correct
bool authenticateUser(const string& username, const string& password) {
    ifstream file("users.txt");
    string storedUsername, storedPassword;
    while (file >> storedUsername >> storedPassword) {
        if (username == storedUsername && password == storedPassword) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
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
        cerr << "Error: Unable to save contacts to file.\n";
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
        cerr << "Error: Unable to load contacts from file.\n";
    }
}

// Function to add a new contact
void addContact() {
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
        cerr << "Error: Unable to export contacts to CSV file.\n";
    }
}

// Function to import contacts 
void importContacts() {
    ifstream file("Contacts.csv");
    if (!file) {
        cerr << "Error: Unable to open file.\n"; 
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
    bool authenticated = false; // Flag to track user authentication

    cout << "Contact Management System\n";
    cout << "1. Save Contacts\n";
    cout << "2. Authenticate User\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); 
    cout << "-------------------" << endl;
    cout << "Please press Enter for futhur process: ";

    if (choice == 1) {
        addContact(); 
        saveContacts(); 
    } else if (choice == 2) {
        string username, password;

        cout << "\nLogin\n";
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        authenticated = authenticateUser(username, password);

        if (authenticated) {
            cout << "Authentication successful. Welcome, " << username << "!\n";
        } else {
            cout << "Authentication failed. Exiting program.\n";
            return 0;
        }
    } else {
        cout << "Invalid choice.\n";
        return 0; 
    }

    do {
        cout << "\nContact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Delete Contact\n";
        cout << "4. Export Contacts\n";
        cout << "5. Import Contacts\n";
        cout << "6. View Birthday Reminders\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                if (authenticated) {
                    addContact();
                } else {
                    cout << "Please authenticate first.\n";
                }
                break;
            case 2:
                viewContacts();
                break;
            case 3:
    			{
        		string name;
        		cout << "Enter the name of the contact to delete: ";
        		getline(cin, name);
        		deleteContacts(name);
    			}
    			break;
            case 4:
                if (authenticated) {
                    exportContacts();
                } else {
                    cout << "Please authenticate first.\n";
                }
                break;
            case 5:
                if (authenticated) {
                    importContacts();
                } else {
                    cout << "Please authenticate first.\n";
                    }
                break;
            case 6:
                displayBirthdayReminders();
                break;
            case 7:
                if (authenticated) {
                    saveContacts(); // Save contacts before exiting
                }
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}


