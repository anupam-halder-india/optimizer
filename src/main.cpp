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
#include <array>
#include "include/imports.hpp"
#include "include/functions.hpp"
#include "include/modules/inlineing.inl"

int main() {
  string retryal = "yes";
  // Initilizing cURL
  CURL* curl = curl_easy_init();
  if (curl == nullptr) { cerr << "Failed to initialize libcurl" << endl; return 1; } 

   // Checking if, it is installed or not
   while (true) {
     CURLcode res = curl_easy_perform(curl);
     if (res != CURLE_OK) {
       cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
       cout << BOLD << CYAN << "[i] " << RESET << "do you want to retry? (yes/no): ";
       getline(cin, retryal);
       int wrapper = Switch(retryal);
       if (wrapper == 2) { break; } else { cout << BOLD << GREEN << "[!] " << RESET << "Download completed successfully." << endl; }
     }
   }

  string name;
  // Asking for permissions
  // Name is needed for coustomization pourposes
  while (true) {
    cout << BOLD << MAGENTA << "[1]" << RESET << " Please enter your name, we need it for customization purposes (2 to 25 characters, no spaces): ";
    
    getline(cin, name); 
    // Check the length of the name
    int nameLength = name.length();
    if (nameLength >= 2 && nameLength <= 25 && !hasSpaces(name)) {
      break;  // Exit the loop if the name is valid
    } else {
      cout << RED << "[ERROR]" << RESET << "Invalid name length. Please try again." << endl;
    }
  }
  
  // Asking for installation permission of gitLab runner
  string GRIP;
  string arch;
  int wrapper = 1;
  while (true) {
    cout << BOLD << MAGENTA << "[2] " << RESET << "Do you want to install GitLab Runner? (yes/no): ";
    getline(cin, GRIP);
    wrapper = Switch(GRIP);
    if (wrapper == 1) { 
      string armWord;
      if (osType == 3) { string armWord = "arm"; } else string armWord;
      cout << BOLD << MAGENTA << "[2.1] " << RESET << " What is your architecture, you can say 'cancel', to cancel the installation of gitlab runner ((arm32/armhf), arm64, amd64, aarch64, i386, ppc64el, s390x " + armWord + "): ";
      getline(cin, arch);
      archType(arch, GRIP);
      break;
    } else { break; }
  }
  
  // Execution of the instructions according to the given permissions
  if (wrapper == 1) {
    while (true) {
      // Gitlab runner installation url
      while (true) {
        if (osType == 1 || osType == 2) {
	  string url = "https://gitlab-runner-downloads.s3.amazonaws.com/latest/deb/gitlab-runner_" + arch + ".deb";
	  string dpkging = "dpkg -i gitlab-runner_" + arch + ".deb";
	  curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); curl_easy_cleanup(curl);
	  curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
	  break;
	} else if (osType == 3 || osType == 4) { 
	  string url = "https://gitlab-runner-downloads.s3.amazonaws.com/latest/rpm/gitlab-runner_" + arch + ".rpm";
	  string dpkging = "rpm -i gitlab-runner_" + arch + ".rpm && rpm -Uvh gitlab-runner_" + arch + ".rpm";
	  curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); curl_easy_cleanup(curl);
	  curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
	  break;
	} else if (osType == 404) {
	  cout << BOLD << RED << "[ERROR]" << RESET << "error 404, you are using unknown oprating system to install git lab runner, can't install" << endl; retryal = "no";
	  break; } else {
	  cout << BOLD << RED << "[ERROR]" << RESET << "unknown error cant install gitlab runner" << endl; retryal = "no"; 
	  break;
	}
	break;
      }
      while (retryal == "yes") { 
        int Dpackaging = system(dpkging.c_str());

        if (Dpackaging == 0) { cout << BOLD << GREEN "[!] " << RESET << "Installation completed successfully." << endl; break; }
        else { 
	  cerr << BOLD << RED "[ERROR] " << RESET << "Installation failed with error code: " << Dpackaging << endl;
	  cout << BOLD << CYAN << "[i] " << RESET << "do you want to retry (yes/no): ";
	  getline(cin, retryal);
	  Switch(retryal);
	  yesNo(retryal);
	}
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
