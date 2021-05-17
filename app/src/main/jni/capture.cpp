#include "log_utils.h"
#include "CameraProvader.h"

#include <jni.h>

#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadataTags.h>
#include <camera/NdkCameraMetadata.h>

#include <media/NdkImage.h>           // for AImage
#include <media/NdkImageReader.h>     // for AImageReader


/*#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraCaptureSession.h>
#include <camera/NdkCameraError.h>
#include <camera/NdkCameraWindowType.h>*/

#include <string>
#include <thread>

using std::string;
using std::thread;

#ifndef PICTUREN_CAPTURE_H
#define PICTUREN_CAPTURE_H

#define TAG "capture-lib::capture"

void getCameraSize(ACameraMetadata *metadataObj, ACameraMetadata_const_entry entry, acamera_metadata_tag tag, int32_t &width, int32_t &height);

/*static void onDisconnected(void* context, ACameraDevice* device)
{
    __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "onDisconnected");
}

static void onError(void* context, ACameraDevice* device, int error)
{
    __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "onError");
}

static ACameraDevice_stateCallbacks cameraDeviceCallbacks = {
        .context = nullptr,                 // inside the class it <this>
        .onDisconnected = onDisconnected,
        .onError = onError,
};

static void imageCallback(void* context, AImageReader* reader)
{
    AImage *image = nullptr;
    auto status = AImageReader_acquireNextImage(reader, &image);
    // Check status here ...

    // Try to process data without blocking the callback
    thread processor([=](){

        uint8_t *data = nullptr;
        int len = 0;
        AImage_getPlaneData(image, 0, &data, &len);

        // Process data here
        // ...

        AImage_delete(image);
    });
    processor.detach();
}

AImageReader* createJpegReader()
{
    AImageReader* reader = nullptr;
    media_status_t status = AImageReader_new(640, 480, AIMAGE_FORMAT_JPEG,
                                             4, &reader);

    //if (status != AMEDIA_OK)
    // Handle errors here

    AImageReader_ImageListener listener{
            .context = nullptr,
            .onImageAvailable = imageCallback,
    };

    AImageReader_setImageListener(reader, &listener);

    return reader;
}

ANativeWindow* createSurface(AImageReader* reader)
{
    ANativeWindow *nativeWindow;
    AImageReader_getWindow(reader, &nativeWindow);

    return nativeWindow;
}*/

extern "C"
JNIEXPORT jbyteArray JNICALL Java_com_example_picturen_NativeCamera_capture(JNIEnv *env, jobject instance)
 {
    LOGI("capture");

    ACameraManager *cameraManager = ACameraManager_create();

    ACameraIdList *cameraIds = nullptr;
    ACameraManager_getCameraIdList(cameraManager, &cameraIds);

    int camerasNumber = cameraIds->numCameras;
    string logMessage = "found " + std::to_string(camerasNumber) + " cameras.";
    const char *logMessageC = logMessage.c_str();

     __android_log_print(ANDROID_LOG_INFO, TAG, "%s", logMessageC);

    //string backId;

     for (int i = 0; i < cameraIds->numCameras; ++i)
     {
         const char* id = cameraIds->cameraIds[i];
         ACameraMetadata* metadataObj;
         ACameraManager_getCameraCharacteristics(cameraManager, id, &metadataObj);

         int32_t count = 0;
         const uint32_t* tags = nullptr;
         ACameraMetadata_getAllTags(metadataObj, &count, &tags);

         for (int tagIdx = 0; tagIdx < count; ++tagIdx)
         {
             // We are interested in entry that describes the facing of camera
             if (ACAMERA_LENS_FACING == tags[tagIdx]) {
                 ACameraMetadata_const_entry lensInfo = { 0 };
                 ACameraMetadata_getConstEntry(metadataObj, tags[tagIdx], &lensInfo);

                 auto facing = static_cast<acamera_metadata_enum_android_lens_facing_t>(lensInfo.data.u8[0]);

                 if (facing == ACAMERA_LENS_FACING_FRONT)
                 {
                     __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "ACAMERA_LENS_FACING_FRONT");

                     int32_t width;
                     int32_t height;
                     //__android_log_print(ANDROID_LOG_INFO, TAG, "%s: %i %s: %i", "width", width, "  height", height);
                     getCameraSize(metadataObj, lensInfo, ACAMERA_SCALER_AVAILABLE_RECOMMENDED_STREAM_CONFIGURATIONS, width, height);
                     __android_log_print(ANDROID_LOG_INFO, TAG, "%s: %i %s: %i", "width", width, "  height", height);
                 }

                 if (facing == ACAMERA_LENS_FACING_BACK)
                 {
                     __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "ACAMERA_LENS_FACING_BACK");

                     int32_t width;
                     int32_t height;
                     //__android_log_print(ANDROID_LOG_INFO, TAG, "%s: %i %s: %i", "width", width, "  height", height);
                     getCameraSize(metadataObj, lensInfo, ACAMERA_SCALER_AVAILABLE_RECOMMENDED_STREAM_CONFIGURATIONS, width, height);
                     __android_log_print(ANDROID_LOG_INFO, TAG, "%s: %i %s: %i", "width", width, "  height", height);
                 }

                 if (facing == ACAMERA_LENS_FACING_EXTERNAL)
                 {
                     __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "ACAMERA_LENS_FACING_EXTERNAL");
                 }
             }

         }

         ACameraMetadata_free(metadataObj);

     }
     ACameraManager_deleteCameraIdList(cameraIds);


     ACameraManager_delete(cameraManager);

    return nullptr;
 }



void getCameraSize(ACameraMetadata *metadataObj, ACameraMetadata_const_entry entry, acamera_metadata_tag tag, int32_t &width, int32_t &height) {
    /*if (tag != ACAMERA_SCALER_AVAILABLE_STREAM_CONFIGURATIONS)
        return;*/

    __android_log_print(ANDROID_LOG_INFO, TAG, "%s%i", "entry.count:", entry.count);

    for (int i = 0; i < entry.count; i += 4)
    {
        // We are only interested in output streams, so skip input stream
        int32_t input = entry.data.i32[i + 3];
        if (input)
            continue;

        int32_t format = entry.data.i32[i + 0];
        __android_log_print(ANDROID_LOG_INFO, TAG, "%s%i", "format:", format);
        if (format == AIMAGE_FORMAT_JPEG)
        {
            __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "AIMAGE_FORMAT_JPEG");
            width = entry.data.i32[i + 1];
            height = entry.data.i32[i + 2];
        }
    }
}

#endif //PICTUREN_CAPTURE_H
