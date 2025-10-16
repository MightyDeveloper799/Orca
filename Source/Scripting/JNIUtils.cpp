#include <jni.h>
#include "JNIUtils.h"

namespace Orca 
{
    JavaVM* g_JavaVM = nullptr;

    JNIEnv* GetJNIEnv() 
    {
        JNIEnv* env = nullptr;
        jint result = g_JavaVM->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);

        if (result == JNI_EDETACHED) 
        {
            if (g_JavaVM->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr) != 0) {
                return nullptr;
            }
        }

        return env;
    }
}