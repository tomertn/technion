package com.tomerandamir.ex5;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class Main2Activity extends AppCompatActivity {
    public final static String EXTRA_MESSAGE = "calculator";
    public final static String ANSWER = "answer";

    private Button pluseButton;
    private Button minButton;
    private Button finishButton;
    private TextView viewText;
    private int num;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        pluseButton = (Button) findViewById(R.id.buttonPluse);
        minButton = (Button) findViewById(R.id.buttonMin);
        finishButton = (Button) findViewById(R.id.buttonRes);

        viewText = (TextView) findViewById(R.id.textView3);
        Intent intent = getIntent();
        String message = intent.getStringExtra(EXTRA_MESSAGE);
        viewText.setText("Currnet value is: " + message);
        num = Integer.parseInt(message);
        final Intent intent2 = getIntent();

        pluseButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                num++;
                viewText.setText("Currnet value is: " + Integer.toString(num));
            }
        });
        minButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                num--;
                viewText.setText("Currnet value is: " + Integer.toString(num));
            }
        });
        finishButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = Integer.toString(num);
                intent2.putExtra(ANSWER, message);
                setResult(RESULT_OK, intent2);
                finish();
            }
        });
    }
}
