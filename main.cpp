#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
// to upper case function to convert the string to upper case
string toUpperCase(const string &str)
{
    string result = str;
    for (char &c : result)
    {
        c = toupper(c);
    }
    return result;
}
// to lower case  function to convert the string to lower case
string toLowerCase(const string &str)
{
    string result = str;
    for (char &c : result)
    {
        c = tolower(c);
    }
    return result;
}
// substring function to get the substring from a string with a given delimiter and position of the substring;
string subStringer(const string &str, char delim, int pos)
{
    int start = 0;
    int end = str.find(delim);
    vector<string> tokens;
    while (end != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delim, start);
    }
    tokens.push_back(str.substr(start));
    if (pos >= 0 && pos < tokens.size())
    {
        return tokens[pos];
    }
    else
    {
        return ""; // Return an empty string if pos is out of range
    }
}
int main()
{
    // Print welcome message and starting time of the program to the console window
    cout << "=====================================================\n"
         << "*    Welcome to Disease Cases Reporting System!     *\n"
         << "*   *******************************************    *\n"
         << "*                                        *\n"
         << "* It is developed by 'RCA Student Name' as practical* \n"
         << "*   evaluation for the end of Year 3.                      *\n"
         << "=====================================================\n"
         << "Starting Time: " << __DATE__ << " " << __TIME__ << "\n"
         << "Need a help? Type 'help' then press Enter key." << endl;
    // command variable to store the user input
    string command;

    vector<string> tokens;

    // Main program loop
    while (true)
    {
        // Print console prompt
        cout << "console>";

        // Read user input
        getline(cin, command);
        // if command is help we are going to print the help menu to the console window
        if (command == "help")
        {
            cout << "=======================================================\n";
            cout << "*             HELP MENU                                *\n";
            cout << " ======================================================\n";
            cout << "add <location>         : Add a new location\n";
            cout << "delete <location>      : Delete a location\n";
            cout << "record <location> <disease> <cases>  : Record a disease and its cases\n";
            cout << "list locations        : List all existing locations\n";
            cout << "list diseases         : List all existing diseases in locations\n";
            cout << "where <disease>      : Find where disease exists\n";
            cout << "cases <location> <disease>  : Find cases of a disease in a location\n";
            cout << "cases <disease>     : Find total cases of a given disease\n";
            cout << "help                  : Print user manual\n";
            cout << "exit                  : Exit the program\n";
        }
        // if command is add <location>. we are going to save give location
        else if (command.substr(0, 3) == "add")
        {
            string location = toUpperCase(command.substr(4, command.length() - 4));
            // Append location to file
            ofstream Location("locations.txt", ios::app);
            if (Location.is_open())
            {
                // checking if location exists
                ifstream inFile("locations.txt");
                if (!inFile)
                {
                    cout << "Cannot open the file" << endl;
                    return -1; // Return an appropriate value indicating an error
                }
                else
                {
                    Location << location << endl;
                    Location.close();
                    cout << "Location " << location << " is successfully added!" << endl;
                }
            }
            else
            {
                cout << "Failed to open the file." << endl;
            }
        }

        // if commad is list locations
        else if (command == "list locations")
        {
            string myText;
            ifstream MyFile("locations.txt");
            while (getline(MyFile, myText))
            {
                cout << myText << endl;
            }
        }
        // if command is record
        else if (command.substr(0, 6) == "record")
        {
            string disease = command.substr(7, command.length() - 7);
            ofstream Disease("diseases.txt", ios::app);
            if (Disease.is_open())
            {
                Disease << toLowerCase(disease) << endl;
                Disease.close();
            }
        }
        //
        else if (command.substr(0, 5) == "where")
        {
            string disease = command.substr(6, command.length() - 6);
            ifstream inFile("diseases.txt");
            if (!inFile)
            {
                cout << "Cannot open the file" << endl;
                return -1; // Return an appropriate value indicating an error
            }

            string line;
            vector<string> results;
            while (getline(inFile, line))
            {
                if (subStringer(line, ' ', 1) == disease)
                {
                    results.push_back(subStringer(line, ' ', 0));
                }
            }

            if (results.empty())
            {
                cout << "No location with this disease" << endl;
            }
            else
            {
                for (const string &location : results)
                {
                    cout << "[" << location << "]" << endl;
                }
            }
            // if command is list diseases
        }
        else if (command == "list diseases")
        {
            string line;
            vector<string> diseases;
            ifstream myFile("diseases.txt");
            if (!myFile)
            {
                cout << "unable to open the file";
                return -1;
            }
            else
            {

                while (getline(myFile, line))
                {
                    string disease = subStringer(line, ' ', 1);
                    diseases.push_back(disease);
                };
                if (diseases.empty())
                {
                    cout << "No diseases recorded.";
                }
                else
                {
                    for (const string &result : diseases)
                    {
                        cout << toUpperCase(result) << endl;
                    }
                }
            }
        }
        else if (command.substr(0, 5) == "cases" && subStringer(command, ' ', 2) != "")
        {
            // get location
            cout << subStringer(command, ' ', 3) << endl;
            string location = subStringer(command, ' ', 1);
            string locationInLowerCase = toLowerCase(location);
            string disease = subStringer(command, ' ', 2);
            string diseaseToLowerCase = toLowerCase(disease);
            string line;
            ifstream myFile("diseases.txt");
            if (!myFile)
            {
                cout << "Unable to open the file";
                return -1;
            }
            else
            {
                while (getline(myFile, line))
                {
                    if (subStringer(line, ' ', 0) == locationInLowerCase && subStringer(line, ' ', 1) == diseaseToLowerCase)
                    {
                        cout << "Cases of " << toUpperCase(disease) << " at " << toUpperCase(location) << " are: " << subStringer(line, ' ', 2) << endl;
                        // return 1;
                    }
                }
            }
        }
        else if (command.substr(0, 5) == "cases" && subStringer(command, ' ', 2) == "")
        {
            string line;
            int totalCases = 0;
            string disease = subStringer(command, ' ', 1);
            // change disease case
            string diseaseToLowerCase = toLowerCase(disease);
            // open file
            ifstream myFile("diseases.txt");
            if (!myFile)
            {
                cout << "Unable to open file";
                return -1;
            }
            else
            {
                while (getline(myFile, line))
                {
                    if (subStringer(line, ' ', 1) == diseaseToLowerCase)
                    {
                        string caseNumber = subStringer(line, ' ', 2);
                        int num = stoi(caseNumber);
                        totalCases = totalCases + num;
                    }
                }
                cout << "Total cases of '" << toUpperCase(disease) << "' = " << totalCases << endl;
            }
        }
        // Exit program if command is "exit"
        if (command == "exit")
        {
            cout << "Exiting Disease Cases Reporting System." << endl;
            break;
        }
    }
    return 0;
}