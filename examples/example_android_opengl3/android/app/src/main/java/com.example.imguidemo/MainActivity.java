package com.example.imguidemo;

import android.app.Activity;
import android.os.Bundle;
import android.view.SurfaceView;
import android.view.SurfaceHolder;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("imgui_demo");
    }

    private native void nativeStart(Object surface);
    private native void nativeStop();

    private SurfaceView surfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        surfaceView = new SurfaceView(this);
        setContentView(surfaceView);

        surfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder holder) {
                nativeStart(holder.getSurface());
            }

            @Override
            public void surfaceDestroyed(SurfaceHolder holder) {
                nativeStop();
            }

            @Override public void surfaceChanged(SurfaceHolder h, int f, int w, int h2) {}
        });
    }
}
