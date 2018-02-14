#ifndef PROJECT_H
#define PROJECT_H

#include "Exports.h"
#include <glm/glm.hpp>

namespace rtr {

    class Project {
        private:
        REALTIME_API glm::vec3 ProjectVert(const glm::vec3&, const glm::mat4&,
                                           const int, const int, const int,
                                           const int) const;

        public: 


        //halfHeight and width are passed to avoid adding two divide ops
        REALTIME_API glm::vec3 operator()(const glm::vec3& vert, 
                                          const glm::mat4& transform,
                                          const int bufferHeight,
                                          const int bufferWidth,
                                          const int halfHeight,
                                          const int halfWidth) const;
        

    };
}


#endif