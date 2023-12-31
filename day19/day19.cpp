
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

enum class RuleType {
    GreaterThan,
    LessThan,
    Any,
};

struct Rule {
    RuleType type;
    char variable;
    int value;
    std::string target; // special target A and R for accept and reject
};

struct Part {
    int x;
    int m;
    int a;
    int s;
};

using RulesMap = std::map<std::string, std::vector<Rule>>;
RulesMap rules;

std::string resolvePart(const Part& part, const std::string& entry, const RulesMap& rules) {
    auto it = rules.find(entry);
    
    auto ruleList = it->second;
    for (auto& rule : ruleList) {
        if (rule.type == RuleType::Any) {
            return rule.target;
        } else if (rule.type == RuleType::GreaterThan) {
            if (rule.variable == 'x') {
                if (part.x > rule.value) {
                    return rule.target;
                }
            } else if (rule.variable == 'm') {
                if (part.m > rule.value) {
                    return rule.target;
                }
            } else if (rule.variable == 'a') {
                if (part.a > rule.value) {
                    return rule.target;
                }
            } else if (rule.variable == 's') {
                if (part.s > rule.value) {
                    return rule.target;
                }
            }
        } else if (rule.type == RuleType::LessThan) {
            if (rule.variable == 'x') {
                if (part.x < rule.value) {
                    return rule.target;
                }
            } else if (rule.variable == 'm') {
                if (part.m < rule.value) {
                    return rule.target;
                }
            } else if (rule.variable == 'a') {
                if (part.a < rule.value) {
                    return rule.target;
                }
            } else if (rule.variable == 's') {
                if (part.s < rule.value) {
                    return rule.target;
                }
            }
        }
    }

    return entry;
}

int first() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;

        // px{a<2006:qkq,m>2090:A,rfg}
        while (getline(newfile, line)) {

            if (line.length() == 0) {
                break;
            }

            // easier to parse this way
            line[line.length() - 1] = ',';

            // find bracket
            int bracket = line.find('{');
            std::string ruleName = line.substr(0, bracket);

            // split by comma
            std::vector<Rule> ruleList;
            std::string rest = line.substr(bracket + 1);
            bracket = rest.find(",");
            while (bracket != std::string::npos) {
                std::string rule = rest.substr(0, bracket);
                rest = rest.substr(bracket + 1);

                Rule r;
                // s<537:gd
                if (rule.find('<') != std::string::npos) {
                    r.type = RuleType::LessThan;
                    r.variable = rule[0];
                    r.value = std::stoi(rule.substr(rule.find('<') + 1));
                    r.target = rule.substr(rule.find(':') + 1);
                } else if (rule.find('>') != std::string::npos) {
                    r.type = RuleType::GreaterThan;
                    r.variable = rule[0];
                    r.value = std::stoi(rule.substr(rule.find('>') + 1));
                    r.target = rule.substr(rule.find(':') + 1);
                } else {
                    r.type = RuleType::Any;
                    r.target = rule;
                }

                ruleList.push_back(r);

                bracket = rest.find(",");
            }
            rules[ruleName] = ruleList;
        }

        // {x=787,m=2655,a=1222,s=2876}
        std::vector<Part> parts;        
        while (getline(newfile, line)) {
            // split by comma
            std::string rest = line.substr(1, line.length() - 2);
            rest += ",";

            int bracket = rest.find(",");
            Part p;
            while (bracket != std::string::npos) {
                std::string part = rest.substr(0, bracket);

                std::string variable = part.substr(0, part.find('='));
                int value = std::stoi(part.substr(part.find('=') + 1));

                if (variable == "x") {
                    p.x = value;
                } else if (variable == "m") {
                    p.m = value;
                } else if (variable == "a") {
                    p.a = value;
                } else if (variable == "s") {
                    p.s = value;
                }

                rest = rest.substr(bracket + 1);
                bracket = rest.find(",");                
            }
            parts.push_back(p);
        }

        int totalRatingNumbers = 0;

        for (const Part& part : parts) {
            std::string destination = resolvePart(part, "in", rules);
            while (destination != "A" && destination != "R") {
                destination = resolvePart(part, destination, rules);
            }

            if (destination == "A") {
                totalRatingNumbers += part.x + part.m + part.a + part.s;
            } else {
                //std::cout << "reject" << std::endl;
            }
        }

        std::cout << totalRatingNumbers << std::endl;

        newfile.close();
    }


    return 0;
}

struct Range {
    int min = 1;
    int max = 4000;
};

struct PossiblePartRange {
    Range x;
    Range m;
    Range a;
    Range s;
};

int second() {
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in);
    if (newfile.is_open()) {
        std::string line;
        // px{a<2006:qkq,m>2090:A,rfg}
        while (getline(newfile, line)) {

            if (line.length() == 0) {
                break;
            }

            // easier to parse this way
            line[line.length() - 1] = ',';

            // find bracket
            int bracket = line.find('{');
            std::string ruleName = line.substr(0, bracket);

            // split by comma
            std::vector<Rule> ruleList;
            std::string rest = line.substr(bracket + 1);
            bracket = rest.find(",");
            while (bracket != std::string::npos) {
                std::string rule = rest.substr(0, bracket);
                rest = rest.substr(bracket + 1);

                Rule r;
                // s<537:gd
                if (rule.find('<') != std::string::npos) {
                    r.type = RuleType::LessThan;
                    r.variable = rule[0];
                    r.value = std::stoi(rule.substr(rule.find('<') + 1));
                    r.target = rule.substr(rule.find(':') + 1);
                } else if (rule.find('>') != std::string::npos) {
                    r.type = RuleType::GreaterThan;
                    r.variable = rule[0];
                    r.value = std::stoi(rule.substr(rule.find('>') + 1));
                    r.target = rule.substr(rule.find(':') + 1);
                } else {
                    r.type = RuleType::Any;
                    r.target = rule;
                }

                ruleList.push_back(r);

                bracket = rest.find(",");
            }
            rules[ruleName] = ruleList;
        }
        newfile.close();

        std::map<std::string, PossiblePartRange> toVisit;
        toVisit["in"] = PossiblePartRange();

        unsigned long long combinations = 0;

        while (!toVisit.empty()) {
            auto it = toVisit.begin();
            std::string current = it->first;
            PossiblePartRange currentRange = it->second;
            toVisit.erase(it);

            auto ruleList = rules[current];
            PossiblePartRange alternate = currentRange;
            for (auto& rule : ruleList) {
                if (rule.type == RuleType::LessThan) {
                    if (rule.variable == 'x') {
                        currentRange.x.max = std::min(currentRange.x.max, rule.value - 1);
                        alternate.x.min = std::max(alternate.x.min, rule.value);
                    } else if (rule.variable == 'm') {
                        currentRange.m.max = std::min(currentRange.m.max, rule.value - 1);
                        alternate.m.min = std::max(alternate.m.min, rule.value);
                    } else if (rule.variable == 'a') {
                        currentRange.a.max = std::min(currentRange.a.max, rule.value - 1);
                        alternate.a.min = std::max(alternate.a.min, rule.value);
                    } else if (rule.variable == 's') {
                        currentRange.s.max = std::min(currentRange.s.max, rule.value - 1);
                        alternate.s.min = std::max(alternate.s.min, rule.value);
                    }

                    if (rule.target == "R") {
                        currentRange = alternate;
                        continue;
                    }
                    if (rule.target == "A") {
                        combinations += (unsigned long long)(currentRange.x.max - currentRange.x.min + 1) *
                                        (currentRange.m.max - currentRange.m.min + 1) * 
                                        (currentRange.a.max - currentRange.a.min + 1) * 
                                        (currentRange.s.max - currentRange.s.min + 1);
                        currentRange = alternate;
                        continue;                        
                    }
                    toVisit[rule.target] = currentRange;
                    currentRange = alternate;
                } else if (rule.type == RuleType::GreaterThan) {
                    if (rule.variable == 'x') {
                        currentRange.x.min = std::max(currentRange.x.min, rule.value + 1);
                        alternate.x.max = std::min(alternate.x.max, rule.value);
                    } else if (rule.variable == 'm') {
                        currentRange.m.min = std::max(currentRange.m.min, rule.value + 1);
                        alternate.m.max = std::min(alternate.m.max, rule.value);
                    } else if (rule.variable == 'a') {
                        currentRange.a.min = std::max(currentRange.a.min, rule.value + 1);
                        alternate.a.max = std::min(alternate.a.max, rule.value);
                    } else if (rule.variable == 's') {
                        currentRange.s.min = std::max(currentRange.s.min, rule.value + 1);
                        alternate.s.max = std::min(alternate.s.max, rule.value);
                    }
                    
                    if (rule.target == "R") {
                        currentRange = alternate;
                        continue;
                    }
                    if (rule.target == "A") {
                        combinations += (unsigned long long)(currentRange.x.max - currentRange.x.min + 1) * 
                                        (currentRange.m.max - currentRange.m.min + 1) * 
                                        (currentRange.a.max - currentRange.a.min + 1) * 
                                        (currentRange.s.max - currentRange.s.min + 1);
                        currentRange = alternate;
                        continue;                        
                    }
                    toVisit[rule.target] = currentRange;
                    currentRange = alternate;
                } else if (rule.type == RuleType::Any) {
                    if (rule.target == "R") {
                        continue;
                    }
                    if (rule.target == "A") {
                        combinations += (unsigned long long)(alternate.x.max - alternate.x.min + 1) *
                                        (alternate.m.max - alternate.m.min + 1) * 
                                        (alternate.a.max - alternate.a.min + 1) * 
                                        (alternate.s.max - alternate.s.min + 1);
                        continue;                        
                    }
                    toVisit[rule.target] = alternate;
                }
            }
        }

        std::cout << combinations << std::endl;
    }

    return 0;
}

int main() {
    first();
    second();
}


