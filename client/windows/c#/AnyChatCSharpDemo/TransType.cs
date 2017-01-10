using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AnyChatCSharpDemo
{
    /// <summary>
    /// 传输方式
    /// </summary>
    public enum TransType
    {
        /// <summary>
        /// 文本传输
        /// </summary>
        TextMessage = 0,
        /// <summary>
        /// 透明通道
        /// </summary>
        TransBuffer = 1,
        /// <summary>
        /// 透明通道扩展
        /// </summary>
        TransBufferEx = 2
    }
}
