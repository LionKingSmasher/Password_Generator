#ifndef CRYPT_H
#define CRYPT_H

#include <iostream>
#include <unordered_map>

class ShinCrypt {
private:
    std::unordered_map<std::string, std::size_t> files;
public:
    ShinCrypt();
    ~ShinCrypt();
};

#endif // CRYPT_H
