#ifndef CUECARDREADER
#define CUECARDREADER

#include <string>
#include <vector>
#include <stdexcept>

#include "CueCardCollection.h"

class UnevenNumberOfLines : public std::runtime_error { using std::runtime_error::runtime_error; };
class FileNotFound : public std::runtime_error { using std::runtime_error::runtime_error; };
class FileEmpty : public std::runtime_error { using std::runtime_error::runtime_error; };
class EmptyLineEncountered  : public std::runtime_error { using std::runtime_error::runtime_error; };


class CueCardReader
{
public:
    CueCardCollection getCueCardsFromFile(const std::string& path) const;
};

std::string removeTrailingCR(const std::string& str);

#endif /* CUECARDREADER */
