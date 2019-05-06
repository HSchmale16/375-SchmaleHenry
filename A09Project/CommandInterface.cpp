#include "CommandInterface.h"
#include <string>
#include <regex>
#include <vector>
#include <iostream>
#include <functional>
#include <unordered_map>

using CI_Arg = std::smatch;
using CI_Action = std::function<void(CI_Arg)>;

void
DefaultAction(CI_Arg match) {
    for(unsigned int i = 0; i < match.size(); ++i) {
        std::cout << "Match " << i << " -> " << match[i] << std::endl;
    }
}

const std::vector<std::pair<std::regex,CI_Action>> CommandMatchers = {
    { std::regex("light ([0-7]) type (0|1|2)"), 
        DefaultAction
    },
    { std::regex("light ([0-7]) (diffuse|specular|position|atten|direction) "),
        DefaultAction 
    }
};

void
runCommandInterface() {
    std::string line;
    while (std::getline(std::cin, line)) {
        int try_count = 0;
        for (auto p : CommandMatchers) {
            CI_Arg match;
            if (std::regex_match(line, match, p.first)) {
                printf("Matched on try %d\n", try_count); 
                p.second(match);
                goto had_match;
            }
            try_count++;
        }
        printf("We did not get a match, did you mess up the command?\n");
had_match:
        continue;
    }
}
