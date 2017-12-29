#include "ObjectParser.h"


void ObjectParser::ParseFile(std::string filename, Mesh** mesh) {
	std::ifstream file;
	file.open(filename);
	
	if (file.is_open()) {

		std::string line;

		std::string name;
		int vertcount = 0;
		int facecount = 0;

		while (std::getline(file, line)){
			if (line[0] == 'v' && line[1] != 'n') {
				vertcount++;
			}
			else if (line[0] == 'f') {
				facecount++;
			}
			else if (line[0] == 'o') {
				name = line.substr(2, line.length() - 2);
			}
		}

		*mesh = new Mesh(name, vertcount, facecount);
		file.clear();
		file.seekg(0, std::ios::beg);
		vertcount = 0;
		facecount = 0;

		while (std::getline(file, line)) {
			if (line[0] == 'v' && line[1] != 'n') {
				
				size_t pos = 0;
				double x, y, z;
				int current = 0;
				std::string tempLine = line;
				
				while (current != 4) {
					pos = tempLine.find(' ');

					std::string coord = tempLine.substr(0, pos);
				
					switch (current) {
					case 0:
						break;
					case 1:
						x = std::atof(coord.c_str());
						break;
					case 2:
						y = std::atof(coord.c_str());
						break;
					case 3:
						z = std::atof(coord.c_str());
						break;
					}
					current++;
					tempLine.erase(0, pos + 1);
				}
				(*mesh)->vertices[vertcount++] = glm::vec3(x, y, z);
			}
			else if (line[0] == 'f') {
				size_t pos = 0;
				int a, b, c;
				int current = 0;
				std::string tempLine = line;

				while (current != 4) {
					pos = tempLine.find(' ');

					std::string facePart = tempLine.substr(0, pos);


					switch (current) {
					case 0:
						break;
					case 1:
						a = std::atoi(facePart.c_str());
						break;
					case 2:
						b = std::atoi(facePart.c_str());
						break;
					case 3:
						c = std::atoi(facePart.c_str());
						break;
					}
					current++;
					tempLine.erase(0, pos + 1);
				}
				(*mesh)->faces[facecount++] = Face{ a-1, b-1, c-1 };
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

void ObjectParser::ProcessLine(std::string& line) {

}

ObjectParser::ObjectParser()
{
}


ObjectParser::~ObjectParser()
{
}
