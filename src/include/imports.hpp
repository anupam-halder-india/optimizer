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
using std::array;

template <std::size_t N>
using StringArray = std::array<std::string, N>;

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
extern const StringArray<5> yes;
extern const StringArray<5> no;
extern const int osType;

// Necessary for curl
extern const string response;

// From Arch section of GitLab Runner
extern const StringArray<6> arm32;
extern const StringArray<3> arm64;
extern const StringArray<3> amd64;
extern const StringArray<3> aarch64;
extern const StringArray<2> i386;
extern const StringArray<3> ppc64el;
extern const StringArray<3> s390x;
extern const StringArray<3> arm;
extern const StringArray<3> cancel;

// GitLab Runner installation command execution section
extern const string url;
extern const string dpkging;

#endif
