#pragma once

#ifndef JAVA_API_H
#define JAVA_API_H

#include <string>

namespace Orca::ScriptBindings
{
	void InitJavaVM();
	void DestroyJavaVM();
	void CallJavaMethod(const std::string& className, const std::string& methodName);
}

#endif