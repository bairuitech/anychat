using System;
using System.Collections.Generic;
using System.Text;

namespace QueueHelp
{
    /// <summary>
    /// 登录信息类
    /// </summary>
    public class LoginInfo
    {
        public int userID { get; set; }
        public string userName { get; set; }
        public UserIdentityType userIdType { get; set; }
        public int userPriority { get; set; }
        public bool isRouterMode { get; set; }
        public int userSkills { get; set; }
    }
}
