using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;

namespace AnyChatSignClient
{
    public class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("请选择Http协议1.Http、2.Https(默认：Http)：");
            string httpProtocol = "http://";
            if (Console.ReadKey().Key == ConsoleKey.D2)
                httpProtocol = "https://";

            Console.WriteLine("请输入签名服务器IP(默认：127.0.0.1)：");
            string serverIP = "127.0.0.1";
            if (Console.ReadKey().Key != ConsoleKey.Enter)
                serverIP = Console.ReadLine();

            Console.WriteLine("请输入签名服务器端口（默认：8980）：");
            string serverPort = ((int)8980).ToString();
            if (Console.ReadKey().Key != ConsoleKey.Enter)
                serverPort = Console.ReadLine();

            //签名服务器Url
            string signServerUrl = httpProtocol + serverIP + ":" + serverPort;

            Console.WriteLine("请输入用户Id(userId)：(默认：10001）：");
            string userId = "1001";
            if (Console.ReadKey().Key != ConsoleKey.Enter)
                userId = Console.ReadLine();

            Console.WriteLine("请输入应用Id(appId)(默认：0B22DFBA-F559-40FC-B584-FAB11380BE7D)：");
            string appId = "0B22DFBA-F559-40FC-B584-FAB11380BE7D";
            if (Console.ReadKey().Key != ConsoleKey.Enter)
                appId = Console.ReadLine();

            //传入请求参数
            string reqParam = "userId=" + userId + "&appId=" + appId;
            string responseResult = HttpPost(signServerUrl, reqParam);

            if (!String.IsNullOrEmpty(responseResult))
            {
                JsonObject jsonObj = ToClass<JsonObject>(responseResult);

                Console.WriteLine("签名返回errorcode为：" + jsonObj.errorcode);
                Console.WriteLine("签名返回timestamp为：" + jsonObj.timestamp);
                Console.WriteLine("签名返回signStr为：" + jsonObj.sigStr);
            }
            else
            {
                Console.WriteLine("签名返回空字符串");
            }
            System.Console.WriteLine("=============按任意键退出！=============");
            Console.ReadKey();

        }

        /// <summary>  
        /// POST请求与获取结果  
        /// </summary>  
        public static string HttpPost(string Url, string postDataStr)
        {
            string retVal = string.Empty;
            try
            {
                HttpWebRequest request = (HttpWebRequest)WebRequest.Create(Url);
                request.Method = "POST";
                request.ContentType = "application/x-www-form-urlencoded";
                //request.ContentLength = postDataStr.Length;
                StreamWriter writer = new StreamWriter(request.GetRequestStream(), Encoding.ASCII);
                writer.Write(postDataStr);
                writer.Flush();

                HttpWebResponse response = (HttpWebResponse)request.GetResponse();
                string encoding = response.ContentEncoding;
                if (encoding == null || encoding.Length < 1)
                {
                    encoding = "UTF-8"; //默认编码  
                }
                StreamReader reader = new StreamReader(response.GetResponseStream(), Encoding.GetEncoding(encoding));
                retVal = reader.ReadToEnd();
            }
            catch (Exception ex)
            {
                System.Console.WriteLine("AnyChatSignClient has exception, message: " + ex.Message);
            }
            return retVal;
        }

        /// <summary>
        /// 将Json字符串转化成对象
        /// </summary>
        /// <typeparam name="T">转换的对象类型</typeparam>
        /// <param name="output">json字符串</param>
        /// <returns></returns>
        public static T ToClass<T>(string output)
        {
            object result;
            DataContractJsonSerializer outDs = new DataContractJsonSerializer(typeof(T));
            using (MemoryStream outMs = new MemoryStream(Encoding.UTF8.GetBytes(output)))
            {
                result = outDs.ReadObject(outMs);
            }
            return (T)result;
        }
    }

    /// <summary>
    /// 签名信息类
    /// </summary>
    [DataContract]
    class JsonObject
    {
        [DataMember]
        public int errorcode { get; set; }
        [DataMember]
        public int timestamp { get; set; }
        [DataMember]
        public string sigStr { get; set; }
    }
}
