unit GVSDK;
(****************************************************************************
               GVSDK.h
****************************************************************************)

interface
uses
  SysUtils,Messages,Classes,Types,Graphics,GVMessageDefine,GVErrorCodeDefine;


(**
 *	客户端状态类别定义
 *)
type GV_STATE_TYPE_DEFINE=
    (
    	GV_STATE_TYPE_ACTIVE = 0,			///< 客户端活动类型状态
    	GV_STATE_TYPE_CAMERA,				///< 客户端摄像机状态
    	GV_STATE_TYPE_AUDIO,				///< 客户端音频设备状态
    	GV_STATE_TYPE_CHATMODE				///< 客户端聊天模式
    );
type GV_STATE_TYPE=GV_STATE_TYPE_DEFINE;

const
  //会议模式定义
  GV_MEETING_MODE_FREE	=0;					///< 自由模式，发言没有限制，自由发言，抢Mic
  GV_MEETING_MODE_CHAIR	=1;					///< 主持模式，发言受限制，只有主持人给Mic才能发言
  GV_MEETING_MODE_ORDER	=2;					///< 轮巡模式，发言受限制，只有轮到自己才能发言


//活动状态定义
  GV_ACTIVE_STATE_NORMAL	=0;				///< 正常
  GV_ACTIVE_STATE_BUSY		=1;				///< 繁忙
  GV_ACTIVE_STATE_AWAY		=2;				///< 离开

//摄像头状态定义
  GV_CAMERA_STATE_NULL		=0;				///< 没有摄像头
  GV_CAMERA_STATE_NORMAL	=1;				///< 有摄像头但没有打开
  GV_CAMERA_STATE_OPEN		=2;				///< 摄像头已打开

// Mic活动状态定义
  GV_AUDIO_STATE_NULL		=0;				///< 没有安装声卡
  GV_AUDIO_STATE_NORMAL		=1;				///< 有声卡，但没有打开Mic
  GV_AUDIO_STATE_OPEN		=2;				///< Mic已打开

// 客户端聊天模式定义
  GV_CHATMODE_PUBLIC		=0;				///< 公聊模式
  GV_CHATMODE_PRIVATE		=1;				///< 私聊模式，接收不到其它用户的语音和视频数据，仅能接收到自己私聊对象的语音和视频数据，文字消息不受模式影响




implementation

end.
