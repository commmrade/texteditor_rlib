#include <Utils.hpp>



void trim_r(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [] (auto &elem) { return !isspace(elem); }).base(), s.end());
}
void trim_l(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](auto & elem) { return !isspace(elem); }));
}
void trim(std::string &s) {
    trim_l(s);
    trim_r(s);
}