package example.com.anticheating;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationManager;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.provider.Settings;
import android.telephony.SubscriptionInfo;
import android.telephony.SubscriptionManager;
import android.telephony.TelephonyManager;

import com.tcfintech.sdk.TCAntiFraudAgent;

import org.json.JSONArray;
import org.json.JSONObject;

import java.lang.reflect.Method;
import java.net.NetworkInterface;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.regex.Pattern;

/**
 * 获取设备信息class
 *
 */

public class DeviceInfo {

    /**
     *获取设备IMEI信息，需要申请权限："android.permission.READ_PHONE_STATE"
     *
     * @param context
     *
     * @return Returns Imeis
     * 如果是双卡，List size为2，卡槽1的IMEI对应List[0],卡槽2的IMEI对应List[1]
     * 如果是单卡，List size为1，卡槽1的IMEI对应List[0]
     * 如果是List size为0，没有权限获取IMEI信息
     */
    public static List<String> getImeis(Context context) {
        List<String> imeis = new ArrayList<>();
        if (context == null) {
            return imeis;
        }
        try {
            TelephonyManager tm = (TelephonyManager) context
                    .getSystemService(Context.TELEPHONY_SERVICE);
            if (Build.VERSION.SDK_INT >=22) {
                imeis.add(0,tm.getDeviceId());
                if (Build.VERSION.SDK_INT >=23 && tm.getPhoneCount() == 2) {
                    imeis.add(1,tm.getDeviceId(1));
                }
            } else {
                String imei = tm.getDeviceId();

                if (checkimei(imei.trim())) {
                    imeis.add(0,imei.trim());
                }

                try {
                    TelephonyManager telephonyManager1 = (TelephonyManager) context
                            .getSystemService("phone1");
                    String imeiphone1 = telephonyManager1.getDeviceId();
                    if (imeiphone1 != null && checkimei(imeiphone1)) {
                        if (!imeis.contains(imeiphone1)) {
                            imeis.add(0,imeiphone1);
                        }
                    }
                } catch (Throwable e) {
                    e.printStackTrace();
                }

                try {
                    TelephonyManager telephonyManager2 = (TelephonyManager) context
                            .getSystemService("phone2");
                    String imeiphone2 = telephonyManager2.getDeviceId();
                    if (imeiphone2 != null && checkimei(imeiphone2)) {
                        if (!imeis.contains(imeiphone2)) {
                            imeis.add(1,imeiphone2);
                        }
                    }
                } catch (Throwable e) {
                    e.printStackTrace();
                }
            }
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return imeis;
    }

    /**
     *获取设备AndroidID信息
     *
     * @param context
     *
     * @return Returns Android ID
     */
    public static String getAndroidID(Context context) {
        try {
            return Settings.Secure.getString(context.getContentResolver(),
                    Settings.Secure.ANDROID_ID);
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return null;
    }

    /**
     *获取设备WiFi MAC信息，需要申请权限："android.permission.ACCESS_WIFI_STATE"
     *
     * @param context
     *
     * @return Returns WiFi MAC, 格式例如："68:3E:34:A5:5F:C1"
     */
    public static String getWiFiMac(Context context) {
        String INVALID_MAC = "00:00:00:00:00:00";
        Pattern MAC_PATTERN = Pattern
                .compile("^([0-9A-F]{2}:){5}([0-9A-F]{2})$");
        String mac = null;
        //Android M 以上系统返回默认的MAC 地址
        String defaultMacAddress = "02:00:00:00:00:00";
        try {
            //Android M 上获取 WiFi Mac
            if(Build.VERSION.SDK_INT >=23){
                try {
                    List<NetworkInterface> all = Collections.list(NetworkInterface.getNetworkInterfaces());
                    if(all == null || all.size() <= 0){
                        return defaultMacAddress;
                    }
                    for (NetworkInterface nif : all) {
                        if (!nif.getName().equalsIgnoreCase("wlan0")) continue;
                        byte[] macBytes = nif.getHardwareAddress();
                        if (macBytes == null) {
                            return "";
                        }
                        StringBuilder res1 = new StringBuilder();
                        for (byte b : macBytes) {
                            res1.append(String.format("%02X:",b));
                        }
                        if (res1.length() > 0) {
                            res1.deleteCharAt(res1.length() - 1);
                        }
                        mac = res1.toString().toUpperCase().trim();
                    }
                } catch (Throwable e) {
                    e.printStackTrace();
                }
                return (!(mac == null || "".equals(mac.trim())) ? mac : defaultMacAddress);
            }else{
                if (context.checkCallingOrSelfPermission(
                        android.Manifest.permission.ACCESS_WIFI_STATE) == PackageManager.PERMISSION_GRANTED) {
                    WifiManager wifiManager = (WifiManager) context
                            .getSystemService(Context.WIFI_SERVICE);

                    if (wifiManager.isWifiEnabled()) {
                        WifiInfo info = wifiManager.getConnectionInfo();
                        if (info != null) {
                            mac = info.getMacAddress();
                            if (mac != null) {
                                mac = mac.toUpperCase().trim();
                                if (INVALID_MAC.equals(mac)
                                        || !MAC_PATTERN.matcher(mac).matches()) {
                                    mac = null;
                                }
                            }
                        }
                    }
                }
            }
        } catch (Throwable e) {
            e.printStackTrace();
        }
        return mac;
    }

    /**
     *获取SIM IMSI 信息，需要申请权限："android.permission.READ_PHONE_STATE"
     *
     * @param context
     *
     * @return Returns SIM IMSI
     *
     * List size为2，卡槽1的SIM IMSI对应List[0],卡槽2的SIM IMSI对应List[1]
     * List size为1，卡槽的SIM IMSI对应List[0]
     * 如果卡槽位置对应没有SIM卡，对应值为空字符串""
     * 如果是List size为0，没有权限获取IMSI信息
     */
    public static List<String> getSimSubscriberId(Context context) {
        List<String> imsis = new ArrayList<>();
        if (context == null) {
            return imsis;
        }
        try {
            if (Build.VERSION.SDK_INT >=22) {
                TelephonyManager tm = (TelephonyManager) context
                        .getSystemService(Context.TELEPHONY_SERVICE);
                SubscriptionManager sm = (SubscriptionManager) context.getSystemService(
                        Context.TELEPHONY_SUBSCRIPTION_SERVICE);
                for (int index=0; index < 2; index ++) {
                    SubscriptionInfo info = sm.getActiveSubscriptionInfoForSimSlotIndex(index);
                    if (info != null) {
                        int subId = info.getSubscriptionId();
                        // IMSI
                        Method method = tm.getClass().getMethod("getSubscriberId", int.class);
                        method.setAccessible(true);
                        Object ret = method.invoke(tm, subId);
                        imsis.add(index, ret == null ? "" : (String) ret);
                    }
                }
                return imsis;
            } else {
                TelephonyManager telephonyManager1 = (TelephonyManager) context
                        .getSystemService("phone1");
                if (telephonyManager1 != null) {
                    String imsi1 = telephonyManager1.getSubscriberId();
                    imsis.add(0, imsi1 == null ? "" : imsi1);
                }
                TelephonyManager telephonyManager2 = (TelephonyManager) context
                        .getSystemService("phone2");
                if (telephonyManager1 != null) {
                    String imsi2 = telephonyManager2.getSubscriberId();
                    imsis.add(1, imsi2 == null ? "" : imsi2);
                }
                return imsis;
            }
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return imsis;
    }
    /**
     *获取设备位置经度信息，需要申请权限："android.permission.ACCESS_COARSE_LOCATION"，"android.permission..ACCESS_FINE_LOCATION"
     *
     * @param context
     *
     * @return Returns 经度信息,如果获取失败返回：Float.MAX_VALUE
     */
    public static double getGpsLocationsLng(Context context) {
        Location location = getLocation(context);
        if (location != null) {
            return location.getLongitude();
        }
        return Float.MAX_VALUE;
    }
    /**
     *获取设备位置纬度信息，需要申请权限："android.permission.ACCESS_COARSE_LOCATION"，"android.permission..ACCESS_FINE_LOCATION"
     *
     * @param context
     *
     * @return Returns 纬度信息,如果获取失败返回：Float.MAX_VALUE
     */
    public static double getGpsLocationsLat(Context context) {
        Location location = getLocation(context);
        if (location != null) {
            return location.getLatitude();
        }
        return Float.MAX_VALUE;
    }
    /**
     *获取设备运行列表信息
     *
     * @param context
     *
     * @return Returns 运行列表包名列表,只能获取系统版本21以下设备。
     *                 获取21以上运行列表信息，需要参考集成https://github.com/jaredrummler/AndroidProcesses
     */
    public static List<String> getRunningAppList(Context context) {
        List<String> runningApps = new ArrayList<>();
        if (context == null) {
            return runningApps;
        }
        try {
            List<String> runningAppList = new ArrayList<>();
            if (Build.VERSION.SDK_INT < 21) {
                ActivityManager mgr = (ActivityManager) context
                        .getSystemService(Context.ACTIVITY_SERVICE);
                PackageManager pm = context.getPackageManager();
                List<ActivityManager.RunningAppProcessInfo> processes = mgr
                        .getRunningAppProcesses();
                if (processes != null) {
                    for (ActivityManager.RunningAppProcessInfo appInfo : processes) {
                        String name = appInfo.processName;
                        try {
                            if (pm.getLaunchIntentForPackage(name) != null) {
                                runningAppList.add(name);
                            }
                        } catch (Throwable t) {
                            t.printStackTrace();
                        }
                    }
                }
            }
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return runningApps;
    }
    
    /**
     *获取设备安装列表信息
     *
     * @param context
     *
     * @return Returns 安装列表包名列表
     */
    public static List<String> getAllInstalledApps(Context context) {
        List<String> installedApps = new ArrayList<>();
        try {
            PackageManager pm = context.getPackageManager();
            List<PackageInfo> apps = pm.getInstalledPackages(0);
            if (apps != null) {
                for (PackageInfo app : apps) {
                    installedApps.add(app.packageName);
                }
            }
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return installedApps;
    }
    /**
     *获取设备全部信息
     *
     * @param context
     *
     * @return Returns JSONObject数据，设备数据的Key-value
     * 下面是一个完整的样例：
     */
    /*
    {
      "tdid": "39955a67c15549c73d56e667cbbd5cde9",
      "imeis": [
        "864046008412345",
        "864046008445678"
      ],
      "androidId": "6dd3bbfe6a18f6f",
      "wifiMac": "68:3E:34:A5:5F:C1",
      "basebandVersion": "MOLY.LR11.W1539.MD.MP.V12.2.P72, 2016/06/20 20:39",
      "bootTime": 1506667539150,
      "brand": "Meizu",
      "model": "PRO 6",
      "osName": "android",
      "osVersionName": "Android+6.0",
      "brightness": 200,
      "pixel": "1920*1080*480",
      "supportMobile": true,
      "supportWiFi": true,
      "supportGps": true,
      "supportTelephone": true,
      "supportNfc": true,
      "supportBluetooth": true,
      "supportOtg": true,
      "insertEarphones": true,
      "cpuName": "MT6755M",
      "cpuCoreNum": 8,
      "cpuMaxFreq": 1001000,
      "cpuMinFreq": 156000,
      "cpuCurFreq": 1001000,
      "totalDiskSpace": 64524146,
      "freeDiskSpace": 8524146,
      "totalRamSpace": 3842636,
      "freeRamSpace": 2670968,
      "totalSDCardSpace": 5831260,
      "freeSDCardSpace": 4021584,
      "sim": [
        {
          "simOperatorName": "中国联通",
          "subscriberId": "460014156219904"
        },
        {
          "simOperatorName": "中国移动 — CMCC",
          "subscriberId": "460027013275884"
        }
      ],
      "simType": 13,
      "basestationID": 4300921,
      "basestationSignalLevel": 28,
      "cdmaBasestationLocationLng": 2500000,
      "cdmaBasestationLocationLat": 1200000,
      "wifiNetworksConnected": true,
      "mobileNetworksConnected": false,
      "networkType": "WIFI",
      "wifiIP": "172.30.116.231",
      "batteryLevel": 80,
      "batteryState": 2,
      "locale": "zh_CN",
      "language": "zh",
      "timezoneV": "8.0",
      "gpsLocationsLng": 116.4137,
      "gpsLocationsLat": 39.9497,
      "activityRecognition": {
        "activities": [
          {
            "probility": {
              "5": "0.08",
              "8": "0.00",
              "12": "0.03",
              "13": "0.08",
              "14": "0.00",
              "15": "0.80"
            },
            "ts": 1499747157943
          },
          {
            "probility": {
              "5": "0.08",
              "8": "0.00",
              "12": "0.03",
              "13": "0.08",
              "14": "0.00",
              "15": "0.80"
            },
            "ts": 1499747161181
          }
        ],
        "handHolding": [
          {
            "status": false,
            "ts": 1499747157930
          },
          {
            "status": false,
            "ts": 1499747161162
          },
          {
            "status": true,
            "ts": 1499747164399
          }
        ]
      },
      "runningApps": "[com.example.a, com.example.b, com.example.c, com.example.d]",
      "installedApps": "[com.example.a, com.example.b, com.example.c, com.example.d]"
    }
     */
    public static JSONObject getDeviceData(Context context) {
        JSONObject data = new JSONObject();
        try {
            data.put("tdid", TCAntiFraudAgent.getDeviceId(context));
            data.put("imeis",new JSONArray(getImeis(context)));
            data.put("androidId",getAndroidID(context));
            data.put("wifiMac",getWiFiMac(context));
            data.put("basebandVersion", TCAntiFraudAgent.getBasebandVersion());
            data.put("bootTime", TCAntiFraudAgent.getBootTime());
            data.put("brand",TCAntiFraudAgent.getBrand());
            data.put("model",TCAntiFraudAgent.getModel());
            data.put("osName",TCAntiFraudAgent.getOsName());
            data.put("osVersionName",TCAntiFraudAgent.getOsVersionName());
            data.put("brightness",TCAntiFraudAgent.getBrightness(context));
            data.put("pixel",new StringBuilder().append(TCAntiFraudAgent.getHeightPixels(context)).append("*")
                    .append(TCAntiFraudAgent.getWidthPixels(context)).append("*").append(TCAntiFraudAgent.getDensityDpi(context))
                    .toString());
            data.put("supportMobile",TCAntiFraudAgent.isSupportMobileModule(context));
            data.put("supportWiFi",TCAntiFraudAgent.isSupportWiFiModule(context));
            data.put("supportGps",TCAntiFraudAgent.isSupportGpsModule(context));
            data.put("supportTelephone",TCAntiFraudAgent.isSupportTelephoneModule(context));
            data.put("supportNfc",TCAntiFraudAgent.isSupportNfcModule(context));
            data.put("supportBluetooth",TCAntiFraudAgent.isSupportBluetoothModule(context));
            data.put("supportOtg",TCAntiFraudAgent.isSupportOtgModule(context));
            data.put("insertEarphones",TCAntiFraudAgent.isInsertEarphone(context));
            data.put("cpuName",TCAntiFraudAgent.getCpuName());
            data.put("cpuCoreNum",TCAntiFraudAgent.getCpuCoreNum());
            data.put("cpuMaxFreq",TCAntiFraudAgent.getCpuMaxFreq());
            data.put("cpuMinFreq", TCAntiFraudAgent.getCpuMinFreq());
            data.put("cpuCurFreq",TCAntiFraudAgent.getCpuCurrentFreq());
            data.put("totalDiskSpace",TCAntiFraudAgent.getTotalDiskSpace());
            data.put("freeDiskSpace",TCAntiFraudAgent.getFreeDiskSpace());
            data.put("totalRamSpace",TCAntiFraudAgent.getTotalRamSpace());
            data.put("freeRamSpace",TCAntiFraudAgent.getFreeRamSpace());
            data.put("totalSDCardSpace", TCAntiFraudAgent.getTotalSDCardSpace());
            data.put("freeSDCardSpace",TCAntiFraudAgent.getFreeSDCardSpace());
            List<String> imsis = getSimSubscriberId(context);
            List<String> simOperatorName = TCAntiFraudAgent.getSimOperatorName(context);
            JSONArray sim = new JSONArray();
            try {
                for(int i = 0;i< imsis.size();i++) {
                    JSONObject simInfo = new JSONObject();
                    simInfo.put("simOperatorName",simOperatorName.get(i));
                    simInfo.put("subscriberId",imsis.get(i));
                    sim.put(i,simInfo);
                }
            } catch (Throwable t) {
                t.printStackTrace();
            }
            data.put("sim",sim);
            data.put("simType",TCAntiFraudAgent.getSimType(context));
            data.put("basestationID",TCAntiFraudAgent.getBasestationId(context));
            data.put("basestationSignalLevel",TCAntiFraudAgent.getBasestationSignalLevel(context));
            data.put("cdmaBasestationLocationLng",TCAntiFraudAgent.getCdmaBasestationLocationLng(context));
            data.put("cdmaBasestationLocationLat",TCAntiFraudAgent.getCdmaBasestationLocationLat(context));
            data.put("wifiNetworksConnected",TCAntiFraudAgent.isWiFiDataConnected(context));
            data.put("mobileNetworksConnected",TCAntiFraudAgent.isMobileDataConnected(context));
            data.put("networkType", TCAntiFraudAgent.getCurrentNetworkType(context));
            data.put("wifiIP",TCAntiFraudAgent.getCurrentNetworkIP(context));
            data.put("batteryLevel",TCAntiFraudAgent.getBatteryLevel(context));
            data.put("batteryState",TCAntiFraudAgent.getBatteryState(context));
            data.put("locale",TCAntiFraudAgent.getSystemLocale());
            data.put("language",TCAntiFraudAgent.getSystemLanguage());
            data.put("timezoneV",String.valueOf(TCAntiFraudAgent.getSystemTimezoneV()));
            data.put("gpsLocationsLng",getGpsLocationsLng(context));
            data.put("gpsLocationsLat",getGpsLocationsLat(context));
            data.put("activityRecognition",TCAntiFraudAgent.getActivityRecognition(context));
            data.put("runningApps",getRunningAppList(context).toString());
            data.put("installedApps",getAllInstalledApps(context).toString());

        } catch (Throwable t) {
            t.printStackTrace();
        }
        return data;
    }

    private static Location getLocation(Context context) {
        Location result = null;
        if (context == null) {
            return result;
        }
        if (Build.VERSION.SDK_INT >=23) {
            if (context.checkSelfPermission(android.Manifest.permission.ACCESS_COARSE_LOCATION)
                    != PackageManager.PERMISSION_GRANTED) {
                return result;
            }
        }
        try{
            final LocationManager locationManager = (LocationManager) context.getSystemService(context.LOCATION_SERVICE);
            boolean gps = locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
            boolean network = locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER);
            if (gps || network) {
                result = locationManager.getLastKnownLocation(LocationManager.PASSIVE_PROVIDER);
            }
        }catch (Throwable t){
            t.printStackTrace();
        }
        return result;
    }

    private static Boolean checkimei(String IMEI) {
        try {
            Integer LEN = IMEI.length();
            if (LEN > 10 && LEN < 20 && !checkimeisame(IMEI.trim())) {
                return true;
            }
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return false;
    }

    private static Boolean checkimeisame(String imei) {
        try {
            char firstchar = '0';
            if (imei.length() > 0) {
                firstchar = imei.charAt(0);
            }
            Boolean issame = true;
            for (int i = 0; i < imei.length(); i++) {
                char ch = imei.charAt(i);
                if (firstchar != ch) {
                    issame = false;
                    break;
                }
            }
            return issame;
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return false;
    }
}
