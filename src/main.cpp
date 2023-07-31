#include <iostream>
#include <string>
#include <algorithm> // For std::find
#include <curl/curl.h> // for curl

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::find;
using std::begin;
using std::end;
using std::cerr;

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

// choice validator
bool Switch(const string& str);
// curl
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response);

int main() {
  // initilizing curl
  CURL* curl = curl_easy_init();
  if (!curl) { cerr << "Failed to initialize libcurl" << endl; return 1; }

  // curl necessary variables
  CURLcode res = curl_easy_perform(curl);

  // all the variables used

  // necessary for curl
  string response;

  // the name section
  string name;

  // gitlab runner section
  string arch;
  string GRIP; // Gitlab Runner Installation Permission
  
  // from arch secrtion of gitlab runner
  bool validation;
  string arm32;
  string arm64;
  string amd64;  

  // gitlab runner installation command exicution section
  string retryal = "yes";
  string retryal2 = "yes";

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
      cout << RED << "[ERROR]" << RESET << "Invalid name length. Please try again." << endl;
    }
  }
  
  // Installation permission of GitLab Runner and Validation of the chosen option
  while (true) {
    cout << BOLD << MAGENTA << "[2]" << RESET << "Do you want to install GitLab Runner? (yes/no): ";
    getline(cin, GRIP);
    bool validation = Switch(GRIP);
    if (validation) {
      while (true) {
        cout << BOLD << MAGENTA << "[2.1] " << RESET << " What is your architecture, you can say 'cancel', to cancel the installation of gitlab runner (arm32, arm64, amd64): ";
        getline(cin, arch);
	bool hasSpaces = (arch.find(' ') != string::npos);
	string arm32[] = {"ARM32", "Arm32", "arm32"};
	string arm64[] = {"ARM64", "Arm64", "arm64"};
	string amd64[] = {"AMD64", "Amd64", "amd64"};
	string cancel[] = {"CANCEL", "Cancle", "cancle"};
        if (find(begin(arm32), end(arm32), arch) != end(arm32)) {
	  string arch = arm32[2];
	  break;
	} else if (find(begin(arm64), end(arm64), arch) != end(arm64)) {
	  string arch = arm64[2];
	  break;
	} else if (find(begin(amd64), end(amd64), arch) != end(amd64)) {
	  string arch = amd64[2];
	  break;
        } else if (find(begin(cancel), end(cancel), arch) != end(cancel)) {
	  string GRIP = "no";
	  break;
	}else if (hasSpaces || arch.empty()) {
	  cout << BOLD << RED << "[ERROR] " << RESET << "pls don't enter spaces or emptyness" << endl;
        } else {
	  cout << BOLD << RED << "[ERROR] " << RESET << "pls choose from arm32, arm64 or amd64" << endl;
	}
      }
      break;
    }
  }
  
  // Execution of the instructions according to the given permissions
  if (find(begin(yes), end(yes), GRIP) != end(yes)) {
    while (true) {
      // gitlab runner installation url
      while (retryal == "yes") {
        string url = "https://gitlab-runner-downloads.s3.amazonaws.com/latest/deb/gitlab-runner_" + arch + ".deb";
        // gitlab runner installation through its url and curl lib
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      
        // checking if it is installed or not
        if (res != CURLE_OK) { 
	  cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
	  cout << BOLD << CYAN << "[i] " << RESET << "do you want to retry? (yes/no): ";
	  getline(cin, retryal);
	  Switch(retryal);
	  while (true) {
	    if (find(begin(yes), end(yes), retryal) != end(yes)) { string retryal = "yes"; break;}
	    else if (find(begin(no), end(no), retryal) != end(no)) { string retryal = "no"; break; }
	    else { cout << BOLD << RED << "[ERROR] " << RESET << "pls choose from yes or no" << endl; }
	  }
	}
        else { cout << BOLD << GREEN << "[!] " << RESET << "Download completed successfully." << endl; } }
	curl_easy_cleanup(curl);
	break;
      
      while (retryal2 == "yes") {
        string command = "dpkg -i gitlab-runner_" + arch + ".deb";
        int result = system(command.c_str());

        if (result == 0) { cout << BOLD << GREEN "[!] " << RESET << "Installation completed successfully." << endl; break; }
        else { 
	  cerr << BOLD << RED "[ERROR] " << RESET << "Installation failed with error code: " << result << endl;
	  cout << BOLD << CYAN << "[i] " << RESET << "do you want to retry (yes/no): ";
	  getline(cin, retryal2);
	  Switch(retryal2);
	  while (true) {
	    if (find(begin(yes), end(yes), retryal2) != end(yes)) {string retryal2 = "yes"; break;}
	    else if (find(begin(no), end(no), retryal2) != end(no)) { string retryal2 = "no"; break; }
	    else { cout << BOLD << RED << "[ERROR] " << RESET << "pls choose from yes or no" << endl; }
	  }
	}
	curl_easy_cleanup(curl);
      }
      break;
    }
  }

  return 0;
}

// Function definitions
// the curl function
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response) {
  size_t totalSize = size * nmemb;
  response->append((char*)contents, totalSize);
  return totalSize;
}

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
