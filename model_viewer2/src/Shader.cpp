#include <Shader.h>
#include <string.h>

using namespace std;

namespace GEngine
{
	Shader::Shader(string filename, string name, Device *device)
	{
		shader_module = VK_NULL_HANDLE;
		shader_name = name;
		if(loadAndReadFile(filename) > 0)
		{
		    createShaderModule(device);
		}
	}

	Shader::~Shader()
	{
		if (shader_module != VK_NULL_HANDLE)
		{
			vkDestroyShaderModule(dev->getVulkanObject(), shader_module, nullptr);
		}
	}

	string& Shader::getName()
	{
		return shader_name;
	}

	int Shader::loadAndReadFile(string filename)
	{
		ifstream file(filename, std::ios::ate);

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
		dev = device;
		create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		create_info.codeSize = buffer.size();
		buffer_aligned.resize(buffer.size() / sizeof(uint32_t) + 1, 0);
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

