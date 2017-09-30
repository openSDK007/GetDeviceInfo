package example.com.anticheating;

import android.content.Context;

import com.tendcloud.tenddata.TCAgent;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

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
        imeis.add(0,"864046008412345");
        imeis.add(1,"864046008445678");
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
        return "6dd3bbfe6a18f6f";
    }

    /**
     *获取设备WiFi MAC信息，需要申请权限："android.permission.ACCESS_WIFI_STATE"
     *
     * @param context
     *
     * @return Returns WiFi MAC, 格式例如："68:3E:34:A5:5F:C1"
     */
    public static String getWiFiMac(Context context) {
        return "68:3E:34:A5:5F:C1";
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
        imsis.add(0,"460014156219904");
        imsis.add(1,"460027013275884");
        return imsis;
    }
    /**
     *获取设备位置经度信息，需要申请权限："android.permission.ACCESS_COARSE_LOCATION"，"android.permission..ACCESS_FINE_LOCATION"
     *
     * @param context
     *
     * @return Returns 经度信息
     */
    public static double getGpsLocationsLng(Context context) {
        return 116.4137;
    }
    /**
     *获取设备位置纬度信息，需要申请权限："android.permission.ACCESS_COARSE_LOCATION"，"android.permission..ACCESS_FINE_LOCATION"
     *
     * @param context
     *
     * @return Returns 纬度信息
     */
    public static double getGpsLocationsLat(Context context) {
        return 39.9497;
    }
    /**
     *获取设备运行列表信息
     *
     * @param context
     *
     * @return Returns 运行列表包名列表
     */
    public static List<String> getRunningAppList(Context context) {
        List<String> runningApps = new ArrayList<>();
        runningApps.add("com.example.a");
        runningApps.add("com.example.b");
        runningApps.add("com.example.c");
        runningApps.add("com.example.d");
        return runningApps;
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
      "runningApps": "[com.example.a, com.example.b, com.example.c, com.example.d]"
    }
     */
    public static JSONObject getDeviceData(Context context) {
        JSONObject data = new JSONObject();
        try {
            data.put("tdid", TCAgent.getDeviceId(context));
            data.put("imeis",new JSONArray(getImeis(context)));
            data.put("androidId",getAndroidID(context));
            data.put("wifiMac",getWiFiMac(context));
            data.put("basebandVersion", TCAgent.getBasebandVersion());
            data.put("bootTime", TCAgent.getBootTime());
            data.put("brand",TCAgent.getBrand());
            data.put("model",TCAgent.getModel());
            data.put("osName",TCAgent.getOsName());
            data.put("osVersionName",TCAgent.getOsVersionName());
            data.put("brightness",TCAgent.getBrightness(context));
            data.put("pixel",new StringBuilder().append(TCAgent.getHeightPixels(context)).append("*")
                    .append(TCAgent.getWidthPixels(context)).append("*").append(TCAgent.getDensityDpi(context))
                    .toString());
            data.put("supportMobile",TCAgent.isSupportMobileModule(context));
            data.put("supportWiFi",TCAgent.isSupportWiFiModule(context));
            data.put("supportGps",TCAgent.isSupportGpsModule(context));
            data.put("supportTelephone",TCAgent.isSupportTelephoneModule(context));
            data.put("supportNfc",TCAgent.isSupportNfcModule(context));
            data.put("supportBluetooth",TCAgent.isSupportBluetoothModule(context));
            data.put("supportOtg",TCAgent.isSupportOtgModule(context));
            data.put("insertEarphones",TCAgent.isInsertEarphone(context));
            data.put("cpuName",TCAgent.getCpuName());
            data.put("cpuCoreNum",TCAgent.getCpuCoreNum());
            data.put("cpuMaxFreq",TCAgent.getCpuMaxFreq());
            data.put("cpuMinFreq", TCAgent.getCpuMinFreq());
            data.put("cpuCurFreq",TCAgent.getCpuCurrentFreq());
            data.put("totalDiskSpace",TCAgent.getTotalDiskSpace());
            data.put("freeDiskSpace",TCAgent.getFreeDiskSpace());
            data.put("totalRamSpace",TCAgent.getTotalRamSpace());
            data.put("freeRamSpace",TCAgent.getFreeRamSpace());
            data.put("totalSDCardSpace", TCAgent.getTotalSDCardSpace());
            data.put("freeSDCardSpace",TCAgent.getFreeSDCardSpace());
            List<String> imsis = getSimSubscriberId(context);
            List<String> simOperatorName = TCAgent.getSimOperatorName(context);
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
            data.put("simType",TCAgent.getSimType(context));
            data.put("basestationID",TCAgent.getBasestationId(context));
            data.put("basestationSignalLevel",TCAgent.getBasestationSignalLevel(context));
            data.put("cdmaBasestationLocationLng",TCAgent.getCdmaBasestationLocationLng(context));
            data.put("cdmaBasestationLocationLat",TCAgent.getCdmaBasestationLocationLat(context));
            data.put("wifiNetworksConnected",TCAgent.isWiFiDataConnected(context));
            data.put("mobileNetworksConnected",TCAgent.isMobileDataConnected(context));
            data.put("networkType", TCAgent.getCurrentNetworkType(context));
            data.put("wifiIP",TCAgent.getCurrentNetworkIP(context));
            data.put("batteryLevel",TCAgent.getBatteryLevel(context));
            data.put("batteryState",TCAgent.getBatteryState(context));
            data.put("locale",TCAgent.getSystemLocale());
            data.put("language",TCAgent.getSystemLanguage());
            data.put("timezoneV",String.valueOf(TCAgent.getSystemTimezoneV()));
            data.put("gpsLocationsLng",getGpsLocationsLng(context));
            data.put("gpsLocationsLat",getGpsLocationsLat(context));
            data.put("activityRecognition",TCAgent.getActivityRecognition(context));
            data.put("runningApps",getRunningAppList(context).toString());

        } catch (Throwable t) {
            t.printStackTrace();
        }
        return data;
    }
}
