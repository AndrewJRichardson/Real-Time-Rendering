#ifndef OBJECTPARSER_H
#define OBJECTPARSER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Mesh.h"

#include "Exports.h"



class ObjectParser
{

private:
    std::vector<glm::vec3> vertStore;
    std::vector<glm::vec2> textStore;
    std::vector<glm::vec3> normStore;

public:
    //Contrustors
    REALTIME_API ObjectParser();
    REALTIME_API ~ObjectParser();

    //Methods
    REALTIME_API void ParseFile(std::string file, Mesh** mesh);
    REALTIME_API void ProcessFaceChunk(std::string&, Face&, int);

};

#endif // !OBJECTPARSER_H



