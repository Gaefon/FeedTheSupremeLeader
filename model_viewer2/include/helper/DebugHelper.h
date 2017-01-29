#ifndef DEBUG_HELPER_H
#define DEBUG_HELPER_H

#include "../Shader.h"
#include "../Camera.h"

class DebugHelper
{
	private:
		static Shader *m_shader;
		
	public:
		static void initShader(Shader *shader);
		static void drawAxis(float size, Camera *camera);
};

#endif
