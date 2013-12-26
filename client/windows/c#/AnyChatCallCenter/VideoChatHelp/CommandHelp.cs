using System;
using System.Collections.Generic;
using System.Text;

namespace VideoChatHelp
{
    public class CommandHelp
    {
        #region 指令生成、解析、发送和接收


        /// <summary>
        /// 生成指令
        /// </summary>
        /// <param name="cmd">指令代码</param>
        /// <param name="paramsObject">附加数据列表</param>
        /// <returns></returns>
        public static string GenerateCommand(int cmd, params ParamInfo[] paramsObject)
        {
            string str = "";
            try
            {
                foreach (ParamInfo p in paramsObject)
                {
                    str += "<" + p.Name + ">" + p.Value + "</" + p.Name + ">";
                }
                str = "<CMD>" + cmd + "</CMD>" + str;
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatHelp.CommandHelp.GenerateCommand       GenerateCommand：" + ex.Message.ToString());
            }
            return str;
        }

        /// <summary>
        /// 生成标记指令
        /// </summary>
        /// <param name="strMark"></param>
        /// <param name="paramsObject"></param>
        /// <returns></returns>
        public static string GenerateMarkCommand(params ParamInfo[] paramsObject)
        {
            string str = "";
            try
            {
                foreach (ParamInfo p in paramsObject)
                {
                    str += "<" + p.Name + ">" + p.Value + "</" + p.Name + ">";
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatHelp.CommandHelp.GenerateMarkCommand       GenerateMarkCommand：" + ex.Message.ToString());
            }
            return str;
        }

        /// <summary>
        /// 解析指令代码
        /// </summary>
        /// <param name="cmdString">需解析字符串</param>
        /// <returns>指令代码</returns>
        public static string ResolveCommand(string cmdString)
        {
            return GetStringContent(cmdString, "<CMD>", "</CMD>");
        }

        /// <summary>
        /// 解析指令内容
        /// </summary>
        /// <param name="cmd">指令代码</param>
        /// <param name="cmdString">需解析字符串</param>
        /// <returns>参数集</returns>
        public static List<ParamInfo> ResolveCommand(int cmd, string cmdString)
        {
            List<ParamInfo> list = new List<ParamInfo>();
            try
            {
                //遍历枚举类
                foreach (ParamEnum st in (ParamEnum[])System.Enum.GetValues(typeof(ParamEnum)))
                {
                    string str = GetStringContent(cmdString, "<" + st.ToString() + ">", "</" + st.ToString() + ">");
                    if (str != null)
                    {
                        ParamInfo p = new ParamInfo(st.ToString(), str);
                        list.Add(p);
                    }
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatHelp.CommandHelp.ResolveCommand       ResolveCommand：" + ex.Message.ToString());
            }
            return list;
        }


        /// <summary>
        /// 从参数集中获取指定的参数对象
        /// </summary>
        /// <param name="list">参数集</param>
        /// <param name="ParamName">参数名</param>
        /// <returns></returns>
        public static ParamInfo GetParamInfoByParams(List<ParamInfo> list, string ParamName)
        {
            ParamInfo param = new ParamInfo(ParamName,"0");
            try
            {
                foreach (ParamInfo p in list)
                {
                    if (p.Name == ParamName)
                    {
                        param = p;
                        break;
                    }
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatHelp.CommandHelp.GetParamInfoByParams       GetParamInfoByParams：" + ex.Message.ToString());
            }
            return param;
        }

        /// <summary>    
        /// 获取字符串中指定字符间的字符串    
        /// </summary>    
        /// <param name="str">要截取的字符串</param>    
        /// <param name="start">开始字符串</param>    
        /// <param name="last">结束字符串</param>    
        /// <returns></returns>    
        private static string GetStringContent(string str, string start, string last)
        {
            try
            {
                int indexof = -1;
                indexof = str.IndexOf(start);
                if (indexof != -1)
                {
                    str = str.Substring(str.IndexOf(start) + start.Length, str.Length - str.IndexOf(start) - start.Length);
                    str = str.Substring(0, str.LastIndexOf(last));
                    return str;
                }
                else
                {
                    return null;
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatHelp.CommandHelp.GetStringContent       GetStringContent：" + ex.Message.ToString());
                return null;
            }
        }

        #endregion

        #region 约定关键字

        /// <summary>
        /// 约定参数
        /// </summary>
        public enum ParamEnum
        {
            /// <summary>
            /// 请求数据类型
            /// </summary>
            DATATYPE,
            /// <summary>
            /// 数据
            /// </summary>
            DATA,
            /// <summary>
            /// 数据：用户ID
            /// </summary>
            DATA_USERID,
            /// <summary>
            /// 数据：用户外网IP
            /// </summary>
            DATA_USERIP,
            /// <summary>
            /// 数据：用户名
            /// </summary>
            DATA_USERNAME,
            /// <summary>
            /// Object对象ID
            /// </summary>
            OBJECTID,
            /// <summary>
            /// 状态
            /// </summary>
            STATUS,
            /// <summary>
            /// 附加参数wparam
            /// </summary>
            WPARAM,
            /// <summary>
            /// 源用户ID
            /// </summary>
            SUSERID,
            /// <summary>
            /// 目标用户ID
            /// </summary>
            TUSERID,
            /// <summary>
            /// 控制数据类型
            /// </summary>
            CTRLCODE,
            /// <summary>
            /// 错误代码
            /// </summary>
            RETCODE,
            /// <summary>
            /// 房间ID
            /// </summary>
            ROOMID
        }

        #endregion

        #region 网络断开错误

        /// <summary>
        /// 获取网络错误内容
        /// </summary>
        /// <param name="error"></param>
        /// <returns></returns>
        public static string GetLinkCloseErrorString(int error)
        {
            try
            {
                foreach (ErrorInfo e in linkCloseError)
                {
                    if (e.Error == error)
                    {
                        return e.Errorstring;
                    }
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatHelp.CommandHelp.GetLinkCloseErrorString       GetLinkCloseErrorString：" + ex.Message.ToString());
            }
            return "操作失败";
        }

        /// <summary>
        /// 网络连接断开
        /// </summary>
        public static ErrorInfo[] linkCloseError = new ErrorInfo[] { 
            new ErrorInfo(0,"正常断开，如网络中断，服务器被关闭等"),
            new ErrorInfo(1,"该用户在其它计算机上登录，之前的连接被服务器断开"),
            new ErrorInfo(2,"服务器功能受限制（演示模式下不允许长时间连接服务器）"),
            new ErrorInfo(3,"接收到来自其它网络的连接，连接被主动关闭"),
            new ErrorInfo(4,"客户端程序版本太旧，不允许连接"),
            new ErrorInfo(5,"连接服务器认证失败（服务器设置了认证密码），"),
            new ErrorInfo(6,"网络连接超时，服务器主动断开"),
            new ErrorInfo(7,"服务器不支持嵌入式设备连接，或连接设备超过授权设备数")
        };

        /// <summary>
        /// 错误对象error
        /// </summary>
        public class ErrorInfo
        {

            public ErrorInfo()
            {
            }

            public ErrorInfo(int error, string errorstring)
            {
                Error = error;
                Errorstring = errorstring;
            }
            private int error;
            /// <summary>
            /// 错误代码
            /// </summary>
            public int Error
            {
                get { return error; }
                set { error = value; }
            }
            private string errorstring;
            /// <summary>
            /// 错误描述
            /// </summary>
            public string Errorstring
            {
                get { return errorstring; }
                set { errorstring = value; }
            }
        }

        #endregion
    }
}
