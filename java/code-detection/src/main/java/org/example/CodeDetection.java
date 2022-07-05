package org.example;


import com.zhiwei.crawler.core.HttpBoot;
import com.zhiwei.crawler.core.utils.RequestUtils;
import okhttp3.Request;
import okhttp3.Response;

import java.io.IOException;
import java.time.Duration;

/**
 * 编码探测
 *
 * @author aszswaz
 * @date 2022-07-05 10:30:36
 */
@SuppressWarnings("JavadocDeclaration")
public class CodeDetection {
    @SuppressWarnings("ConstantConditions")
    public static void main(String[] args) throws IOException {
        HttpBoot builder = new HttpBoot.Builder()
                .retryTimes(3)
                .connectTimeout(Duration.ofMinutes(2))
                .readTimeout(Duration.ofMinutes(2))
                .writeTimeout(Duration.ofMinutes(2))
                .detectChineseCharset(true)
                .build();

        Request request = RequestUtils.wrapGet("https://jj.jxnews.com.cn/");
        Response response = builder.syncCall(request);
        String body = response.body().string();
        System.out.println(body);
    }
}
