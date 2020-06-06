package com.tomerandamir.ex5;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private Button send_button;
    private EditText editText;
    private TextView viewText;
    public final static String EXTRA_MESSAGE = "calculator";
    public final static String ANSWER = "answer";

    final int CLC_REQUEST = 1;  // The request code

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        send_button = (Button) findViewById(R.id.button1);
        editText = (EditText) findViewById(R.id.editText2);
        viewText = (TextView) findViewById(R.id.textView);
        final Intent intent = new Intent(this, Main2Activity.class);

        send_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = editText.getText().toString();
                intent.putExtra(EXTRA_MESSAGE, message);
                startActivityForResult(intent, CLC_REQUEST);
            }
        });
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == CLC_REQUEST) {
            if (resultCode == RESULT_OK) {
                viewText.setText("The answer is: " + data.getStringExtra(ANSWER));
            }
        }
    }
}
