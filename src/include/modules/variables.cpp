#include "../imports.hpp"
#include "../functions.hpp"

const string yes[5] = {"yes", "Yes", "YES", "y", "Y"};
const string no[5] = {"no", "No", "NO", "n", "N"};
bool hasSpaces = (name.find(' ') != string::npos);

string response;
int osType = osDection();
string name;

string arch;
string GRIP;
int wrapper;

string arm32[6] = {"ARM32", "Arm32", "arm32", "armhf", "ARMHF", "Armhf"};
string arm64[3] = {"ARM64", "Arm64", "arm64"};
string amd64[3] = {"AMD64", "Amd64", "amd64"};
string aarch64[3] = {"AARCH64", "Arrch64", "aarch64"};
string i386[2] = {"I386", "i386"};
string ppc64el[3] = {"PPC64EL", "Ppc64el", "ppc64el"};
string s390x[3] = {"S390x", "S390X", "s390x"};
string arm[3] = {"ARM", "Arm", "arm"};
string cancel[3] = {"CANCEL", "Cancle", "cancle"};

string url;
string dpkging;
string retryal = "yes";
string retryal2 = "yes";
