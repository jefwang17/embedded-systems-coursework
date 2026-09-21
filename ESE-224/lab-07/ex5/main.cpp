// main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include "GameInventory.h"

enum class ActiveInv { INT_INV, DOUBLE_INV };

static inline std::string trim(const std::string& s) {
    size_t a = 0, b = s.size();
    while (a < b && std::isspace(static_cast<unsigned char>(s[a]))) ++a;
    while (b > a && std::isspace(static_cast<unsigned char>(s[b-1]))) --b;
    return s.substr(a, b - a);
}

struct ParsedAdd {
    std::string name, attrStr, valueStr;
    bool ok{false};
};

static ParsedAdd parseAddLine(const std::string& line) {
    ParsedAdd out;
    const std::string pref = "ADD ";
    if (line.rfind(pref, 0) != 0) return out;
    std::string rest = line.substr(pref.size());
    size_t p1 = rest.find('|');
    if (p1 == std::string::npos) return out;
    size_t p2 = rest.find('|', p1 + 1);
    if (p2 == std::string::npos) return out;
    out.name     = trim(rest.substr(0, p1));
    out.attrStr  = trim(rest.substr(p1 + 1, p2 - (p1 + 1)));
    out.valueStr = trim(rest.substr(p2 + 1));
    out.ok = !out.name.empty() && !out.attrStr.empty() && !out.valueStr.empty();
    return out;
}

int main() {
    // fast I/O; we’ll output only after we’ve collected all commands
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    GameInventory<int>    invInt;
    GameInventory<double> invDouble;
    ActiveInv active = ActiveInv::INT_INV;

    // 1) Ask for Q
    int Q = 0;
    while (true) {
        std::cout << "Enter number of commands: " << std::flush;
        if (std::cin >> Q && Q > 0) break;
        std::cout << "Please enter a positive integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // eat '\n'

    // 2) Collect exactly Q lines first (no execution yet)
    std::vector<std::string> cmds;
    cmds.reserve(Q);
    for (int i = 0; i < Q; ) {
        std::string line;
        if (!std::getline(std::cin, line)) break;
        line = trim(line);
        if (line.empty()) continue; // don't count empty lines
        cmds.push_back(line);
        ++i;
    }

    // 3) Now execute
    std::cout << "=== Executing Commands ===\n";

    for (const std::string& line : cmds) {
        if (line == "SWITCH INT") {
            active = ActiveInv::INT_INV;
            std::cout << "[SWITCH] Active inventory: INT\n";

        } else if (line == "SWITCH DOUBLE") {
            active = ActiveInv::DOUBLE_INV;
            std::cout << "[SWITCH] Active inventory: DOUBLE\n";

        } else if (line.rfind("ADD ", 0) == 0) {
            ParsedAdd p = parseAddLine(line);
            if (!p.ok) {
                std::cout << "[ERROR] Bad ADD format. Use: ADD <name>|<attribute>|<value>\n";
                continue;
            }
            try {
                double val = std::stod(p.valueStr);
                if (active == ActiveInv::INT_INV) {
                    int attr = std::stoi(p.attrStr);
                    invInt.addItem(p.name, attr, val);
                    std::cout << "[ADD] " << p.name
                              << " (attr=" << attr
                              << ", value=" << std::fixed << std::setprecision(2) << val << ")\n";
                } else {
                    double attr = std::stod(p.attrStr);
                    invDouble.addItem(p.name, attr, val);
                    std::cout << "[ADD] " << p.name
                              << " (attr=" << std::fixed << std::setprecision(2) << attr
                              << ", value=" << std::fixed << std::setprecision(2) << val << ")\n";
                }
            } catch (...) {
                std::cout << "[ERROR] Invalid numbers in ADD.\n";
            }

        } else if (line == "POP") {
            if (active == ActiveInv::INT_INV) {
                Item<int> t("", 0, 0.0);
                if (invInt.removeMostRecent(t)) {
                    std::cout << "[POP] " << t.name
                              << " (attr=" << t.attribute
                              << ", value=" << std::fixed << std::setprecision(2) << t.value << ")\n";
                } else {
                    std::cout << "[POP] (empty)\n";
                }
            } else {
                Item<double> t("", 0.0, 0.0);
                if (invDouble.removeMostRecent(t)) {
                    std::cout << "[POP] " << t.name
                              << " (attr=" << std::fixed << std::setprecision(2) << t.attribute
                              << ", value=" << std::fixed << std::setprecision(2) << t.value << ")\n";
                } else {
                    std::cout << "[POP] (empty)\n";
                }
            }

        } else if (line == "PEEK") {
            if (active == ActiveInv::INT_INV) {
                Item<int> t("", 0, 0.0);
                if (invInt.retrieveMostRecent(t)) {
                    std::cout << "[PEEK] " << t.name
                              << " (attr=" << t.attribute
                              << ", value=" << std::fixed << std::setprecision(2) << t.value << ")\n";
                } else {
                    std::cout << "[PEEK] (empty)\n";
                }
            } else {
                Item<double> t("", 0.0, 0.0);
                if (invDouble.retrieveMostRecent(t)) {
                    std::cout << "[PEEK] " << t.name
                              << " (attr=" << std::fixed << std::setprecision(2) << t.attribute
                              << ", value=" << std::fixed << std::setprecision(2) << t.value << ")\n";
                } else {
                    std::cout << "[PEEK] (empty)\n";
                }
            }

        } else if (line == "TOTAL") {
            double sum = (active == ActiveInv::INT_INV) ? invInt.totalValue()
                                                        : invDouble.totalValue();
            std::cout << "[TOTAL] " << std::fixed << std::setprecision(2) << sum << "\n";

        } else if (line == "AVERAGE") {
            double avg = (active == ActiveInv::INT_INV) ? invInt.averageAttribute()
                                                        : invDouble.averageAttribute();
            std::cout << "[AVERAGE] " << std::fixed << std::setprecision(2) << avg << "\n";

        } else if (line == "SHOW") {
            if (active == ActiveInv::INT_INV) invInt.displayInventory();
            else                               invDouble.displayInventory();

        } else if (line == "CLEAR") {
            if (active == ActiveInv::INT_INV) invInt.clear();
            else                               invDouble.clear();

        } else {
            std::cout << "[WARN] Unknown command: " << line << "\n";
        }
    }

    return 0;
}
