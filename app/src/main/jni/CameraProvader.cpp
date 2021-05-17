#include "log_utils.h"
#include "CameraProvader.h"

#include <jni.h>

#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadataTags.h>
#include <camera/NdkCameraMetadata.h>

CameraProvader::CameraProvader() {
    cameraManager = ACameraManager_create();
    ACameraManager_getCameraIdList(cameraManager, &cameraIds);
}

CameraProvader::~CameraProvader() {
    ACameraManager_delete(cameraManager);
}