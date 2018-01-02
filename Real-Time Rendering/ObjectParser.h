#ifndef OBJECTPARSER_H
#define OBJECTPARSER_H

#include <iostream>
#include <fstream>

#include "Mesh.h"

#include "Exports.h"



class ObjectParser
{

private:
	void ProcessLine(std::string&);

public:
	//Contrustors
	REALTIME_API ObjectParser();
	REALTIME_API ~ObjectParser();

	//Methods
	REALTIME_API void ParseFile(std::string file, Mesh** mesh);

};




#endif // !OBJECTPARSER_H



