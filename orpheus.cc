#include <iostream>
#include <string>
#include <vector>
#include <re2/re2.h>

using namespace std;
using namespace re2;

// adapted from https://stackoverflow.com/questions/25889065/how-to-use-re2-library-when-match-arguments-are-unknown

int main(int argc, char* argv[]) {
    // Check for the correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <regex> <text>" << endl;
        return 1;
    }

    string regex = string(argv[1]);
    string text = argv[2];

    RE2 re(regex);

    if (!re.ok()) {
        printf("Failed to compile regular expression.\n");
        return 1;
    }

    vector<string> results;
    vector<RE2::Arg> arguments;
    vector<RE2::Arg*> arguments_ptrs;

    size_t args_count = re.NumberOfCapturingGroups();

    results.resize(args_count);
    arguments.resize(args_count);
    arguments_ptrs.resize(args_count);

    for (size_t i = 0; i < args_count; ++i) {
        arguments[i] = &results[i];
        arguments_ptrs[i] = &arguments[i];
    }

    if (RE2::FullMatchN(text, re, arguments_ptrs.data(), args_count)) {
        printf("True\n");
        for (size_t i = 0; i < args_count; i++) {
            printf("Group %zu: %s\n", i+1, results[i].c_str());
        }
    } else {
        printf("False\n");
    }

    return 0;
}