package com.example.jason.passwordprog;

import android.content.DialogInterface;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.content.Intent;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    private Button button;
    private EditText test;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        onButton();
    }

    public void onButton() {
        button = (Button) findViewById(R.id.button);
        test = (EditText) findViewById(R.id.editText);

        button.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                if (test.getText().toString().equals("hackathon")) {
                    Intent launchIntent = getPackageManager().getLaunchIntentForPackage("no.nordicsemi.android.mcp");
                    startActivity(launchIntent);
                }
            }
        });
    }
}
