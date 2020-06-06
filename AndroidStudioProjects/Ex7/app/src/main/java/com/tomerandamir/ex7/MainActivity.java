package com.tomerandamir.ex7;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaMetadataRetriever;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.StrictMode;
import android.view.View;
import android.webkit.URLUtil;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.HashMap;

public class MainActivity extends AppCompatActivity {


    private Button button;
    private EditText editText ;
    private TextView titleView ;
    private TextView artistView ;
    private String url;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        button = (Button) findViewById(R.id.button);
        editText = (EditText) findViewById(R.id.editText);
        titleView =(TextView) findViewById(R.id.titleView);
        artistView =(TextView) findViewById(R.id.artistView);
        final MediaPlayer mp = new MediaPlayer();
        final MediaMetadataRetriever retriever = new MediaMetadataRetriever();
        url ="";
        button.setOnClickListener(new View.OnClickListener() {
            @Override

            public void onClick(View v) {
                String status = button.getText().toString();
                if (status.compareTo(getApplicationContext().getString(R.string.play)) != 0) {
                    mp.pause();
                    button.setText(getApplicationContext().getString(R.string.play));
                } else {
                    String newUrl = editText.getText().toString();
                    if (url.compareTo(newUrl) !=0) {
                        url = newUrl;
                        mp.reset();
                        if (URLUtil.isHttpUrl(url)) {
                            retriever.setDataSource(url, new HashMap<String, String>());
                            try {
                                mp.setDataSource(url);
                                mp.prepare();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            String artist = retriever.extractMetadata(MediaMetadataRetriever.METADATA_KEY_ARTIST);
                            String titel = retriever.extractMetadata(MediaMetadataRetriever.METADATA_KEY_TITLE);
                            titleView.setText("Artist: " + artist);
                            artistView.setText("Titel: " + titel);
                        } else {

                            Toast.makeText(getApplicationContext(), getApplicationContext().getString(R.string.inv), Toast.LENGTH_SHORT);
                        }
                    }
                        mp.start();
                        button.setText(getApplicationContext().getString(R.string.pause));
                }
            }
        });
    }
}
