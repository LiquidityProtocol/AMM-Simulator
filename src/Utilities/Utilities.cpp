#include "Utilities.hpp"

bool Utilities::ValidNumber(std::string text) {
    if (text.empty()) {
        return false;
    }
    int dot_index = std::find(text.begin(), text.end(), '.') - text.begin();
    for (int i = (text[0] == '-'); i < (int)text.size(); ++i) {
        if (i != dot_index && !isdigit(text[i])) {
            return false;
        }
    }
    return true;
}
