#ifndef PICTUREN_CAMERAPROVADER_H
#define PICTUREN_CAMERAPROVADER_H


class ACameraManager;
class ACameraIdList;

class CameraProvader {
public:
    CameraProvader();
    ~CameraProvader();

public:
    ACameraManager *cameraManager = nullptr;
    ACameraIdList *cameraIds = nullptr;
};


#endif //PICTUREN_CAMERAPROVADER_H
