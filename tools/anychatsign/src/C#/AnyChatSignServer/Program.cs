using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;
using Newtonsoft.Json;

namespace AnyChatSignServer
{
    public class Program
    {
        static HttpListener listener;
        static String PrivateRsaKeyFileName = "private_rsa.pem";

        public static void Main(string[] args)
        {
            IniFileHelper iniHelper = new IniFileHelper(Directory.GetCurrentDirectory() + "\\AnyChatSignServer.ini");

            //读取私钥文件名
            StringBuilder strPrivateKeyFilename = new StringBuilder(128);
            iniHelper.GetIniString("Base Settings", "privateKeyFileName", "private_rsa.pem", strPrivateKeyFilename, strPrivateKeyFilename.Capacity);
            PrivateRsaKeyFileName = strPrivateKeyFilename.ToString();

            StringBuilder strIP = new StringBuilder(32);
            iniHelper.GetIniString("Base Settings", "HTTPListenServerIP", "127.0.0.1", strIP, strIP.Capacity);
            String ServerIP = strIP.ToString();

            StringBuilder strPort = new StringBuilder(32);
            iniHelper.GetIniString("Base Settings", "HTTPListenPort", "8980", strPort, strPort.Capacity);
            String ServerPort = strPort.ToString();

            String httpProtocol = "http://";

            int isHttps = iniHelper.GetIniInt("Base Settings", "HTTPListenPort", 0);
            if (isHttps == 1)
            {
                httpProtocol = "https://";
            }

            String listenerURL = httpProtocol + ServerIP + ":" + ServerPort + "/";

            listener = new HttpListener();
            listener.Prefixes.Add(listenerURL);
            try
            {
                listener.Start();
                Console.WriteLine("已启动HTTP服务，URL为：" + listenerURL);
                listener.BeginGetContext(new AsyncCallback(GetContextCallBack), listener);
            }
            catch (Exception e)
            {
                System.Console.WriteLine("AnyChatSignServer has exception, message: " + e.StackTrace);
            }
            
            System.Console.WriteLine("=============按字母“Q”键退出！=============");
            while (true)
            {
                ConsoleKey InputKey = Console.ReadKey().Key;

                if (InputKey == ConsoleKey.Q)
                {
                    break;
                }
            }    

        }


        public static void GetContextCallBack(IAsyncResult ar)
        {
            try
            {
                listener = ar.AsyncState as HttpListener;
                HttpListenerContext context = listener.EndGetContext(ar);
                //再次监听请求
                listener.BeginGetContext(new AsyncCallback(GetContextCallBack), listener);
                //处理请求,返回请求处理结果
                string reqResult = Request(context.Request);
                //输出请求返回结果
                Response(context.Response, reqResult);
            }
            catch(Exception ex) {
                System.Console.WriteLine("AnyChatSignServer has exception, message: " + ex.StackTrace);
               
            }
        }

        /// <summary>
        /// 处理输入参数
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        static string Request(HttpListenerRequest request)
        {
            string reqResult = "Welcome to AnyChatSignServer!";

            if (request.HttpMethod.ToLower().Equals("get"))
            {
                //GET请求处理
                if (!string.IsNullOrEmpty(request.QueryString["anychat"]))
                    reqResult = request.QueryString["anychat"];
            }
            else if (request.HttpMethod.ToLower().Equals("post"))
            {
                //这是在POST请求时必须传参的判断
                //POST请求后的响应格式为：{"errorcode":0, "timestamp":1452934106, "sigStr":"xxx"}
                if (!request.HasEntityBody)
                {
                    reqResult = JsonConvert.SerializeObject(new { errorcode = 218, timestamp = 0, sigStr = "" });
                    return reqResult;
                }
                //POST请求处理
                Stream SourceStream = request.InputStream;
                byte[] currentChunk = ReadLineAsBytes(SourceStream);
                //获取数据中有空白符需要去掉，输出的就是post请求的参数字符串 如：userId=10001&appId=90A9545C-30F7-4F5A-8B56-9CB111706A24
                string reqParam = Encoding.Default.GetString(currentChunk).Replace("", "");

                //在实际生产环境中可以考虑将AppId放在服务端，在ini文件中参数项来配置
                if (reqParam.ToUpper().IndexOf("USERID") < 0 || reqParam.ToUpper().IndexOf("APPID") < 0)
                {
                    //传入的参数值有错误
                    reqResult = JsonConvert.SerializeObject(new { errorcode = 219, timestamp = 0, sigStr = "" });

                    return reqResult;
                }

                //处理请求参数
                string[] reqParamArray = null;
                string userId = "0";
                string appId = string.Empty;

                if (reqParam.IndexOf('&') > 0){
                    reqParamArray = reqParam.Split(new char[]{'&'}, StringSplitOptions.RemoveEmptyEntries);
                }
                if (reqParam.Length <= 0)
                {
                    //传入的参数有错误
                    reqResult = JsonConvert.SerializeObject(new { errorcode = 219, timestamp = 0, sigStr = "" });
                    return reqResult;
                }
                for (int i = 0; i < reqParamArray.Length; i++)
                {
                    string param = reqParamArray[i].ToString().ToUpper();
                    if (param.IndexOf("USERID") >= 0)
                    {
                        userId = reqParamArray[i].ToString().Substring(param.ToString().IndexOf("=") + 1);
                    }
                    if (param.IndexOf("APPID") >= 0)
                    {
                        appId = reqParamArray[i].ToString().Substring(param.ToString().IndexOf("=") + 1);
                    }
                }

                string privateKeyFilePath = Directory.GetCurrentDirectory() + "\\" + PrivateRsaKeyFileName;
                if (FileHelper.IsExistFile(privateKeyFilePath))
                {
                    string privateKey = FileHelper.FileToString(privateKeyFilePath);
                    reqResult = getRsaSign(userId, appId, privateKey);
                }
                else
                {
                    System.Console.WriteLine("AnyChatSignServer has Error, message: 未找到文件" + PrivateRsaKeyFileName);

                    //未找到私钥文件
                    reqResult = JsonConvert.SerializeObject(new { errorcode = 217, timestamp = 0, sigStr = "" });
                    return reqResult;
                }
            }
            return reqResult;
        }

        static byte[] ReadLineAsBytes(Stream SourceStream)
        {
            var resultStream = new MemoryStream();
            while (true)
            {
                int data = SourceStream.ReadByte();
                resultStream.WriteByte((byte)data);
                if (data <= 10)
                    break;
            }
            resultStream.Position = 0;
            byte[] dataBytes = new byte[resultStream.Length];
            resultStream.Read(dataBytes, 0, dataBytes.Length);
            return dataBytes;
        }

        /// <summary>
        /// 输出方法
        /// </summary>
        /// <param name="response">response对象</param>
        /// <param name="responseString">输出值</param>
        /// <param name="contenttype">输出类型默认为json</param>
        static void Response(HttpListenerResponse response, string responsestring, string contenttype = "application/json")
        {
            response.StatusCode = 200;
            response.StatusDescription = "OK";
            response.ContentType = contenttype;
            response.ContentEncoding = Encoding.UTF8;

            //对于一个不带有credentials的请求,可以指定为'*',表示允许来自所有域的请求；在实际生产环境中需要进行修改或调整
            response.AddHeader("Access-Control-Allow-Origin", "*");
            
            byte[] buffer = System.Text.Encoding.UTF8.GetBytes(responsestring);
            //对客户端输出相应信息.
            response.ContentLength64 = buffer.Length;
            System.IO.Stream output = response.OutputStream;
            output.Write(buffer, 0, buffer.Length);
            //关闭输出流，释放相应资源
            output.Close();
        }

        /// <summary>
        /// 获取Ras签名
        /// </summary>
        /// <param name="userId">用户Id</param>
        /// <param name="appId">应用Id</param>
        /// <param name="privateKey">私钥</param>
        /// <returns></returns>
        static string getRsaSign(string userId, string appId, string privateKey)
        {
            string retVal = "";

            int userid = -1;
            int.TryParse(userId, out userid);

            //应用Id
            String appid = appId;
            StringBuilder sbPrivateKey = new StringBuilder();
            sbPrivateKey.Append(privateKey);

            StringBuilder sbAppId = new StringBuilder();
            sbAppId.Append(appid);

            int signStrSize = 1024;
            StringBuilder outSignStr = new StringBuilder(signStrSize);

            try
            {
                int timeStamp = 0;
                string signStr = string.Empty;

                int errorcode = AnyChatSign.AnyChatRsaSign(userid, sbAppId, sbPrivateKey, outSignStr, signStrSize, ref timeStamp);
                if (errorcode == 0)
                {
                    signStr = outSignStr.ToString();

                    Object dataObj = new { signStr = signStr, signTimestampe = timeStamp };
                }
                else
                {
                }

                retVal = JsonConvert.SerializeObject(new { errorcode = errorcode, timestamp = timeStamp, sigStr = signStr });

            }
            catch (Exception e)
            {
                System.Console.WriteLine("AnyChatSignServer has exception, message: " + e.StackTrace);
                retVal = JsonConvert.SerializeObject(new { errorcode = -99, timestamp = 0, sigStr = "" });
                return retVal;
            }
            
            return retVal;
        }
    }
}
