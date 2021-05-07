package com.example.picturen;

public class CameraFactory {
    enum CameraType {NATIVE};

    public static Camera create(CameraType cameraType) {
        switch (cameraType) {
            case NATIVE:
                return new NativeCamera();
            default:
                return new NativeCamera();
        }
    }
}
