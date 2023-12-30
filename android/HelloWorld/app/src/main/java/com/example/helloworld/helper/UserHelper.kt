package com.example.helloworld.helper

import android.content.ContentValues
import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import com.example.helloworld.R
import com.example.helloworld.entity.User

class UserHelper(
    val context: Context
) : SQLiteOpenHelper(
    context,
    "user.db",
    null,
    1
) {
    companion object {
        private const val TABLE = "user"
    }

    override fun onCreate(db: SQLiteDatabase?) {
        if (db == null) return
        // 创建 user 表
        val sql = context.resources.getString(R.string.create_table)
        db.execSQL(sql)
    }

    override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {
    }

    fun insert(value: User) {
        val values = ContentValues()
        val db = writableDatabase

        values.put("name", value.name)
        values.put("age", value.age)
        values.put("height", value.height)

        db.insert(TABLE, null, values)
    }

    fun findAll(): List<User> {
        val db = writableDatabase
        val l = arrayListOf<User>()

        val cursor = db.query(
            TABLE,
            arrayOf("id", "name", "age", "height"),
            null,
            null,
            null,
            null,
            "id",
            null
        )
        for (i in 0..<cursor.count) {
            var index = 0
            cursor.moveToNext()
            val id = cursor.getInt(index++)
            val name = cursor.getString(index++)
            val age = cursor.getInt(index++)
            val height = cursor.getInt(index)
            l.add(User(id, name, age, height))
        }
        cursor.close()
        return l
    }
}