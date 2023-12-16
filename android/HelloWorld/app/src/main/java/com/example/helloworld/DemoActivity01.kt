package com.example.helloworld

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.TextView

class DemoActivity01 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_demo01)

        Log.i(DemoActivity01::class.java.name, "on create")

        findViewById<Button>(R.id.activity_demo01_btn).setOnClickListener {
            val text = findViewById<EditText>(R.id.activity_demo01_input).text
            if (text.isBlank()) throw Exception("the entered text cannot be empty")
            findViewById<TextView>(R.id.activity_demo01_label).text = text
        }
    }
}