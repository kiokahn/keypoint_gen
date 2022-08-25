
#include "graphics/gl_extension.h"

namespace graphics {

bool kGlExtensionInitialized = false;

void glExtensionInitialize()
{
	if (kGlExtensionInitialized) return;

	kGlExtensionInitialized = true;
	glewInit();
}


};