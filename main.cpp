#include "HasherSHA.h"

int main() {

    std::string testString = "abcde";
    HasherSHA h(testString);
    std::cout << h << std::endl;
    h.hashString(h.getHashedString());
    std::cout << h << std::endl;

}