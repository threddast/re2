#include <iostream>
#include <string>
#include <vector>
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"


using namespace std;
using namespace re2;

// adapted from https://stackoverflow.com/questions/25889065/how-to-use-re2-library-when-match-arguments-are-unknown

int main(int argc, char* argv[]) {
    string regex = "the(?<=el(?<=e.*).*)";
    string text = "hellothere";
    if (argc == 3) {
        regex = string(argv[1]);
        text = argv[2];
    }

    if(RE2::FullMatch(text, regex)) {  // there is a bug in the NFA, it always returns full match even when it is not
        printf("Full match!\n");
    } else {
        printf("No full match\n");
    }
    
    if(RE2::PartialMatch(text, regex)) {
        printf("Partial match!\n");
        return 0;
    } else {
        printf("No partial match\n");
    }

    // parse regex
    RegexpStatus status;
    Regexp::ParseFlags flags;
    Regexp* parsed = Regexp::Parse(regex, flags, &status);
    printf("Parsed regex: \n\t%s\n", parsed->Dump().c_str());

    // compile regex for matching
    RE2 re(regex); // calls RE2::Init() internally

    // dump prog of regex
    Prog* prog = re.GetProg();
    printf("Dump of regex: \n%s\n", prog->MyDump().c_str());


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
        printf("Match!\n");
        for (size_t i = 0; i < args_count; i++) {
            printf("\tGroup %zu: %s\n", i+1, results[i].c_str());
        }
    } else {
        printf("No match\n");
    }

    return 0;
}
