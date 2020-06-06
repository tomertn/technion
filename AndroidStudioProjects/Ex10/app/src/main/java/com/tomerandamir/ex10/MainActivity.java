package com.tomerandamir.ex10;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.StrictMode;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    private EditText editText ;
    private WebView webView ;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        editText = (EditText) findViewById(R.id.editText);
        webView = (WebView) findViewById(R.id.webView);
    }
    public void Gointernet(View view) {

        webView.setWebViewClient(new WebViewClient());
        webView.loadUrl(editText.getText().toString());
    }
}
