package com.example.helloworld;

import static com.example.helloworld.R.id;
import static com.example.helloworld.R.layout;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        super.setContentView(layout.activity_main);

        this.addActivityButton(id.activity_button, ButtonActivity.class);
        this.addActivityButton(id.activity_text_view, TextViewActivity.class);
        this.addActivityButton(id.activity_relative_layout, RelativeLayoutActivity.class);
        this.addActivityButton(id.activity_grid_layout, GridLayoutActivity.class);
        this.addActivityButton(id.activity_scroll_view, ScrollViewActivity.class);
    }

    /**
     * 创建一个切换页面的按钮
     *
     * @param id 按钮的 id
     * @param c  页面对应的 class
     */
    private <T extends AppCompatActivity> void addActivityButton(int id, Class<T> c) {
        final Intent intent = new Intent();
        intent.setClass(this, c);

        super.findViewById(id)
                .setOnClickListener((view) -> {
                    Button btn = (Button) view;
                    Toast.makeText(this, "正在切换到：" + btn.getText(), Toast.LENGTH_SHORT).show();

                    // 打开页面
                    super.startActivity(intent);
                });
    }
}