package com.example.helloworld

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        findViewById<Button>(R.id.activity_demo01)
            .setOnClickListener {
                val intent = Intent()
                intent.setClass(this, DemoActivity01::class.java)
                startActivity(intent)
            }
    }
}