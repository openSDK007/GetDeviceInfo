package example.com.anticheating;

import android.app.Application;

import com.tendcloud.tenddata.TCAgent;

/**
 * Created by jrr on 2017/9/29.
 */

public class MyApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        //==========__AppAnalytics_start__
        TCAgent.init(this.getApplicationContext(), "Your APP ID", "Your Channel");
        //==========__CaughtExceptions_start__

    }
}
