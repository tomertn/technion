package com.tomerandamir.ex8;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private Button button;
    private TextView select ;
    private TextView selected ;
    private Spinner spinner;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button = (Button) findViewById(R.id.button);
        select =(TextView) findViewById(R.id.select);
        selected =(TextView) findViewById(R.id.selected);
        spinner = (Spinner)findViewById(R.id.spinner);
        ArrayAdapter<String> adp = new ArrayAdapter(getApplicationContext(), android.R.layout.simple_spinner_item, getResources().getStringArray(R.array.Contacts));
        spinner.setAdapter(adp);
        button.setOnClickListener(new View.OnClickListener() {
            @Override

            public void onClick(View v) {
                selected.setText("Contact selected: " + spinner.getSelectedItem().toString());
            }
        });
    }
}
