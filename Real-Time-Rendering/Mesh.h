#ifndef MESH_H
#define MESH_H

#include "Exports.h"

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <memory>
#include <iostream>

namespace rtr{

/** \brief holds a vector for a vertex of a face and its corresponding 
 * UV vector if it exists
 */
struct FaceVertSet {
    public:
    glm::vec3 v;
    glm::vec2 vt;
};

/// Holds the information regarding a face of a mesh
/**
 * Used to group faces of a mesh together
 */
class Face {
    private:
    public:
    int vertCount;
    glm::vec3 surfaceNormal;
    FaceVertSet* vertSets;


    public:
    REALTIME_API Face();
    REALTIME_API Face(int);
    REALTIME_API ~Face();

};


/// Stores information for a mesh
/**
 * To create a mesh use ObjectParser to parse an obj file 
 * or create a parser to create meshes from another file type
 * 
 */
class Mesh {
    public:
    //Members
    int faceCount;
    std::string name;
    Face*      faces;

    //Constructors
    REALTIME_API Mesh(const std::string& name, int);
    REALTIME_API ~Mesh();

};

}

#endif // !MESH_H