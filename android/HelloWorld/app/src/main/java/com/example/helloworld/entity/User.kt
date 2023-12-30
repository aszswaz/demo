package com.example.helloworld.entity

@Suppress("unused")
class User(
    var id: Int,
    var name: String,
    var age: Int,
    var height: Int
) {
    constructor(name: String, age: Int, height: Int) : this(0, name, age, height)
}