#ifndef MESH_H
#define MESH_H

#include "Exports.h"

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <memory>
#include <iostream>

#include <SDL.h>

// struct REALTIME_API MemCount{
//     int refcount = 0;
// };

struct FaceVertSet {
    public:
    glm::vec3 v;
    glm::vec2 vt;
    glm::vec3 vn;
};

class Face {
    private:
    // MemCount* refCount; 
    public:
    int vertCount;
    FaceVertSet* vertSets;

    public:
    REALTIME_API Face();
    REALTIME_API Face(int);
    REALTIME_API ~Face();

    //REALTIME_API Face& operator=(const Face&);
};


class Mesh {
        // MemCount* refCount;
    public:
    //Members
    int faceCount;
    std::string name;
    glm::vec3 position;
    Face*      faces;

    //Constructors
    REALTIME_API Mesh(const std::string& name, int);
    //REALTIME_API Mesh(const Mesh&);
    REALTIME_API ~Mesh();

        //Operators
        // REALTIME_API Mesh& operator=(const Mesh&);
};

#endif // !MESH_H