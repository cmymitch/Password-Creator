#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include "Color.h"
using namespace std;

void welcome() 
{
    // Display welcome message
    cout << dye::aqua("#############################################\n"
                      "#   Welcome to the password creation tool!  #\n"
                      "#          Cameron Mitchell (2309227)       #\n"
                      "#             Abertay University            #\n"
                      "#############################################\n");

    Sleep(3000); // Time delay
    system("cls"); // Clear terminal
}

// Get user to enter a password
string getPassword()
{
    string originalPassword = "";
    cout << dye::red("WARNING! PASSWORD ENTERED WILL BE VISIBLE AND NOT HIDDEN!"); // Display red warning that password will be visible
    cout << "\n\n\nPlease enter password: "; cin >> originalPassword; // Ask user to enter a password
    system("cls");
    return originalPassword;
}

string addWords(string oldPassword)
{
    //https://www.geeksforgeeks.org/how-to-read-from-a-file-in-cpp/?ref=ml_lbp
    //https://www.w3schools.com/cpp/cpp_howto_random_number.asp
    ifstream file("word.txt");

    int times = 0;
    while (times < 2) {
        int number = rand() % 1000;  // Random number between 0 and 999 (for 1000 lines)
        string word = "";

        // Reset the file pointer to the beginning of the file
        file.clear();
        file.seekg(0, ios::beg);

        // Skip to the random line (based on the random number)
        for (int i = 0; i < number; ++i) {
            getline(file, word);  // Read each line until we reach the random line
        }

        // Append the word to the oldPassword
        oldPassword += "-" + word;

        times += 1;
    }
    file.close();
    return oldPassword;
}

string addDigits(string oldPassword)
{
    for (int i = 0; i <= 2; i++)
    {
        int randomINT = rand() % 10;
        int randomPOS = rand() % oldPassword.length();
        char c = '0' + randomINT; // https://www.tek-tips.com/threads/convert-from-int-to-char.1088107/
        oldPassword.insert(randomPOS, 1, c);
    }
 
    return oldPassword;
}

string addSymbols(string oldPassword)
{
    string randomSymbols = "!$%^&*()[{]}#~@;:/?.>,<|";

    for (int i = 0; i <= 2; i++)
    {
        int randomINT = rand() % randomSymbols.length();
        char randomChar = randomSymbols[randomINT];
        int randomPOS = rand() % oldPassword.length();
      
        oldPassword.insert(randomPOS, 1, randomChar);
    }
    return oldPassword;
}

string complexifyPasswordmenu(string originalPassword)
{
    int choice = 0;
    bool exit = false;
    string newPassword = "";
    while (!exit)
    {
        // Display menu options
        system("cls");
        cout << dye::blue("Your original password: " + originalPassword);
        cout << "\n\n\n";
        cout << "Please select an option below to make your password more secure:\n";
        cout << "1. Add 2 random words (low security)\n";
        cout << "2. Add random words and some digits. (Medium security)\n";
        cout << dye::green("3. Add all of the above and symbols. (Recommended)\n");
        cout << "Please enter your choice (1 - 3): ";
        cin >> choice;

        // Add in check to see if entered choice is a number and is in range

        if (choice <= 3 && choice >= 1)
        {
            exit = true;
        }
    }
    
    // switch statement to call functions
    switch(choice)
    {
        case 1: 
            // Call function
            newPassword = addWords(originalPassword);
            break;
        case 2:
            // Call function
            newPassword = addDigits(addWords(originalPassword));
            break;
        case 3:
            // Call function
            newPassword = addSymbols(addDigits(addWords(originalPassword)));
            break;
        default:
            break;
    }
   
    system("cls");
    return newPassword;
}

void displaynewPassword(string newPassword)
{
    cout << dye::green("Your new password is: " + newPassword) << endl;
    system("pause");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(0)); // Seed the random number with the time.
    welcome(); // Display welcome message
    displaynewPassword(complexifyPasswordmenu(getPassword())); // Run program
    return 0;
}
