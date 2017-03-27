#include <Shader.h>
#include <string.h>
using namespace std;

namespace GEngine
{
    Shader::Shader(string filename, Device *device)
    {
        shader_module = VK_NULL_HANDLE;
        if(loadAndReadFile(filename) > 0)
        {
            createShaderModule(device);
        }
    }

    int Shader::loadAndReadFile(string filename)
    {
        ifstream file(filename, std::ios::ate | std::ios::binary);

        if(!file.is_open())
        {
            cerr << "File " << filename << " could not be opened!" << endl;
            return 0;
        }
        size_t file_size = (size_t)file.tellg();
        file.seekg(0);
        buffer.resize(file_size, 0);
        file.read(buffer.data(), file_size);
        file.close();
        return 1;
    }

    void Shader::createShaderModule(Device *device)
    {
        VkShaderModuleCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.codeSize = buffer.size();
        vector<uint32_t> buffer_aligned(buffer.size() / sizeof(uint32_t) + 1);
        memcpy(buffer_aligned.data(), buffer.data(), buffer.size());
        create_info.pCode = buffer_aligned.data();

        if(vkCreateShaderModule(device->getVulkanObject(), &create_info, nullptr, &shader_module) != VK_SUCCESS)
        {
            cerr << "Failed to create shader module" << endl;
            shader_module = VK_NULL_HANDLE;
        }
    }

    VkShaderModule Shader::getVulkanObject()
    {
        return shader_module;
    }
}

