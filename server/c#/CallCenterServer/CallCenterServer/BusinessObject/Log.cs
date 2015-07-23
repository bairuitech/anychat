using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace BusinessObject
{
    /// <summary>
    /// 日志核心类
    /// </summary>
    public class Log
    {
        public static string logPath = Application.StartupPath +"\\AnyChatDemoLog.log";

        /// <summary>
        /// 生成log
        /// </summary>
        /// <param name="log"></param>
        public static void SetLog(string log)
        {
            try
            {
                File.AppendAllText(logPath, "[" + DateTime.Now.ToString() + "]" + log + "\r\n");
            }
            catch (Exception)
            {
            }
        }
    }
}
