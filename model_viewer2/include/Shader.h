#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <string>

#include <Device.h>

namespace GEngine
{
    class Shader
    {
        public:
			Shader(std::string filename, Device *device);
			~Shader();

            int loadAndReadFile(std::string filename);
            void createShaderModule(Device *device);
            VkShaderModule getVulkanObject();

        private:
            std::vector<char> buffer;
            VkShaderModule shader_module;
            Device *dev;

    };
}
#endif
