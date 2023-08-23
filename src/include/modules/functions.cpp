#include <iostream>
#include <string>
#include <algorithm>  // For std::find
#include <curl/curl.h>  // for curl
#include <fstream>  // for the os detction
#include <array>
#include "../imports.hpp"
#include "../functions.hpp"
#include "inlineing.inl"

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
  while (true){
    if (find(begin(yes), end(yes), str) != end(yes)) {
      return 1; break;  // Return true for a valid input
    } else if (find(begin(no), end(no), str) != end(no)) {
      return 2;  break;  // Return true for a valid input
    } else if (hasSpaces(str) || str.empty()) {
      cout << BOLD << RED << "[ERROR] " << RESET << "pls don't enter spaces or emptyness" << endl;
    } else {
      cout << BOLD << RED << "[ERROR]" << RESET << "Please choose from 'yes' or 'no'." << endl;  // Return false for an invalid input
    }
  }
  return 0;
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

// arch type
int archType(string& arch, string& GRIP) {
  while (true) {
    if (StrDect(arm32, arch)) { arch = arm32[3]; break; }
    else if (StrDect(arm64, arch)) { arch = arm64[2]; break; }
    else if (StrDect(i386, arch)) { arch = i386[1]; break; }
    else if (StrDect(ppc64el, arch)) { arch = ppc64el[2]; break; }
    else if (StrDect(s390x, arch)) { arch = s390x[2]; break; }
    else if ((osType == 3 && StrDect(arm, arch)) || (osType == 4 && StrDect(arm, arch))) { arch = arm[2]; break; }
    else if (StrDect(aarch64, arch)) { arch = aarch64[2]; break; }
    else if (find(begin(cancel), end(cancel), arch) != end(cancel)) { string GRIP = "no"; break; }
    else if (hasSpaces(arch) || arch.empty()) { cout << BOLD << RED << "[ERROR] " << RESET << "pls don't enter spaces or emptyness, retry" << endl; }
    else { cout << BOLD << RED << "[ERROR] " << RESET << "pls choose from arm32, arm64, amd64, aarch64, i386, ppc64el, or s390x, retry" << endl; }
  }
  return 0;
}

string yesNo(string& str) {
  while (true) {
    if (StrDect(yes, str)) { str = "yes"; break;}
    else if (StrDect(no, str)) { str = "no"; break; }
    else { cout << BOLD << RED << "[ERROR] " << RESET << "pls choose from yes or no" << endl; }
  }
  return str;
}
