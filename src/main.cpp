#include <iostream>
#include <string>
#include <algorithm> // For std::find

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::find;
using std::begin;
using std::end;

// The global necessary variables

// necessary booleans
string yes[] = { "yes", "Yes", "YES", "y", "Y" };
string no[] = { "no", "No", "NO", "n", "N" };

// colours
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define RESET "\033[0;0m"

// Function prototypes
bool Switch(const string& str);

int main() {

  // all the variables used

  // the name section
  string name;

  // gitlab runner section
  string arch;
  string GRIP; // Gitlab Runner Installation Permission
  // from arch secrtion of gitlab runner
  string arm32;
  string arm64;
  string amd64;  

  // Asking for permissions

  // name for coustomization pourposes
  while (true) {
    cout << BOLD << MAGENTA << "[1]" << RESET << " Please enter your name, we need it for customization purposes (2 to 25 characters, no spaces): ";
    getline(cin, name);

    // to check if there is space or not
    bool hasSpace = (name.find(' ') != string::npos);
    // Check the length of the name
    int nameLength = name.length();
    if (nameLength >= 2 && nameLength <= 25 && !hasSpace) {
      break; // Exit the loop if the name is valid
    } else {
      std::cout << RED << "[ERROR]" << RESET << "Invalid name length. Please try again." << std::endl;
    }
  }
  bool validation;
  // Installation permission of GitLab Runner and Validation of the chosen option
  while (true) {
    cout << BOLD << MAGENTA << "[2]" << RESET << "Do you want to install GitLab Runner? (yes/no): ";
    getline(cin, GRIP);
    bool validation = Switch(GRIP);
    if (validation) {
      while (true) {
        cout << BOLD << MAGENTA << "[2.1] " << RESET << " What is your architecture (arm32, arm64, amd64): ";
        getline(cin, arch);
	bool hasSpaces = (arch.find(' ') != string::npos);
	string arm32[] = {"ARM32", "Arm32", "arm32"};
	string arm64[] = {"ARM64", "Arm64", "arm64"};
	string amd64[] = {"AMD64", "Amd64", "amd64"};
        if (find(begin(arm32), end(arm32), arch) != end(arm32)) {
	  string arch = arm32[2];
	  break;
	} else if (find(begin(arm64), end(arm64), arch) != end(arm64)) {
	  string arch = arm64[2];
	  break;
	} else if (find(begin(amd64), end(amd64), arch) != end(amd64)) {
	  string arch = amd64[2];
	  break;
        } else if (hasSpaces || arch.empty()) {
	  cout << BOLD << RED << "[ERROR] " << RESET << "pls don't enter spaces or emptyness" << endl;
        } else {
	  cout << BOLD << RED << "[ERROR] " << RESET << "pls choose from arm32, arm64 or amd64" << endl;
	}
      }
      break;
    }
  }
  // Execution of the instructions according to the given permissions

  return 0;
}

// Function definitions

// Choice validator
bool Switch(const string& str) {
  // Check if the input matches any of the elements in the global 'yes' or 'no'
  bool hasSpaces = (str.find(' ') != string::npos);
  if (find(begin(yes), end(yes), str) != end(yes)) {
    return true; // Return true for a valid input
  } else if (find(begin(no), end(no), str) != end(no)) {
    return true; // Return true for a valid input
  } else if (hasSpaces || str.empty()) {
    cout << BOLD << RED << "[ERROR] " << RESET << "pls don't enter spaces or emptyness" << endl;
    return false;
  } else {
    cout << BOLD << RED << "[ERROR]" << RESET << "Please choose from 'yes' or 'no'." << endl;
    return false; // Return false for an invalid input
  }
}
