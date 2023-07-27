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
string yes[] = { "yes", "Yes", "YES", "y", "Y" };
string no[] = { "no", "No", "NO", "n", "N" };

// Function prototypes
bool Switch(const string& str);

int main() {
  // Asking for permissions

  string gitlabRunnerInstallationPermission;
  // Installation permission of GitLab Runner and Validation of the chosen option
  while (!Switch(gitlabRunnerInstallationPermission)) {
    cout << "Do you want to install GitLab Runner? (yes/no)" << endl;
    cin >> gitlabRunnerInstallationPermission;
  }

  // Execution of the instructions according to the given permissions

  return 0;
}

// Function definitions

// Choice validator
bool Switch(const string& str) { 
  // Check if the input matches any of the elements in the global 'yes' or 'no'
  if (find(begin(yes), end(yes), str) != end(yes)) {
    return true; // Return true for a valid input
  } else if (find(begin(no), end(no), str) != end(no)) {
    return true; // Return true for a valid input
  } else {
    cout << "Please choose from 'yes' or 'no'." << endl;
    return false; // Return false for an invalid input
  }
}
