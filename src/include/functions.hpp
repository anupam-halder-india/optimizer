#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

// Function prototypes

// curl
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response);

// choice validator
int Switch(const string& str);

// os dector
int osDection();

// arch type
int archType(string& arch, string& GRIP);

// yes or no
string yesNo(string& str);

#endif
