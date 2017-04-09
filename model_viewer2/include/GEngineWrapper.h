#ifndef GENGINEWRAPPER_H_INCLUDED
#define GENGINEWRAPPER_H_INCLUDED
#include <GEngine.h>
#include <Version.h>
#include <Window.h>
#include <Surface.h>
#include <SwapChain.h>
#include <Shader.h>
#include <Pipeline.h>
#include <CommandBuffers.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <string>

namespace GEngine
{
    class GEngineWrapper
    {

        public:
        GEngineWrapper();
        ~GEngineWrapper();
        Draw(std::string window_name, unsigned int width, unsigned int height);
    };
}
#endif // GENGINEWRAPPER_H_INCLUDED
