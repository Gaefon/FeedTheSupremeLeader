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
			Shader(std::string filename, std::string name, Device *device);
			~Shader();

            int loadAndReadFile(std::string filename);
            void createShaderModule(Device *device);
            VkShaderModule getVulkanObject();
            std::string& getName();

        private:
            std::vector<char> buffer;
            std::string shader_name;
            VkShaderModule shader_module;
            Device *dev;
            
            std::vector<uint32_t> buffer_aligned;

    };
}
#endif
