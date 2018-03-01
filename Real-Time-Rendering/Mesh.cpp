#include "Mesh.h"


Mesh::Mesh(const std::string& name, int faceCount) {
	this->name      = name;
	faces 	  	    = new Face[faceCount];
	this->faceCount = faceCount;
	
    // refCount = new MemCount {};
    // refCount->refcount = 1;
}


Mesh::~Mesh() {
    // if(--(refCount->refcount) == 0){
        delete[] faces;
        // delete refCount;
    // }
}

// Mesh& Mesh::operator=(const Mesh& m){
//     name          = m.name;
// 	vertices      = m.vertices;
// 	faces         = m.faces;
// 	texCoords     = m.texCoords;
// 	vertexNormals = m.vertexNormals;
// 	vertCount     = m.vertCount;
// 	faceCount     = m.faceCount;
// 	texCount      = m.texCount;
// 	normalCount   = m.normalCount;
//     refCount      = m.refCount;
//     refCount->refcount++;  
//     return *this;
// }


Face::Face(){
    vertCount = 3;
	vertSets  = new FaceVertSet[vertCount];
    // refCount = new MemCount;
    // refCount->refcount = 1;;
}


// Face& Face::operator=(const Face& f){
//     vertSets = f.vertSets;
//     // refCount = f.refCount;
//     refCount++;
//     return *this;
// }

Face::~Face(){
    // refCount->refcount--;
    // if(refCount->refcount == 0){
        if (vertSets != nullptr){
            delete[] vertSets;
        }
        // delete refCount;
    // }
}


