#ifndef _PARAMS_H_
#define _PARAMS_H_

#include <string>
#include "RenderPipeline.h"

struct Params
{
	struct
	{
		std::string fileName;
		bool fileIsCreated = false;
	} gLogFile;
	
	RenderPipeline* gRenderPipeline = nullptr;
};

extern Params* gParams;

#endif // _PARAMS_H_