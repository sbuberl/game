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

void readJsonFile(const std::string &fileName, rapidjson::Document &document);

#endif
