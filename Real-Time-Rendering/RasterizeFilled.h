#ifndef RASTERIZEFILLED_H
#define RASTERIZEFILLED_H

#include <glm/glm.hpp>

#include "RasterizerMode.h"
#include "Device.h"
#include "Exports.h"

namespace rtr {

    class RasterizeFilled : public RasterizerMode {
        private:
        SDL_Window* window;
        bool colour;
        int c;

        public:
        REALTIME_API RasterizeFilled();
        REALTIME_API RasterizeFilled(SDL_Window& window);
        REALTIME_API void operator()(FaceVertSet, FaceVertSet, FaceVertSet,
                                     Device&);
        REALTIME_API void test(glm::vec3&, glm::vec3&, glm::vec3&, Device&);

    };
}

#endif