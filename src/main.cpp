#include <iostream>
#include <string>
#include <algorithm> // For std::find
using std::cout;
using std::endl;
using std::cin;
using std::string;

// Function prototypes
bool Switch(const string& str);

int main() {
  // Asking for permissions

  // Installation permission of GitLab Runner
  string ans;
  cout << "Do you want to install GitLab Runner? (yes/no)" << endl;
  cin >> ans;

  // Validation of the chosen option
  while (!Switch(ans)) {
    cout << "Do you want to install GitLab Runner? (yes/no)" << endl;
    cin >> ans;
  }

  // Execution of the instructions according to the given permissions

  return 0;
}

// Function definition

// Choice validator
bool Switch(const string& str) {
  string yes[] = { "yes", "Yes", "YES", "y", "Y" };
  string no[] = { "no", "No", "NO", "n", "N" };

  // Check if the input matches any of the elements in the arrays
  if (std::find(std::begin(yes), std::end(yes), str) != std::end(yes)) {
    return true; // Return true for a valid input
  } else if (std::find(std::begin(no), std::end(no), str) != std::end(no)) {
    return true; // Return true for a valid input
  } else {
    cout << "Please choose from 'yes' or 'no'." << endl;
    return false; // Return false for an invalid input
  }
}
