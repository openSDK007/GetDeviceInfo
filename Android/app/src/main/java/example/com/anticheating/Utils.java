package example.com.anticheating;

import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Build;

public class Utils {


	public static final boolean isEmpty(String s) {
		return s == null || "".equals(s.trim());
	}


	public static boolean hasPermission(Context context, String permission) {
		try {
			return context.checkCallingOrSelfPermission(permission) == PackageManager.PERMISSION_GRANTED;
		}catch (Throwable t){
			t.printStackTrace();
		}
		return false;
	}

	public static boolean isApiLevelAbove(int level) {
		return Build.VERSION.SDK_INT >= level;
	}
}
