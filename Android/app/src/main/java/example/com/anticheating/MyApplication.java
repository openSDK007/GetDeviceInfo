package example.com.anticheating;

import android.app.Application;

import com.tcfintech.sdk.TCAntiFraudAgent;

/**
 * Created by jrr on 2017/9/29.
 */

public class MyApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();

        TCAntiFraudAgent.init(this.getApplicationContext(), "Your APP ID", "Your Channel");


    }
}
