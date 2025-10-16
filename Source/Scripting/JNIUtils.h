#pragma once

#ifndef JNI_UTILS_H
#define JNI_UTILS_H

#include <jni.h>
#include "../OrcaAPI.h"

namespace Orca
{
	ORCA_API JNIEnv* GetJNIEnv();
	extern ORCA_API JavaVM* g_JavaVM;
}

#endif