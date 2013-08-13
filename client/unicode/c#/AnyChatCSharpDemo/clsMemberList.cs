using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace AnyChatCSharpDemo
{
    public class clsMemberList
    {
        /// <summary>
        /// 在线用户属性结构
        /// </summary>
        public struct MemberItem
        {
            /// <summary>
            /// 用户账号
            /// </summary>
            public string m_UserName;
            /// <summary>
            /// 用户ＩＤ，开发包自动分配
            /// </summary>
            public int m_UserID;
            /// <summary>
            /// 真实姓名
            /// </summary>
            public string m_RealName;
            /// <summary>
            /// 用户列表中的顺序
            /// </summary>
            public int m_Index;
            /// <summary>
            /// 用户权限,0主持人权限，1音频，2视频,3隐身
            /// </summary>
            public int[] m_Permission;
        }
    }
}
