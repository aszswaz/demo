package com.example.helloworld

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.os.Bundle
import android.util.Log
import android.view.View
import android.view.View.OnClickListener
import android.widget.Button
import android.widget.ListView
import androidx.appcompat.app.AppCompatActivity
import com.example.helloworld.adapter.UserAdapter
import com.example.helloworld.dialog.UserDialog
import com.example.helloworld.helper.UserHelper

class SQLiteActivity : AppCompatActivity(), OnClickListener {

    private lateinit var helper: UserHelper
    private lateinit var adapter: UserAdapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_sqlite)

        helper = UserHelper(this)
        adapter = UserAdapter(this)
        adapter.addAll(helper.findAll())
        val view = findViewById<ListView>(R.id.user_list)
        view.adapter = adapter
        val btn = findViewById<Button>(R.id.user_create)
        btn.setOnClickListener(this)
    }

    override fun onStart() {
        super.onStart()
    }

    override fun onStop() {
        super.onStop()
        if (::helper.isInitialized) helper.close()
    }

    override fun onClick(v: View?) {
        // 创建用户
        val dialog = UserDialog(helper, adapter)
        dialog.show(supportFragmentManager, "dialog")
    }
}