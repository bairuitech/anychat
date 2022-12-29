
#include "CmacOSWindowListInfo.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
 
static void WindowListApplierFunction(const void *inputDictionary, void *context);
static NSString* convertDictToJson(NSDictionary * dict);
static NSArray* getWindowListCopyWindowInfo(CGWindowListOption listOptions);
static void showScreenRecordingPrompt();
 
CmacOSWindowListInfo::CmacOSWindowListInfo()
{
    showScreenRecordingPrompt();
}

CmacOSWindowListInfo::~CmacOSWindowListInfo()
{
    
}

 
std::string CmacOSWindowListInfo::getOnScreenWindowInfoList()
{
    NSArray* winInfoList = getWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly);
    
    if (winInfoList.count < 1)
        return "";
    
    NSMutableDictionary* data_dict = [NSMutableDictionary dictionary];
    [data_dict setObject:winInfoList forKey:@"hwndinfo"];
    [data_dict setObject:@(0) forKey:@"errorcode"];
    
    NSString *json = convertDictToJson(data_dict);
 
    std::string result = json.length < 1 ? "" : json.UTF8String;
    return result;
}

std::string CmacOSWindowListInfo::getOffScreenWindowInfoList()
{
    NSArray* winInfoList = getWindowListCopyWindowInfo(kCGWindowListExcludeDesktopElements);
    
    if (winInfoList.count < 1)
        return "";
    
    NSMutableDictionary* data_dict = [NSMutableDictionary dictionary];
    [data_dict setObject:winInfoList forKey:@"hwndinfo"];
    [data_dict setObject:@(0) forKey:@"errorcode"];
    
    NSString *json = convertDictToJson(data_dict);
 
    std::string result = json.length < 1 ? "" : json.UTF8String;
    return result;
}


std::string CmacOSWindowListInfo::getAllScreenWindowInfoList()
{
    NSArray* winInfoList = getWindowListCopyWindowInfo(kCGWindowListOptionAll);
    
    if (winInfoList.count < 1)
        return "";
    
    NSMutableDictionary* data_dict = [NSMutableDictionary dictionary];
    [data_dict setObject:winInfoList forKey:@"hwndinfo"];
    [data_dict setObject:@(0) forKey:@"errorcode"];
    
    NSString *json = convertDictToJson(data_dict);
 
    std::string result = json.length < 1 ? "" : json.UTF8String;
    return result;
}



static NSArray* getWindowListCopyWindowInfo(CGWindowListOption listOptions)
{
    // Ask the window server for the list of windows.
    CFArrayRef windowList = CGWindowListCopyWindowInfo(listOptions, kCGNullWindowID);
 
    // Copy the returned list, further pruned, to another list. This also adds some bookkeeping
    // information to the list as well as
    NSMutableArray * prunedWindowList = [NSMutableArray array];

    CFArrayApplyFunction(windowList,
                         CFRangeMake(0, CFArrayGetCount(windowList)),
                         &WindowListApplierFunction,
                         (__bridge void *)(prunedWindowList));
    
    CFRelease(windowList);
    
    // return the new window list
    return prunedWindowList;
}


static NSString* convertDictToJson(NSDictionary * dict)
{
    if (dict == nil)
        return @"";
 
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dict
                                        options:NSJSONWritingSortedKeys
                                        error:&error];
    NSString *jsonString = @"";
    if (jsonData != nil)
    {
        jsonString = [[NSString alloc]initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    
    return jsonString;
}

static NSString *kWindowIDKey = @"hwnd";  // Window ID
static NSString *kAppNameKey  = @"name";  // Application Name
static NSString *kWindowOrderKey = @"id"; // The overall front-to-back ordering of the windows as returned by the window server
 
 
static void WindowListApplierFunction(const void *inputDictionary, void *context)
{
    NSDictionary *entry = (__bridge NSDictionary*)inputDictionary;
    NSMutableArray *outputArray = (__bridge NSMutableArray*)context;
    
    // The flags that we pass to CGWindowListCopyWindowInfo will automatically filter out most undesirable windows.
    // However, it is possible that we will get back a window that we cannot read from, so we'll filter those out manually.
    int sharingState = [entry[(id)kCGWindowSharingState] intValue];
    
    if(sharingState != kCGWindowSharingNone)
    {
        NSMutableDictionary *outputEntry = [NSMutableDictionary dictionary];
        
        // Grab the application name, but since it's optional we need to check before we can use it.
        NSString *applicationName = entry[(id)kCGWindowOwnerName];
        if(applicationName != nil)
        {
            // PID is required so we assume it's present.
            NSString *name = [NSString stringWithFormat:@"%@", applicationName];
            outputEntry[kAppNameKey] = name;
        }
        else
        {
            // The application name was not provided, so we use a fake application name to designate this.
            // PID is required so we assume it's present.
            NSString *nameAndPID = [NSString stringWithFormat:@"((unknown)) (%@)", entry[(id)kCGWindowOwnerPID]];
            outputEntry[kAppNameKey] = nameAndPID;
        }
  
        // Grab the Window ID & Window Level. Both are required, so just copy from one to the other
        NSString* windowId = [NSString stringWithFormat:@"%@", entry[(id)kCGWindowNumber]];
        outputEntry[kWindowIDKey] = @(windowId.integerValue); 
    
        // Finally, we are passed the windows in order from front to back by the window server
        // Should the user sort the window list we want to retain that order so that screen shots
        // look correct no matter what selection they make, or what order the items are in. We do this
        // by maintaining a window order key that we'll apply later.
        outputEntry[kWindowOrderKey] = @(outputArray.count);
       
        
        [outputArray addObject:outputEntry];
    }
}

//显示权限
static void showScreenRecordingPrompt()
{
    /* macos 10.14 and lower do not require screen recording permission to get window titles */
    if(@available(macos 10.15, *)) {
        /*
         To minimize the intrusion just make a 1px image of the upper left corner
         This way there is no real possibilty to access any private data
         */
        CGImageRef screenshot = CGWindowListCreateImage(
                                               CGRectMake(0, 0, 1, 1),
                                               kCGWindowListOptionOnScreenOnly,
                                               kCGNullWindowID,
                                               kCGWindowImageDefault);
        
        if (screenshot) {
            CFRelease(screenshot);
        }
    }
}
