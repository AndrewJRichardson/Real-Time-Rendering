#include "Mesh.h"


rtr::Mesh::Mesh(const std::string& name, int faceCount) {
	this->name      = name;
	faces 	  	    = new Face[faceCount];
	this->faceCount = faceCount;
}


rtr::Mesh::~Mesh() {
    delete[] faces;
}

rtr::Face::Face(){
    vertCount = 3;
	vertSets  = new FaceVertSet[vertCount];
}


rtr::Face::~Face(){
    if (vertSets != nullptr){
        delete[] vertSets;
    }
}


