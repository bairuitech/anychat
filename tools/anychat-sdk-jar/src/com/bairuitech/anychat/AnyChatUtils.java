package com.bairuitech.anychat;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * AnyChat工具类
 */

public class AnyChatUtils {



    /**
     * 获取app包名信息
     */
    public static String getAppPackageName(Context context) {
        try {
            String packageName = context.getPackageName();
            return packageName;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "";
    }


    /**
     * 获取app签名md5值
     * 与“keytool -list -keystore D:\Desktop\app_key”‘keytool -printcert *file D:\Desktop\CERT.RSA’获取的md5值一样
     */
    public static String getAppSignMd5Str(Context context) {
        try {
            PackageInfo packageInfo = context.getPackageManager().getPackageInfo(context.getPackageName(), PackageManager.GET_SIGNATURES);
            Signature[] signs = packageInfo.signatures;
            Signature sign = signs[0];
            String signStr = encryptionMD5(sign.toByteArray());
            return signStr;
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
        return "";
    }


    /**
     * MD5加密
     * @param byteStr 需要加密的内容
     * @return 返回 byteStr的md5值
     */
    public static String encryptionMD5(byte[] byteStr) {
        //MessageDigest 类为应用程序提供信息摘要算法的功能，如 MD5 或 SHA 算法。
        MessageDigest messageDigest = null;
        StringBuffer md5StrBuff = new StringBuffer();
        try {
            messageDigest = MessageDigest.getInstance("MD5");
            messageDigest.reset();
            messageDigest.update(byteStr);
            byte[] byteArray = messageDigest.digest();
            for (int i = 0; i < byteArray.length; i++) {
                if (Integer.toHexString(0xFF & byteArray[i]).length() == 1) {
                    md5StrBuff.append("0").append(Integer.toHexString(0xFF & byteArray[i]));
                } else {
                    md5StrBuff.append(Integer.toHexString(0xFF & byteArray[i]));
                }
            }
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return md5StrBuff.toString();
    }


}
