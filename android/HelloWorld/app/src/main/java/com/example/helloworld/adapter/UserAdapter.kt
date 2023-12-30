package com.example.helloworld.adapter

import android.annotation.SuppressLint
import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.BaseAdapter
import android.widget.TextView
import com.example.helloworld.R
import com.example.helloworld.entity.User

class UserAdapter(
    context: Context
) : BaseAdapter() {
    private val list: ArrayList<User> = ArrayList()
    private val inflater = LayoutInflater.from(context)

    override fun getCount(): Int {
        return list.size
    }

    override fun getItem(position: Int): User {
        return list[position]
    }

    override fun getItemId(position: Int): Long {
        return position.toLong()
    }

    /**
     * 生成列表的元素视图
     */
    @SuppressLint("ViewHolder", "SetTextI18n")
    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        val user = list[position]
        val view = inflater.inflate(R.layout.user_element, parent, false)

        val nameView = view.findViewById<TextView>(R.id.user_name)
        val detailView = view.findViewById<TextView>(R.id.user_detail)
        nameView.text = user.name
        detailView.text = "age: ${user.age}, height: ${user.height}"
        return view
    }

    fun add(v: User) {
        list.add(v)
        notifyDataSetChanged()
    }

    fun addAll(l: List<User>) {
        list.addAll(l)
        notifyDataSetChanged()
    }

    fun clear() {
        list.clear()
        notifyDataSetChanged()
    }
}