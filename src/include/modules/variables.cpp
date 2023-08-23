#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <array>
#include "../imports.hpp"
#include "../functions.hpp"

const StringArray<5> yes = {"yes", "Yes", "YES", "y", "Y"};
const StringArray<5> no = {"no", "No", "NO", "n", "N"};

const string response;
const int osType = osDection();

string arch;
string GRIP;
int wrapper = 0;

const StringArray<6> arm32 = {"ARM32", "Arm32", "arm32", "armhf", "ARMHF", "Armhf"};
const StringArray<3> arm64 = {"ARM64", "Arm64", "arm64"};
const StringArray<3> amd64 = {"AMD64", "Amd64", "amd64"};
const StringArray<3> aarch64 = {"AARCH64", "Arrch64", "aarch64"};
const StringArray<2> i386 = {"I386", "i386"};
const StringArray<3> ppc64el = {"PPC64EL", "Ppc64el", "ppc64el"};
const StringArray<3> s390x = {"S390x", "S390X", "s390x"};
const StringArray<3> arm = {"ARM", "Arm", "arm"};
const StringArray<3> cancel = {"CANCEL", "Cancle", "cancle"};

const string url;
const string dpkging;
string retryal = "yes";
string retryal2 = "yes";
