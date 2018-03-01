#include "ObjectParser.h"

void ObjectParser::ParseFile(std::string filename, Mesh** mesh) {
    std::ifstream file;
    file.open(filename);
    
    if (file.is_open()) {

        std::string line;

        std::string name;
        int vertcount = 0;
        int normalcount = 0;
        int texcount = 0;
        int facecount = 0;


        while (std::getline(file, line)){
            if (line[0] == 'v') {
                if (line[1] == ' '){
                    vertcount++;
                }else if (line[1] == 't'){
                    texcount++;
                }else if (line[1] == 'n'){
                    normalcount++;
                }
            }
            else if (line[0] == 'f') {
                facecount++;
            }
            else if (line[0] == 'o') {
                name = line.substr(2, line.length() - 2);
            }
        }





        //Faces in obj files point to indexes of previously preocesses elements
        //so need the store verts, tex coords and normals so faces can be created later
        *mesh = new Mesh(name, facecount);
        vertStore = std::vector<glm::vec3>(vertcount);
        textStore = std::vector<glm::vec2>(texcount);
        normStore = std::vector<glm::vec3>(normalcount);

        file.clear();
        file.seekg(0, std::ios::beg);
        vertcount   = 0;
        normalcount = 0;
        facecount   = 0;
        texcount    = 0;

        while (std::getline(file, line)) {
            if (line[0] == 'v') {
                if (line[1] == ' '){
                    size_t pos = 0;
                    float x, y, z;
                    int current = 0;
                    std::string tempLine = line;
                    std::cout << "vert" << std::endl;
                    while (current != 4) {
                        pos = tempLine.find(' ');

                        std::string coord = tempLine.substr(0, pos);
                    
                        switch (current) {
                        case 0:
                            break;
                        case 1:
                            x = std::stof(coord.c_str());
                            break;
                        case 2:
                            y = std::stof(coord.c_str());
                            break;
                        case 3:
                            z = std::stof(coord.c_str());
                            break;
                        }
                        current++;
                        tempLine.erase(0, pos + 1);
                    }
                    vertStore[vertcount++] = glm::vec3(x,y,z);
                }else if (line[1] == 't'){
                    size_t pos = 0;
                    float u,v;
                    int current = 0;
                    std::string tempLine = line;
                    std::cout << "VT" << std::endl;
                    while (current != 3){
                        pos = tempLine.find(' ');
                        std::string coord = tempLine.substr(0,pos);

                        switch (current) {
                        case 0:
                            break;
                        case 1:
                            u = std::stof(coord.c_str());
                            break;
                        case 2:
                            v = std::stof(coord.c_str());
                            break;
                        }

                        current++;
                        tempLine.erase(0, pos+1);
                    }
                    textStore[texcount++] = glm::vec2(u, v);
                }else if (line[1] == 'n'){
                    size_t pos = 0;
                    float x,y,z;
                    int current = 0;
                    std::string tempLine = line;
                    std::cout << "VN" << std::endl;
                    while (current != 4){
                        pos = tempLine.find(' ');
                        std::string coord = tempLine.substr(0,pos);

                        switch (current) {
                        case 0:
                            break;
                        case 1:
                            x = std::stof(coord.c_str());
                            break;
                        case 2:
                            y = std::stof(coord.c_str());
                            break;
                        case 3:
                            z = std::stof(coord.c_str());
                            break;
                        }

                        current++;
                        tempLine.erase(0, pos+1);
                    }
                    normStore[normalcount++] = glm::vec3(x, y, z);
                }
            } else if (line[0] == 'f') {
                size_t pos = 0;
                size_t slashPos = 0;
                int current = 0;
                int currentSlash = 0;
                std::string tempLine = line;
                Face* face = &((*mesh)->faces[facecount++]);

                std::cout << "face" << std::endl;
                while (current != 4) {
                    pos = tempLine.find(' ');
                    std::string facePart = tempLine.substr(0, pos);

                    switch (current) {
                    case 0:
                        break;
                    case 1:
                        ProcessFaceChunk(facePart, *face, 0);
                        // a = std::atoi(facePart.c_str());
                        break;
                    case 2:
                        ProcessFaceChunk(facePart, *face, 1);
                        // b = std::atoi(facePart.c_str());
                        break;
                    case 3:
                        ProcessFaceChunk(facePart, *face, 2);
                        // c = std::atoi(facePart.c_str());
                        break;
                    }
                    current++;
                    tempLine.erase(0, pos + 1);
                }
                //(*mesh)->faces[facecount++] = Face{ a-1, b-1, c-1 };
            }
        }
        file.close();
        return;
        
    }
    else {
        std::cout << "cannot open";
        return;
    }

}


void ObjectParser::ProcessFaceChunk(std::string& chunk, Face& face, int setNum){
    //Face descriptions in object files are not completely consistent
    //they can have up to 3 components seperated by slashes
    //f v/vt/vn
    //however, the slashes are not always added in cases were
    //some componenets are missing, for example:
    //f v/vt
    //There is no trailing slash to represent an absent component.
    //This makes 4 possible cases that need to be parsed:
    // f v, f v/vt, f v/vt/vn, f v//vn


    size_t    slashPos = 0;
    FaceVertSet& set = face.vertSets[setNum];

    //npos is returned when nothing is found
    if ((slashPos = chunk.find('/')) == std::string::npos){
        //-1 so the number aligns with array indexes
        set.v = vertStore[std::atoi(chunk.c_str()) -1];
    }else{
        std::string chunkPart = chunk.substr(0, slashPos); 
        set.v = vertStore[std::atoi(chunkPart.c_str()) -1];
        chunk.erase(0, slashPos+1);

        if((slashPos = chunk.find('/')) == std::string::npos){
            set.vt = textStore[std::atoi(chunkPart.c_str()) -1];
        }else{
            chunkPart = chunk.substr(0, slashPos); 
            if(chunkPart.size() != 0){
                set.vt = textStore[std::atoi(chunkPart.c_str()) -1];
            }
            chunk.erase(0, slashPos+1);
            if (chunk.size() > 0){
                set.vn = vertStore[std::atoi(chunk.c_str()) -1];
            }
        }
    }
}


ObjectParser::ObjectParser()
{
}


ObjectParser::~ObjectParser()
{
}
