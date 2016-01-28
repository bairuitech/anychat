using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace AnyChatSignServer
{
    public class AnyChatSign
    {
        public const string AnyChatSignDll = "anychatsign.dll";

        /// <summary>
        /// 对应用接入信息使用私钥进行签名
        /// </summary>
        /// <param name="userId">用户Id（整形）</param>
        /// <param name="strUserId">用户Id（字符串型）</param>
        /// <param name="appId">应用Id</param>
        /// <param name="privateKey">私钥</param>
        /// <param name="outSignStr">身份签名信息</param>
        /// <param name="signStrSize">保存签名信息的长度</param>
        /// <param name="timeStamp">签名时间戳</param>
        /// <returns>0成功，非0失败</returns>
        [DllImport(AnyChatSignDll, EntryPoint = "AnyChatRsaSign", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AnyChatRsaSign(int userId, StringBuilder strUserId, StringBuilder appId, StringBuilder privateKey, StringBuilder outSignStr, int signStrSize, ref int timeStamp);

        /// <summary>
        /// 对应用接入信息签名使用公钥进行验证
        /// </summary>
        /// <param name="userId">用户Id</param>
        /// <param name="strUserId">用户Id（字符串型）</param>
        /// <param name="appId">应用Id</param>
        /// <param name="signStr">身份签名信息</param>
        /// <param name="timeStamp">签名时间戳</param>
        /// <param name="publicKey">公钥</param>
        /// <returns>验证成功返回0，不成功返回非0</returns>
        [DllImport(AnyChatSignDll, EntryPoint = "AnyChatRsaVerify", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AnyChatRsaVerify(int userId, StringBuilder strUserId, StringBuilder appId, StringBuilder signStr, int timeStamp, StringBuilder publicKey);
    }
}
