package com.example.picturen;

import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = MainActivity.class.getSimpleName();

    private static final int CAMERA_PERMISSIONS_CODE = 100;


    private EditText editFilename;
    private Button captureFrameButton;

    private Camera camera;
    private FrameWriter frameWriter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        editFilename = findViewById(R.id.editPictureName);
        captureFrameButton = findViewById(R.id.tekePicture);

        captureFrameButton.setOnClickListener(this::onTakePictureClick);

        checkPermissions();
    }

    // TODO: move logic from this method into sepatate class according to MVVM patern
    private void onTakePictureClick(View view) {
        captureFrameButton.setEnabled(false);

        camera = CameraFactory.create(CameraFactory.CameraType.NATIVE);
        frameWriter = FrameWriterFactory.create(FrameWriterFactory.Location.SD);

        camera.capture(new CameraCallback() {
            @Override
            public void onCaptureSucceed(byte[] frame) {
                Log.i(TAG, "Camera captured frame : " + frame);

                captureFrameButton.setEnabled(true);

                frameWriter.write(frame, new FrameWriterCallback() {
                    @Override
                    public void onSuccessSave() {
                        Log.i(TAG, "Frame saved successfully");
                    }
                    @Override
                    public void onFailedSave() {
                        Log.i(TAG, "Failed to save frame");
                        Toast.makeText(MainActivity.this, getText(R.string.message_on_failed_save).toString(), Toast.LENGTH_SHORT).show();
                    }
                });
            }

            @Override
            public void onCaptureFailed() {
                Log.i(TAG, "Camera failed to capture frame");
                Toast.makeText(MainActivity.this, getText(R.string.message_on_failed_capture).toString(), Toast.LENGTH_SHORT).show();

                captureFrameButton.setEnabled(true);
            }
        } );
    }

    // TODO: move this method into sepatate class according to MVVM patern
    void checkPermissions() {
        if (checkSelfPermission(Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED
            || (checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED))
        {
            requestPermissions(new String[]{Manifest.permission.CAMERA, Manifest.permission.WRITE_EXTERNAL_STORAGE}, CAMERA_PERMISSIONS_CODE);
            Log.i(TAG, "Requesting permissions: CAMERA, WRITE_EXTERNAL_STORAGE");
        } else {
            Log.i(TAG, "CAMERA, WRITE_EXTERNAL_STORAGE permissions already granted");
        }
    }
}