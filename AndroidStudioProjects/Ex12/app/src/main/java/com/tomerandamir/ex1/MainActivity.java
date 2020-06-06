package com.tomerandamir.ex1;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    private Button change;
    private Button clear;
    private EditText editText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        clear = (Button)findViewById(R.id.clear);
        change = (Button)findViewById(R.id.change);
        editText = (EditText)findViewById(R.id.editText);

        change.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                change.setText(editText.getText());
            }
        });
        clear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                change.setText(R.string.changeString);
            }
        });

    }
}
