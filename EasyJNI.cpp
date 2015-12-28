/****************************************************************************
 Copyright (c) 2015 Victor Komarov

 https://github.com/fnz
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "EasyJNI.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "base/ccUTF8.h"

#define LOG_TAG "EasyJNI"
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

std::unordered_map<JNIEnv*, std::vector<jobject>> EasyJNI::localRefs;

jstring EasyJNI::convert(cocos2d::JniMethodInfo& t, const char* x) {
    jstring ret = cocos2d::StringUtils::newStringUTFJNI(t.env, x ? x : "");
    localRefs[t.env].push_back(ret);
    return ret;
}

jstring EasyJNI::convert(cocos2d::JniMethodInfo& t, const std::string& x) {
    return convert(t, x.c_str());
}

void EasyJNI::deleteLocalRefs(JNIEnv* env) {
    if (!env) {
        return;
    }

    for (const auto& ref : localRefs[env]) {
        env->DeleteLocalRef(ref);
    }
    localRefs[env].clear();
}

void EasyJNI::reportError(const std::string& className, const std::string& methodName, const std::string& signature) {
    LOGE("Failed to find static java method. Class name: %s, method name: %s, signature: %s ",  className.c_str(), methodName.c_str(), signature.c_str());
}

#endif