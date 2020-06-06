package com.tomerandamir.ex4;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.StrictMode;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity {


    Bitmap drawableFromUrl(String url) throws java.net.MalformedURLException, java.io.IOException {
        Bitmap x;

        HttpURLConnection connection = (HttpURLConnection)new URL(url).openConnection();
        connection.setRequestProperty("User-agent","Mozilla/4.0");

        connection.connect();
        InputStream input = connection.getInputStream();

        x = BitmapFactory.decodeStream(input);
        return x;
    }

    private Button button;
    private ImageView img;
    int status = 0;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        button = (Button)findViewById(R.id.button);
        img = (ImageView) findViewById(R.id.imageView);

        try {
            drawable = new BitmapDrawable(getResources(),drawableFromUrl(url));
            layout.setBackground(drawable);
            img.setImageBitmap(drawableFromUrl(getString(R.string.urlOff)));
        } catch (IOException e) {
            e.printStackTrace();
        }
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (status == 0) {
                    try {
                        img.setImageBitmap(drawableFromUrl(getString(R.string.urlOn)));
                        button.setText(R.string.powerOff);
                        status = 1;
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                } else {
                    try {
                        img.setImageBitmap(drawableFromUrl(getString(R.string.urlOff)));
                        button.setText(R.string.powerOn);
                        status = 0;
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
    }
}
