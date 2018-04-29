#ifndef MESH_H
#define MESH_H

#include "Exports.h"

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <memory>
#include <iostream>


struct FaceVertSet {
    public:
    glm::vec3 v;
    glm::vec2 vt;
};

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


class Mesh {
    public:
    //Members
    int faceCount;
    std::string name;
    glm::vec3 position;
    Face*      faces;

    //Constructors
    REALTIME_API Mesh(const std::string& name, int);
    REALTIME_API ~Mesh();

};

#endif // !MESH_H