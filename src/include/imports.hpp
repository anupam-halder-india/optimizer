#ifndef IMPORTS_HPP
#define IMPORTS_HPP

#include <iostream>
#include <string>
#include <algorithm> // For std::find
#include <fstream>   // For file input/output
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;
using std::find;
using std::begin;
using std::end;
using std::cerr;
using std::ifstream;
using std::ios;
using std::cin;

// Colours
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define RESET "\033[0;0m"

// Necessary booleans
extern const string yes[5];
extern const string no[5];
extern const int osType;
extern const bool hasSpaces;

// Necessary for curl
extern const string response;

// The name section
extern string name;

// GitLab Runner section
extern string arch;
extern string GRIP; // GitLab Runner Installation Permission
extern int wrapper;

// From Arch section of GitLab Runner
extern const string arm32[6];
extern const string arm64[3];
extern const string amd64[3];
extern const string aarch64[3];
extern const string i386[2];
extern const string ppc64el[3];
extern const string s390x[3];
extern const string arm[3];
extern const string cancel[3];

// GitLab Runner installation command execution section
extern const string url;
extern const string dpkging;
extern string retryal;
extern string retryal2;

#endif
