package com.example.helloworld

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.view.View.OnClickListener
import android.view.View.OnLongClickListener
import android.widget.Button
import android.widget.Toast

class ButtonActivity : AppCompatActivity(), OnClickListener, OnLongClickListener {
    private lateinit var btn01: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_button)

        this.initBtn01()
        this.initBtn02()
    }

    /**
     * 点击事件
     */
    override fun onClick(v: View?) {
        val b = v as Button
        // 在屏幕下方显示一个消息提示
        Toast.makeText(this, "你点击了按钮：" + b.text, Toast.LENGTH_SHORT).show()
    }

    /**
     * 用户长按按钮事件
     *
     * @return 是否消费此次事件，
     *          true  表示消费此次事件，不会再继续触发点击事件
     *          false 表示不消费此次事件，会继续触发点击事件
     */
    override fun onLongClick(v: View?): Boolean {
        val b = v as Button
        Toast.makeText(
            this,
            "你长按了按钮：" + b.text,
            Toast.LENGTH_SHORT
        ).show()
        return true
    }

    private fun initBtn01() {
        btn01 = super.findViewById(R.id.btn01)
        btn01.setOnClickListener(this)
        btn01.setOnLongClickListener(this)
    }

    private fun initBtn02() {
        val disable = "禁用“${btn01.text}“按钮"
        val enable = "启用“${btn01.text}“按钮"

        val btn02 = super.findViewById<Button>(R.id.btn02)
        btn02.text = disable
        btn02.setOnClickListener {
            btn01.isEnabled = !btn01.isEnabled
            if (btn01.isEnabled)
                btn02.text = disable
            else
                btn02.text = enable
        }
    }
}