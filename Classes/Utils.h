#ifndef _UTILS_H_
#define _UTILS_H_

#include <json/document.h>

#include <string>

template<typename F>
void tokenize(const std::string& str, const std::string& delimiters, F processor)
{
    std::string::size_type lastPos = 0;
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos && std::string::npos != lastPos)
    {
        processor(str.substr(lastPos, pos - lastPos));
        lastPos = pos + 1;
        pos = str.find_first_of(delimiters, lastPos);
    }

    processor(str.substr(lastPos, pos - lastPos));
}

template<typename F>
unsigned int randomInt(F &random, unsigned int min, unsigned int max)
{
    return min + (random() % (int)(max - min + 1));
}

void readJsonFile(const std::string &fileName, rapidjson::Document &document);

#endif
