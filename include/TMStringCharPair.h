#ifndef TMSTRINGCHARPAIR_H
#define TMSTRINGCHARPAIR_H

#include <string>

struct TMStringCharPair {
    std::string name;
    char character;

    bool operator== (const TMStringCharPair& other) const {
        return (name == other.name && character == other.character);
    }
};

// injection of hash policy for TMStringCharPair (for unordered map purpose)
namespace std {
    template<> struct hash<TMStringCharPair> {
        typedef TMStringCharPair argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& mypair) const {
            result_type const h1 ( std::hash<std::string>()(mypair.name) );
            result_type const h2 ( std::hash<char>()(mypair.character) );
            return h1 ^ (h2 << 1);
        }
    };
}

#endif // TMSTRINGCHARPAIR_H
