package com.tomerandamir.ex9;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;


public class MainActivity extends AppCompatActivity {

    private Button button1;
    private ImageView anime1;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button1 = (Button) findViewById(R.id.button_1);
        anime1 = (ImageView) findViewById(R.id.anime) ;
        anime1.setBackgroundResource (R.drawable.animations);

        final AnimationDrawable ad1 = (AnimationDrawable) anime1.getBackground();
        button1.setOnClickListener(new View.OnClickListener() {
            @Override

            public void onClick(View v) {
                if(button1.getText().toString().compareTo(getApplicationContext().getString(R.string.button_start)) == 0 ) {
                    ad1.start();
                    button1.setText(getApplicationContext().getString(R.string.button_stop));
                }
                else
                {
                    ad1.stop();
                    button1.setText(getApplicationContext().getString(R.string.button_start));
                }
            }
        });

    }
}
