/*

MIT License

Copyright (c) 2023 Anupam Halder

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <iostream>
#include <string>
#include <algorithm>  // For std::find
#include <curl/curl.h>  // for curl
#include <fstream>  // for the os detction
#include <unistd.h>  // for exec()

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::find;
using std::begin;
using std::end;
using std::cerr;
using std::ifstream;
using std::ios;

// The global necessary variables

// necessary booleans
const string yes[] = { "yes", "Yes", "YES", "y", "Y" };
const string no[] = { "no", "No", "NO", "n", "N" };

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
int Switch(const string& str);
// curl
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response);
// os dector
int osDection();
const int osType = osDection();

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
  string GRIP;  // Gitlab Runner Installation Permission
  int wrapper;

  // from arch secrtion of gitlab runner
  string arm32;
  string arm64;
  string amd64;

  // gitlab runner installation command exicution section
  string url;
  string dpkging;
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
      break;  // Exit the loop if the name is valid
    } else {
      cout << RED << "[ERROR]" << RESET << "Invalid name length. Please try again." << endl;
    }
  }
  
  // Installation permission of GitLab Runner and Validation of the chosen option
  while (true) {
    cout << BOLD << MAGENTA << "[2] " << RESET << "Do you want to install GitLab Runner? (yes/no): ";
    getline(cin, GRIP);
    wrapper = Switch(GRIP);
    if (wrapper == 1) {
      while (true) {
	string armWord; 
	if (osType == 3) { string armWord = "arm"; } else string armWord = "";
        cout << BOLD << MAGENTA << "[2.1] " << RESET << " What is your architecture, you can say 'cancel', to cancel the installation of gitlab runner ((arm32/armhf), arm64, amd64, aarch64, i386, ppc64el, s390x " + armWord + "): ";
        getline(cin, arch);
	bool hasSpaces = (arch.find(' ') != string::npos);
	string arm32[] = {"ARM32", "Arm32", "arm32", "armhf", "ARMHF", "Armhf"};
	string arm64[] = {"ARM64", "Arm64", "arm64"};
	string amd64[] = {"AMD64", "Amd64", "amd64"};
	string aarch64[] = {"AARCH64", "Arrch64", "aarch64"};
	string i386[] = {"I386", "i386"};
	string ppc64el[] = {"PPC64EL", "Ppc64el", "ppc64el"};
	string s390x[] = {"S390x", "S390X", "s390x"};
	string arm[] = {"ARM", "Arm", "arm"};
	string cancel[] = {"CANCEL", "Cancle", "cancle"};

        if (find(begin(arm32), end(arm32), arch) != end(arm32)) { string arch = arm32[3]; break; }
	else if (find(begin(arm64), end(arm64), arch) != end(arm64)) { string arch = arm64[2]; break; }
	else if (find(begin(i386), end(i386), arch) != end(i386)) { string arch = i386[1]; break; }
	else if (find(begin(ppc64el), end(ppc64el), arch) != end(ppc64el)) { string arch = ppc64el[2]; break; }
	else if (find(begin(s390x), end(s390x), arch) != end(s390x)) { string arch = s390x[2]; break; }
	else if ((osType == 3 && find(begin(arm), end(arm), arch) != end(arm)) || (osType == 4 && find(begin(arm), end(arm), arch) != end(arm))) { string arch = arm[2]; break; }
	else if (find(begin(aarch64), end(aarch64), arch) != end(aarch64)) { string arch = aarch64[2]; break; } 
	else if (find(begin(cancel), end(cancel), arch) != end(cancel)) { string GRIP = "no"; break; }
	else if (hasSpaces || arch.empty()) { cout << BOLD << RED << "[ERROR] " << RESET << "pls don't enter spaces or emptyness" << endl;}
	else { cout << BOLD << RED << "[ERROR] " << RESET << "pls choose from arm32, arm64, amd64, aarch64, i386, ppc64el or s390x" << endl; }
      }
      break;
    } else if (wrapper == 2) { break; }
    else {cout << BOLD << RED << "[ERROR] " << RESET << "pls choose from yes or no" << endl;}
  }
  
  // Execution of the instructions according to the given permissions
  if (wrapper == 1) {
    while (true) {
      // gitlab runner installation url
      while (retryal == "yes") {
        if (osType == 1 || osType == 2) { string url = "https://gitlab-runner-downloads.s3.amazonaws.com/latest/deb/gitlab-runner_" + arch + ".deb"; string dpkging = "dpkg -i gitlab-runner_" + arch + ".deb"; }
	else if (osType == 3 || osType == 4) { string url = "https://gitlab-runner-downloads.s3.amazonaws.com/latest/rpm/gitlab-runner_" + arch + ".rpm"; string dpkging = "rpm -i gitlab-runner_" + arch + ".rpm && rpm -Uvh gitlab-runner_" + arch + ".rpm"; }
	else if (osType == 404) { cout << BOLD << RED << "[ERROR]" << RESET << "error 404, you are using unknown oprating system to install git lab runner, can't install" << endl; break; }
	else { cout << BOLD << RED << "[ERROR]" << RESET << "unknown error cant install gitlab runner" << endl; break;}
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
        const char* Dpkging = dpkging.c_str(); 
        if (execl("/bin/sh", "sh", "-c", Dpkging, (char*)NULL) == -1) { cerr << BOLD << RED << "[ERROR] " << RESET << "Failed to execute command." << endl; return 1; }
      }
      break;
    }
  }
// ofstream bashrcFile("~/.bashrc", std::ios::app);
// if (bashrcFile.is_open()) {
  // bashrcFile << "" <<
// }
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
int Switch(const string& str) {
  // Check if the input matches any of the elements in the global 'yes' or 'no'
  bool hasSpaces = (str.find(' ') != string::npos);
  if (find(begin(yes), end(yes), str) != end(yes)) {
    return 1;  // Return true for a valid input
  } else if (find(begin(no), end(no), str) != end(no)) {
    return 2;  // Return true for a valid input
  } else if (hasSpaces || str.empty()) {
    cout << BOLD << RED << "[ERROR] " << RESET << "pls don't enter spaces or emptyness" << endl;
    return 3;
  } else {
    cout << BOLD << RED << "[ERROR]" << RESET << "Please choose from 'yes' or 'no'." << endl;
    return 4;  // Return false for an invalid input
  }
}

// os dector
int osDection() {
  ifstream releaseFile("/etc/os-release");
  if (!releaseFile.is_open()) {
    cerr << BOLD << RED << "[ERROR]" << RESET << " opening /etc/os-release" << endl;
    return 404;  // Return 404 if the file cannot be opened
  }

  string line;
  string distribution;

  while (getline(releaseFile, line)) {
    if (line.find("ID=") != string::npos) {
      distribution = line.substr(3);  // Extract the value after "ID="
      break;
    }
  }

  transform(distribution.begin(), distribution.end(), distribution.begin(), ::tolower);

  if (distribution == "ubuntu") {
    return 1;  // Return 1 for Ubuntu
  } else if (distribution == "debian") {
    return 2;  // Return 2 for Debian
  } else if (distribution == "centos") {
    return 4;  // Return 4 for CentOS
  } else if (distribution == "rhel" || distribution == "redhat") {
    return 3;  // Return 3 for Red Hat
  } else {
    return 404;  // Return 404 for other distributions
  }
}

