package com.example.picturen;

public interface CameraCallback {
    public void onCaptureSucceed(byte[] frame);
    public void onCaptureFailed();
}

