package com.example.helloworld

import android.graphics.drawable.AnimatedImageDrawable
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ImageView

class ImageViewActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_image_view)

        // 播放 GIF 图片
        val iv = super.findViewById<ImageView>(R.id.image01)
        // iv.setImageResource(R.drawable.barbara)
        val d = iv.drawable
        if (d is AnimatedImageDrawable) d.start()
    }
}