
#include "Utils.h"

#include <json/reader.h>
#include <json/filereadstream.h>

#include <cstdio>

void readJsonFile(const std::string &fileName, rapidjson::Document &document)
{
    FILE* pFile = std::fopen(fileName.c_str(), "rb");
    char buffer[1024];
    rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
    document.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);
    std::fclose(pFile);
}
