package com.example.helloworld

import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class TextViewActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_text_view)

        Log.i(TextViewActivity::class.java.name, "on create")

        findViewById<Button>(R.id.text_view_btn).setOnClickListener {
            val text = findViewById<EditText>(R.id.text_view_input).text
            if (text.isBlank()) throw Exception("the entered text cannot be empty")
            findViewById<TextView>(R.id.text_view_label).text = text
        }
    }
}