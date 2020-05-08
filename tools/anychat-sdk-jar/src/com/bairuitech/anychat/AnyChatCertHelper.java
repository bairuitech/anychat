package com.bairuitech.anychat;

import android.annotation.SuppressLint;
import android.os.Build;
import android.util.Base64;
import android.util.Log;

import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.security.KeyFactory;
import java.security.Principal;
import java.security.PublicKey;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.security.interfaces.RSAPrivateKey;
import java.security.interfaces.RSAPublicKey;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.crypto.Cipher;

/**
 * 获取数字证书相关信息，证书有效性验证，RSA加密和解密功能
 */
public class AnyChatCertHelper {
    private static final int AC_RSA_PKCS1_OAEP_PADDING_SHE256 = 100;
    private static final String RSA_OAEP_SHA256_PADDING = "RSA/ECB/OAEPWithSHA256AndMGF1Padding";//加密填充方式
    private static final String RSA = "RSA";// 非对称加密密钥算法
    private static String beginCertificate = "-----BEGIN CERTIFICATE-----";
    private static String endCertificate = "-----END CERTIFICATE-----";

    public static int GetRSAPaddingMode(int flags) {
        return AC_RSA_PKCS1_OAEP_PADDING_SHE256;
    }

    /**
     * @param certBytes，数字证书crt传入的byte数组
     * @return
     */
    public static String GetX509CertInfo(byte[] certBytes) {
        JSONObject certificateInfo = null;
        String key;
        CertificateFactory certificatefactory;
        X509Certificate cert;
        InputStream input;
        PublicKey pk;
        try {
            certificatefactory = CertificateFactory.getInstance("X.509");
            input = new ByteArrayInputStream(certBytes);
            cert = (X509Certificate) certificatefactory.generateCertificate(input);
            pk = cert.getPublicKey();
            if (certificateInfo == null) {
                certificateInfo = new JSONObject();
            }
            Date notBefore = cert.getNotBefore();
            long notBeforeDate = notBefore.getTime() / 1000;
            certificateInfo.put("Before", notBeforeDate);
            Date notAfter = cert.getNotAfter();
            long notAfterDate = notAfter.getTime() / 1000;
            certificateInfo.put("After", notAfterDate);
            String name = cert.getSubjectDN().getName();
            String domain = cropString(name);
            certificateInfo.put("OwnerUrl", domain);
            key = Base64.encodeToString(pk.getEncoded(), Base64.NO_WRAP);
            certificateInfo.put("PubKey", key);
            return certificateInfo.toString();
        } catch (Exception e) {
            Log.e("AnyChatCertHelper", "GetX509CertInfo failure", e.fillInStackTrace());
        }
        return null;
    }

    /**
     * 使用正则获取特定的字符串
     *
     * @param s
     * @return
     */
    private static String cropString(String s) {
        StringBuilder stringBuilder = new StringBuilder();
        Pattern p = Pattern.compile("(?<=CN\\=).*?(?=,|(s*$))");
        Matcher m = p.matcher(s);
        while (m.find()) {
            stringBuilder.append(m.group());
        }
        return stringBuilder.toString();
    }

    /**
     * 证书有效性验证
     *
     * @param certChain
     * @param cert2Verify
     * @return
     */
    public static int VerifyX509Cert(byte[] certChain, byte[] cert2Verify) {
        List<X509Certificate> certs = new ArrayList<X509Certificate>();
        CertificateFactory certificatefactory;
        X509Certificate cert;
        InputStream input;
        int result = 0;
        String chainString = null;
        String strCertChain = new String(certChain);
        if (strCertChain != null && strCertChain.length() > 0) {
            String[] strings = strCertChain.split(beginCertificate);
            int length = strings.length;
            chainString = beginCertificate + strings[length - 1];
        }
        do {
            try {
                String[] splitCert = splitCert(chainString.getBytes());
                if (Build.VERSION.SDK_INT >= 27/*Build.VERSION_CODES.P*/) {
                    certificatefactory = CertificateFactory.getInstance("X.509");
                } else {
                    certificatefactory = CertificateFactory.getInstance("X.509", "BC");
                }

                input = new ByteArrayInputStream(cert2Verify);
                cert = (X509Certificate) certificatefactory.generateCertificate(input);
                certs.add(cert);
                StringBuilder stringBuilder;
                for (String b : splitCert) {
                    if (b.indexOf(beginCertificate) == -1) {
                        break;
                    }
                    stringBuilder = new StringBuilder();
                    stringBuilder.append(b);
                    if (!b.endsWith(endCertificate)) {
                        stringBuilder.append(endCertificate);
                    }
                    byte[] certByte = stringBuilder.toString().getBytes();
                    input = new ByteArrayInputStream(certByte);

                    try {
                        cert = (X509Certificate) certificatefactory.generateCertificate(input);
                        certs.add(cert);
                    } catch (Exception e) {
                        Log.e("AnyChatCertHelper", "VerifyX509Cert parse failure", e.fillInStackTrace());
                    }
                }
                List<X509Certificate> certOrder = order(certs);
                if (certOrder.size() <= 0) {
                    break;
                }
                X509Certificate lastCert = certOrder.get(certOrder.size() - 1);
                if (!lastCert.getIssuerDN().equals(lastCert.getSubjectDN())) {
                    X509Certificate rootCert = getRootCert(lastCert);
                    if (rootCert == null) {
                        result = -1;
                        break;
                    }
                    certOrder.add(rootCert);
                }
                verifyCerts(certOrder);
            } catch (Exception e) {
                Log.e("AnyChatCertHelper", "VerifyX509Cert failure", e.fillInStackTrace());
                result = -1;
                break;
            }
            result = 0;
            break;
        } while (false);
        return result;
    }

    /**
     * 将证书链拆分
     *
     * @param certChain
     * @return
     */
    private static String[] splitCert(byte[] certChain) {
        String s = new String(certChain);
        String[] cert = s.split(endCertificate);
        return cert;
    }

    /**
     * 找到证书父节点
     *
     * @param parents
     * @param child
     * @return
     */
    private static X509Certificate findParent(List<X509Certificate> parents, X509Certificate child) {
        Principal issuerDN = child.getIssuerDN();
        Principal subjectDN = child.getSubjectDN();
        if (issuerDN.equals(subjectDN)) {
            return null;
        }
        for (int i = 0; i < parents.size(); i++) {
            X509Certificate parent = parents.get(i);
            if (parent == null) {
                break;
            }
            if (issuerDN.equals(parent.getSubjectDN())) {
                return parent;
            }
        }
        return null;
    }

    /**
     * 排序
     *
     * @param certss
     * @return
     */
    private static List<X509Certificate> order(List<X509Certificate> certss) {
        List<X509Certificate> certInOder = new ArrayList<X509Certificate>();
        X509Certificate cert2Verify = certss.get(0);
        certInOder.add(cert2Verify);
        for (int i = 0; i < certss.size(); i++) {
            X509Certificate parent = findParent(certss, cert2Verify);
            if (parent == null) {
                break;
            } else {
                certInOder.add(parent);
                cert2Verify = parent;
            }
        }
        return certInOder;
    }

    /**
     * 证书有效性验证
     *
     * @param certs
     * @throws Exception
     */
    private static void verifyCerts(List<X509Certificate> certs) throws Exception {
        int n = certs.size();
        for (int i = 0; i < n - 1; i++) {
            X509Certificate cert = certs.get(i);
            X509Certificate issuer = (X509Certificate) certs.get(i + 1);
            cert.verify(issuer.getPublicKey());
        }
        X509Certificate last = (X509Certificate) certs.get(n - 1);
        last.verify(last.getPublicKey());
    }

    /**
     * 用公钥对字符串进行加密
     *
     * @param data 数据
     */
    @SuppressLint("TrulyRandom")
    public static byte[] RSA_PublicEncrypt(byte[] data, byte[] publicKey) {
        try {
            byte[] decodePublicKey = Base64.decode(publicKey, Base64.NO_WRAP);
            X509EncodedKeySpec keySpec = new X509EncodedKeySpec(decodePublicKey);
            KeyFactory kf = KeyFactory.getInstance(RSA);
            RSAPublicKey keyPublic = (RSAPublicKey) kf.generatePublic(keySpec);
            int keySize = keyPublic.getModulus().bitLength();
            Cipher cipher = Cipher.getInstance(RSA_OAEP_SHA256_PADDING);
            cipher.init(Cipher.ENCRYPT_MODE, keyPublic);
            return rsaSplitCodec(Cipher.ENCRYPT_MODE, data, keySize, cipher);
        } catch (Exception e) {
            Log.e("AnyChatCertHelper", "RSA_PublicEncrypt failure", e.fillInStackTrace());
        }
        return null;
    }


    /**
     * 私钥加密
     *
     * @param data       待加密数据
     * @param privateKey 密钥
     * @return byte[] 加密数据
     */
    @SuppressLint("TrulyRandom")
    public static byte[] RSA_PrivateEncrypt(byte[] data, byte[] privateKey) {
        try {
            byte[] key = getKey(privateKey);
            byte[] decodePrivateKey = Base64.decode(key, Base64.NO_WRAP);
            PKCS8EncodedKeySpec keySpec = new PKCS8EncodedKeySpec(decodePrivateKey);
            KeyFactory kf = KeyFactory.getInstance(RSA);
            RSAPrivateKey keyPrivate = (RSAPrivateKey) kf.generatePrivate(keySpec);
            int keySize = keyPrivate.getModulus().bitLength();
            Cipher cipher = Cipher.getInstance(RSA_OAEP_SHA256_PADDING);
            cipher.init(Cipher.ENCRYPT_MODE, keyPrivate);
            return rsaSplitCodec(Cipher.ENCRYPT_MODE, data, keySize, cipher);
        } catch (Exception e) {
            Log.e("AnyChatCertHelper", "RSA_PrivateEncrypt failure", e.fillInStackTrace());
        }
        return null;
    }

    /**
     * 公钥解密
     *
     * @param data      待解密数据
     * @param publicKey 密钥
     * @return byte[] 解密数据
     */
    @SuppressLint("TrulyRandom")
    public static byte[] RSA_PublicDecrypt(byte[] data, byte[] publicKey) {
        try {
            byte[] decodePublicKey = Base64.decode(publicKey, Base64.NO_WRAP);
            X509EncodedKeySpec keySpec = new X509EncodedKeySpec(decodePublicKey);
            KeyFactory kf = KeyFactory.getInstance(RSA);
            RSAPublicKey keyPublic = (RSAPublicKey) kf.generatePublic(keySpec);
            int keySize = keyPublic.getModulus().bitLength();
            Cipher cipher = Cipher.getInstance(RSA_OAEP_SHA256_PADDING);
            cipher.init(Cipher.DECRYPT_MODE, keyPublic);
            return rsaSplitCodec(Cipher.DECRYPT_MODE, data, keySize, cipher);
        } catch (Exception e) {
            Log.e("AnyChatCertHelper", "RSA_PublicDecrypt failure", e.fillInStackTrace());
        }
        return null;
    }

    /**
     * 使用私钥进行解密
     */
    @SuppressLint("TrulyRandom")
    public static byte[] RSA_PrivateDecrypt(byte[] data, byte[] privateKey) {
        try {
            byte[] key = getKey(privateKey);
            byte[] decodePrivateKey = Base64.decode(key, Base64.NO_WRAP);
            PKCS8EncodedKeySpec keySpec = new PKCS8EncodedKeySpec(decodePrivateKey);
            KeyFactory kf = KeyFactory.getInstance(RSA);
            RSAPrivateKey keyPrivate = (RSAPrivateKey) kf.generatePrivate(keySpec);
            int keySize = keyPrivate.getModulus().bitLength();
            Cipher cipher = Cipher.getInstance(RSA_OAEP_SHA256_PADDING);
            cipher.init(Cipher.DECRYPT_MODE, keyPrivate);
            return rsaSplitCodec(Cipher.DECRYPT_MODE, data, keySize, cipher);
        } catch (Exception e) {
            Log.e("AnyChatCertHelper", "RSA_PrivateDecrypt failure", e.fillInStackTrace());
        }
        return null;
    }

    /**
     * 对字符串进行分段加密或解密
     */
    private static byte[] rsaSplitCodec(int mode, byte[] data, int keySize, Cipher cipher) throws Exception {
        int dataLen = data.length;
        int maxBlock;
        if (mode == Cipher.DECRYPT_MODE) {
            maxBlock = keySize / 8;
        } else {
            maxBlock = (keySize / 8) - 66;
        }
        if (dataLen <= maxBlock) {
            return cipher.doFinal(data);
        }
        List<Byte> allBytes = new ArrayList<Byte>();
        int bufIndex = 0;
        byte[] buf = new byte[maxBlock];
        for (int i = 0; i < dataLen; i++) {
            buf[bufIndex] = data[i];
            if ((++bufIndex == maxBlock) || (i == dataLen - 1)) {
                byte[] encryptBytes = cipher.doFinal(buf);
                for (byte b : encryptBytes) {
                    allBytes.add(b);
                }
                bufIndex = 0;
                if (i == dataLen - 1) {
                    buf = null;
                } else {
                    buf = new byte[Math.min(maxBlock, dataLen - i - 1)];
                }
            }
        }
        byte[] bytes = new byte[allBytes.size()];
        {
            int i = 0;
            for (Byte b : allBytes) {
                bytes[i++] = b.byteValue();
            }
        }
        return bytes;
    }

    /**
     * 获取特定的字符串
     *
     * @param s
     * @return
     */
    private static byte[] getKey(byte[] s) {
        String keyContent = new String(s);
        String key = keyContent.substring(keyContent.indexOf("Y-----") + 7, keyContent.lastIndexOf("-----E"));
        return key.getBytes();
    }

    /**
     * 获取系统根证书
     *
     * @param selfCert
     * @return
     */
    public static X509Certificate getRootCert(X509Certificate selfCert) {
        try {
            File mDir = new File(System.getenv("ANDROID_ROOT") + "/etc/security/cacerts");
            X509Certificate mCertificates = null;
            if (mDir != null && mDir.isDirectory()) {
                for (String caFile : mDir.list()) {
                    X509Certificate cert = readCertificate(mDir, caFile);
                    if (cert == null) {
                        break;
                    }
                    String issuerDN = cropString(selfCert.getIssuerDN().getName());
                    String subjectDN = cropString(cert.getSubjectDN().getName());
                    if (subjectDN.equals(issuerDN)) {
                        mCertificates = cert;
                        break;
                    }
                }
            }
            return mCertificates;
        } catch (Exception e) {
            Log.e("AnyChatCertHelper", "Get RootCert failure", e.fillInStackTrace());
        }
        return null;
    }

    private static X509Certificate readCertificate(File mDir, String file) {
        CertificateFactory mCertFactory = null;
        InputStream is = null;
        X509Certificate x509Certificate = null;
        try {
            is = new BufferedInputStream(new FileInputStream(new File(mDir, file)));
            mCertFactory = CertificateFactory.getInstance("X.509");
            x509Certificate = (X509Certificate) mCertFactory.generateCertificate(is);
            is.close();
            return x509Certificate;
        } catch (Exception e) {
            Log.e("AnyChatCertHelper", "Read Certificate failure", e.fillInStackTrace());
        }
        return null;
    }

}
