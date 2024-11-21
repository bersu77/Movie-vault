#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// Function to write a string to a file
void write_TO_FILE(string& content) {
    ofstream file("password.txt");
    if (!file) {
        cerr << "Unable to open file";
        return;
    }
    file << content;
    file.close();
}

int main() {
    // Ask the user for a password
    string password;
    cout << "Enter your password: ";
    cin >> password;

    // Write the password to the file
    write_TO_FILE(password);

    cout << "Password saved successfully!\n";

    return 0;
}
