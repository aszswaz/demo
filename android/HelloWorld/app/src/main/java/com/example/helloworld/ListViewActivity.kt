package com.example.helloworld

import android.os.Bundle
import android.widget.ArrayAdapter
import android.widget.Button
import android.widget.ListView
import androidx.appcompat.app.AppCompatActivity
import com.example.helloworld.adapter.UserAdapter
import com.example.helloworld.entity.User

@Suppress("unused")
class ListViewActivity : AppCompatActivity() {
    private lateinit var listView: ListView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_list_view)

        listView = findViewById(R.id.list_view)

        // setAdapter01()
        setAdapter02()
    }

    /**
     * 使用 Android 自带的元素样式创建表格
     */
    private fun setAdapter01() {
        // 设置列表元素和元素的样式，android.R.layout.simple_list_item_1 是一个内置样式
        val item = ArrayAdapter<String>(this, android.R.layout.simple_list_item_1)
        item.add("item 01")
        item.add("item 02")
        item.add("item 03")
        // 修改列表时自动更新视图
        item.setNotifyOnChange(true)

        listView.adapter = item
        findViewById<Button>(R.id.list_view_btn)
            .setOnClickListener {
                item.add("item ${String.format("%02d", item.count + 1)}")
            }
    }

    /**
     * 使用自定义样式创建表格
     */
    private fun setAdapter02() {
        val adapter = UserAdapter(this)

        val users = arrayListOf(
            User(name = "Jack", age = 10, height = 100),
            User(name = "Jerry", age = 10, height = 110),
            User(name = "tom", age = 10, height = 110),
        )
        for (user in users) {
            adapter.add(user)
        }

        listView.adapter = adapter
    }
}