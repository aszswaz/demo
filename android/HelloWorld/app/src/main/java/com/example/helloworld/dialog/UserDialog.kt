package com.example.helloworld.dialog

import android.app.AlertDialog
import android.app.Dialog
import android.content.DialogInterface
import android.os.Bundle
import android.view.View
import android.widget.EditText
import androidx.fragment.app.DialogFragment
import com.example.helloworld.R
import com.example.helloworld.adapter.UserAdapter
import com.example.helloworld.entity.User
import com.example.helloworld.helper.UserHelper

class UserDialog(
    private val helper: UserHelper,
    private val adapter: UserAdapter
) : DialogFragment(), DialogInterface.OnClickListener {
    private lateinit var view: View

    override fun onCreateDialog(savedInstanceState: Bundle?): Dialog {
        activity ?: throw IllegalStateException("Activity cannot be null")

        val builder = AlertDialog.Builder(activity)
        view = View.inflate(activity, R.layout.user_create, null)

        builder.setPositiveButton("保存", this)
        builder.setNegativeButton("取消") { dialog, _ -> dialog.cancel() }

        builder.setView(view)
        return builder.create()
    }

    override fun onClick(dialog: DialogInterface?, which: Int) {
        val name = view.findViewById<EditText>(R.id.user_name).text.toString()
        val age = view.findViewById<EditText>(R.id.user_age).text.toString().toInt()
        val height = view.findViewById<EditText>(R.id.user_height).text.toString().toInt()
        helper.insert(User(name, age, height))
        dialog?.cancel()
        // 将数据库中的数据展示到页面
        adapter.clear()
        adapter.addAll(helper.findAll())
    }
}
