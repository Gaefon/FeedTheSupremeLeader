#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <Device.h>

namespace GEngine
{
	class Shader
	{
		public:
			enum class ArgumentType : int
			{
				None = -1,
				Vertex = 0,
				Color = 1
			};
			
			
			Shader(std::string filename, std::string name, Device *device);
			~Shader();

			int loadAndReadFile(std::string filename);
			void createShaderModule(Device *device);
			VkShaderModule getVulkanObject();
			std::string& getName();

			void addArgumentType(int position, ArgumentType type);


		private:
		    std::vector<char> buffer;
		    std::string shader_name;
		    VkShaderModule shader_module;
		    Device *dev;
		    
		    std::map<int, ArgumentType> argument_position;
		    
		    std::vector<uint32_t> buffer_aligned;

	};
}
#endif
