#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#ifndef PICTUREN_DEF_H
#define PICTUREN_DEF_H

#define STRINGIFY(x) #x
#define LOG_TAG    __FILE__ ":" STRINGIFY(__Capture__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //PICTUREN_DEF_H
