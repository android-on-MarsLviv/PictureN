package com.example.picturen;

import androidx.annotation.NonNull;

public interface Camera {
    public void capture(@NonNull CameraCallback captureCallback);
}
