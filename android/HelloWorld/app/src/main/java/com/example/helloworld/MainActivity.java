package com.example.helloworld;

import static com.example.helloworld.R.id;
import static com.example.helloworld.R.layout;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    public static final String TAG = MainActivity.class.getSimpleName();

    /**
     * 创建 activity
     * activity 的生命周期如下：
     * onCreate -> onStart -> onResume -> onPause -> onStop -> onDestroy
     * onCreate  是开始创建 activity
     * onStart   进入 activity，或 APP 回到前台
     * onPause   离开 activity，或 APP 被切换到后台
     * onDestroy 是销毁 activity 或退出 APP
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        super.setContentView(layout.activity_main);
        Log.d(TAG, "onCreate");

        this.addActivityButton(id.activity_button, ButtonActivity.class);
        this.addActivityButton(id.activity_text_view, TextViewActivity.class);
        this.addActivityButton(id.activity_relative_layout, RelativeLayoutActivity.class);
        this.addActivityButton(id.activity_grid_layout, GridLayoutActivity.class);
        this.addActivityButton(id.activity_scroll_view, ScrollViewActivity.class);
        this.addActivityButton(id.activity_image_view, ImageViewActivity.class);
        this.addActivityButton(id.activity_list_view, ListViewActivity.class);
        this.addActivityButton(id.activity_sqlite, SQLiteActivity.class);
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.d(TAG, "onStart");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG, "onResume");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.d(TAG, "onPause");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.d(TAG, "onStop");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "onDestroy");
    }

    /**
     * 创建一个切换页面的按钮
     *
     * @param id 按钮的 id
     * @param c  页面对应的 class
     */
    private <T extends AppCompatActivity> void addActivityButton(int id, Class<T> c) {
        final Intent intent = new Intent(this, c);
        super.findViewById(id)
                .setOnClickListener(view -> {
                    Button btn = (Button) view;
                    Toast.makeText(this, "正在切换到：" + btn.getText(), Toast.LENGTH_SHORT).show();
                    // 打开页面
                    super.startActivity(intent);
                });
    }
}