#include "JavaAPI.h"
#include <jni.h>
#include <iostream>

namespace Orca::ScriptBindings
{
	JavaVM* jvm = nullptr;
	JNIEnv* env = nullptr;

	void InitJavaVM()
	{
		JavaVMInitArgs vm_args;
		JavaVMOption options[1];
		options[0].optionString = const_cast<char*>("-Djava.class.path=./scripts");
		vm_args.version = JNI_VERSION_21;
		vm_args.nOptions = 1;
		vm_args.options = options;
		vm_args.ignoreUnrecognized = false;

		jint res = JNI_CreateJavaVM(&jvm, reinterpret_cast<void**>(&env), &vm_args);
		if (res != JNI_OK)
		{
			std::cerr << "Failed to create a Java VM!" << std::endl;
		}
	}

	void DestroyJavaVM()
	{
		if (jvm) jvm->DestroyJavaVM();
	}

	void CallJavaMethod(const std::string& className, const std::string& methodName)
	{
		jclass cls = env->FindClass(className.c_str());
		if (!cls)
		{
			std::cerr << "The following class has not been found: " << className << std::endl;
			return;
		}

		jmethodID mID = env->GetStaticMethodID(cls, methodName.c_str(), "()V");
		if (!mID)
		{
			std::cerr << "The following method has not been found: " << methodName << std::endl;
			return;
		}

		env->CallStaticVoidMethod(cls, mID);
	}
}