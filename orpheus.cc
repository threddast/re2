#include <iostream>
#include <string>
#include <re2/re2.h>

using namespace std;
using namespace re2;

int main(int argc, char* argv[]) {
    // Check for the correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <regex> <text>" << endl;
        return 1;
    }

    string regex = argv[1];
    string text = argv[2];

    if (RE2::FullMatch(text, regex)) {
	printf("True\n");
    } else {
	printf("False\n");
    }

    return 0;
}

