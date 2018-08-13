#ifndef OBJECTPARSER_H
#define OBJECTPARSER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Mesh.h"

#include "Exports.h"


namespace rtr {

///Parses a .obj file to create a Mesh
/**
 * This parser currently cannot convert shapes other that triangles 
 * so the faces must be represented as triangles. Triangles are the
 * traditonal unit in rendering but some modelling programs, such as 
 * Blender, output models in quads rather than triangles. This can 
 * usually be fixed by converting them into triangles when parsing
 * the file, this parser does not currently do this. You can convert
 * models to use triangles in most modelling programs.
 */
class ObjectParser
{

private:
    std::vector<glm::vec3> vertStore;
    std::vector<glm::vec2> textStore;
    std::vector<glm::vec3> normStore;

public:
    //Contrustors
    ///Default Constructor
    REALTIME_API ObjectParser();
    ///Default Destructor
    REALTIME_API ~ObjectParser();

    //Methods
    //Parses a .obj file
    /**
     * The pointer to mesh pointer should be null when passed in 
     * if it points to an actual mesh, that meshes memory will be leaked
     * 
     * User is responsible for deleting the resulting mesh, this is seen
     * as poor design and will be fixed in the future
     */
    REALTIME_API void ParseFile(std::string file, Mesh** mesh);
    REALTIME_API void ProcessFaceChunk(std::string&, Face&, int);

};

}
#endif // !OBJECTPARSER_H



