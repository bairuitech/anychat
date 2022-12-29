#ifndef ANYCHAT_MACOS_WINDOWLISTINFO_H__INCLUDED_
#define ANYCHAT_MACOS_WINDOWLISTINFO_H__INCLUDED_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>

/**
 *  macOS窗口信息获取
 */
 
class CmacOSWindowListInfo
{
public:
    CmacOSWindowListInfo();
    virtual ~CmacOSWindowListInfo();
 
public:
    //得到显示窗口列表信息
    std::string getOnScreenWindowInfoList();
    
    //得到隐藏窗口列表信息
    std::string getOffScreenWindowInfoList();
    
    //得到所有窗口列表信息:显示+隐藏
    std::string getAllScreenWindowInfoList();
};



#endif
