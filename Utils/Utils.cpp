// Utils.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Utils.h"


// This is an example of an exported variable
UTILS_API int nUtils=0;

// This is an example of an exported function.
UTILS_API int fnUtils(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see Utils.h for the class definition
CUtils::CUtils()
{
	return;
}
