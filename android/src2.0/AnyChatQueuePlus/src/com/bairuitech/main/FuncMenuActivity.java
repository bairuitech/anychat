package com.bairuitech.main;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.*;
import android.widget.AdapterView.OnItemClickListener;
import com.bairuitech.anychat.*;
import com.bairuitech.common.ConfigEntity;
import com.bairuitech.common.ConfigService;
import com.bairuitech.common.CustomApplication;
import com.example.anychatqueueplusplus.R;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;


public class FuncMenuActivity extends Activity implements AnyChatBaseEvent,OnClickListener,AnyChatObjectEvent {

    public ConfigEntity configEntity;					//参数配置类
    private CustomApplication mApplication;				//全局类
    public ProgressDialog waitingpd;					//进度提示

    private ImageButton mImgBtnReturn;	         		  // 标题返回
    private TextView mTitleName;						  // 标题名字
    private GridView mMenuGridView;						  //网格布局
    // 功能菜单图标
    private int[] arrFuncIcons = { R.drawable.stronghold_01, R.drawable.stronghold_02,
            R.drawable.stronghold_03, R.drawable.stronghold_04};

    private AnyChatCoreSDK anychat;							 //sdk对象
    private List<Integer> mobject =new ArrayList<Integer>(); //装载营业厅ID
    private ArrayList<HashMap<String, Object>> mArrItem;	 //装载适配器数据

    /** id **/
    private int dwUserId;
    /** 类型 **/
    private int userTypeCode;
    /** 拼接的json字符串 */
    private String dwAttribute;
    /** 1服务端设置，0客户端设置 **/
    private int mUserSetting;
    /** 0:队列，1技能 */
    private int modeStrategy;
    /** 自动路由  1关闭，0开启**/
    private int isAutoMode;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //自定义标题栏
        requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
        setContentView(R.layout.activity_func_menu);
        getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.titlebar);
        SetData();
        //视频参数配置
        ApplyVideoConfig();
        //初始化sdk
        InitSDK();
        //设置对象属性身份
        settingClientUserInfo();
        //初始化布局
        InitLayout();
    }

    /**
     * 初始化从前个界面传进来的数据
     */
    private void SetData() {
        dwUserId = getIntent().getIntExtra("dwUserId", 0);
        userTypeCode = getIntent().getIntExtra("userTypeCode", 0);
        mUserSetting = getIntent().getIntExtra("userSetting", 0);
        modeStrategy = getIntent().getIntExtra("modeStrategy", 0);
        dwAttribute = getIntent().getStringExtra("queueTypeJson");
        isAutoMode = getIntent().getIntExtra("autoMode", 0);
    }

    private void InitSDK() {
        //初始化sdk
        if (anychat == null) {
            anychat = AnyChatCoreSDK.getInstance(this);
        }
        anychat.SetBaseEvent(this);//基本登陆事件接口
        anychat.SetObjectEvent(this);//排队事件接口；
    }

    public void settingClientUserInfo() {
        switch (userTypeCode) {
            case AnyChatObjectDefine.ANYCHAT_OBJECT_FLAGS_CLIENT:
                // 设置用户身份信息设置
                InitClientObjectInfo(0);
                break;
            case AnyChatObjectDefine.ANYCHAT_OBJECT_FLAGS_AGENT:
                if (mUserSetting == 0) {
                    int dwAgentFlags = AnyChatObjectDefine.ANYCHAT_OBJECT_FLAGS_AGENT; // 坐席标识
                    if (isAutoMode == 0) {
                        dwAgentFlags = AnyChatObjectDefine.ANYCHAT_OBJECT_FLAGS_AGENT + AnyChatObjectDefine.ANYCHAT_OBJECT_FLAGS_AUTOMODE; // 坐席标识
                    }

                    // 设置坐席身份信息设置
                    // 业务对象身份初始化；0代表普通客户，2是代表座席 (USER_TYPE_ID)
                    AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_OBJECT_INITFLAGS, dwAgentFlags);
                    AnyChatCoreSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_CLIENTUSER, dwUserId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_STRINGTAG, dwAttribute);
                   //支持所有技能组
                    AnyChatCoreSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_CLIENTUSER, dwUserId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_ATTRIBUTE, -1);
                    // 向服务器发送数据同步请求指令
                    AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, AnyChatObjectDefine.ANYCHAT_INVALID_OBJECT_ID, AnyChatObjectDefine.ANYCHAT_OBJECT_CTRL_SYNCDATA, dwUserId, 0, 0, 0, "");
                }
                // 选择“服务器端设置”时，先从后台确认用户身份
                if (mUserSetting == 1) {
                    // 设置用户身份信息设置
                    InitClientObjectInfo(2);
                }
        }
    }

    //初始化服务对象事件；触发回调OnAnyChatObjectEvent函数
    private void InitClientObjectInfo(int mUserSettingMode) {
        if (mUserSettingMode == 2) {
            //业务对象身份初始化；0代表普通客户，2是代表座席 (USER_TYPE_ID)
            AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_OBJECT_INITFLAGS, AnyChatObjectDefine.ANYCHAT_OBJECT_FLAGS_AGENT);
        } else {
            //业务对象身份初始化；0代表普通客户，2是代表座席 (USER_TYPE_ID)
            AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_OBJECT_INITFLAGS, AnyChatObjectDefine.ANYCHAT_OBJECT_FLAGS_CLIENT);
        }

        //业务对象优先级设定；
        int dwPriority = 10;
        AnyChatCoreSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_CLIENTUSER,dwUserId,AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_PRIORITY, dwPriority);
        //业务对象属性设定，关联技能分组，-1表示具备所有业务技能
        int dwAttribute = -1;
        AnyChatCoreSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_CLIENTUSER, dwUserId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_ATTRIBUTE, dwAttribute);

        // 选择“服务器端设置”时，先从后台确认用户身份
        if (mUserSettingMode != 2) {
            // 向服务器发送数据同步请求指令
            AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, AnyChatObjectDefine.ANYCHAT_INVALID_OBJECT_ID, AnyChatObjectDefine.ANYCHAT_OBJECT_CTRL_SYNCDATA, dwUserId, 0, 0, 0, "");
        }
    }

    private void InitLayout() {

        mApplication = (CustomApplication) getApplication();
        waitingpd = new ProgressDialog(FuncMenuActivity.this);
        this.setTitle("营业厅列表");
        mMenuGridView = (GridView) this.findViewById(R.id.funcmenuGridView);
        mTitleName = (TextView) this.findViewById(R.id.titleName);
        mTitleName.setText(R.string.str_funcTitle);
        mImgBtnReturn = (ImageButton) this.findViewById(R.id.returnImgBtn);
        mImgBtnReturn.setOnClickListener(this);

        showIndeterminate1();
    }
    // 根据配置文件配置视频参数
    private void ApplyVideoConfig() {
        ConfigEntity configEntity = ConfigService.LoadConfig(this);
        if (configEntity.configMode == 1) // 自定义视频参数配置
        {
            // 设置本地视频编码的码率（如果码率为0，则表示使用质量优先模式）
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_BITRATECTRL,
                    configEntity.videoBitrate);
            if (configEntity.videoBitrate == 0) {
                // 设置本地视频编码的质量
                AnyChatCoreSDK.SetSDKOptionInt(
                        AnyChatDefine.BRAC_SO_LOCALVIDEO_QUALITYCTRL,
                        configEntity.videoQuality);
            }
            // 设置本地视频编码的帧率
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_FPSCTRL,
                    configEntity.videoFps);
            // 设置本地视频编码的关键帧间隔
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_GOPCTRL,
                    configEntity.videoFps);
            // 设置本地视频采集分辨率
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL,
                    configEntity.resolution_width);
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL,
                    configEntity.resolution_height);
            // 设置视频编码预设参数（值越大，编码质量越高，占用CPU资源也会越高）
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_PRESETCTRL,
                    configEntity.videoPreset);
        }
        // 让视频参数生效
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_LOCALVIDEO_APPLYPARAM,
                configEntity.configMode);
        // P2P设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_NETWORK_P2PPOLITIC,
                configEntity.enableP2P);
        // 本地视频Overlay模式设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_LOCALVIDEO_OVERLAY,
                configEntity.videoOverlay);
        // 回音消除设置
        AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_ECHOCTRL,
                configEntity.enableAEC);
        // 平台硬件编码设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_CORESDK_USEHWCODEC,
                configEntity.useHWCodec);
        // 视频旋转模式设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_LOCALVIDEO_ROTATECTRL,
                configEntity.videorotatemode);
        // 本地视频采集偏色修正设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA,
                configEntity.fixcolordeviation);
        // 视频GPU渲染设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_VIDEOSHOW_GPUDIRECTRENDER,
                configEntity.videoShowGPURender);
        // 本地视频自动旋转设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION,
                configEntity.videoAutoRotation);
    }

    private void destroyCurActivity() {
        this.setResult(RESULT_OK);
        anychat.Logout();
        onPause();
        onDestroy();
        finish();
    }
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

        if(keyCode == KeyEvent.KEYCODE_BACK){
            anychat.Logout();
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if(anychat != null)
        	anychat.removeEvent(this);
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        anychat.SetBaseEvent(this);
        anychat.SetObjectEvent(this);
    }

    @Override
    public void OnAnyChatConnectMessage(boolean bSuccess) {
        // TODO Auto-generated method stub

    }

    @Override
    public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
        // TODO Auto-generated method stub
    }
    @Override
    public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
        // TODO Auto-generated method stub

    }

    @Override
    public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
        // TODO Auto-generated method stub

    }

    @Override
    public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
        // TODO Auto-generated method stub

    }

    // 网络断开
    @Override
    public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
        // 销毁当前界面
        destroyCurActivity();
        Intent mIntent = new Intent("NetworkDiscon");
        // 发送广播
        sendBroadcast(mIntent);
    }

    @Override
    public void onClick(View v) {
        // TODO Auto-generated method stub
        switch (v.getId()) {
            case R.id.returnImgBtn://按下返回键
                anychat.Logout();
                destroyCurActivity();
                break;

            default:
                break;
        }
    }

    @Override
    public void OnAnyChatObjectEvent(int dwObjectType, int dwObjectId,
                                     int dwEventType, int dwParam1, int dwParam2, int dwParam3,
                                     int dwParam4, String strParam) {
        // TODO Auto-generated method stub
        switch(dwEventType) {

            //营业厅数据同步，回调一次返回一个营业厅对象id（有多少营业厅回调多少次）
            case AnyChatObjectDefine.ANYCHAT_OBJECT_EVENT_UPDATE:
                //装入集合
                mobject.add(dwObjectId);

                break;

            //进入营业厅结果回调
            case AnyChatObjectDefine.ANYCHAT_AREA_EVENT_ENTERRESULT:

                AnyChatEnterAreaResult(dwObjectType, dwObjectId, dwParam1);
                break;
            //数据同步完成回调
            case AnyChatObjectDefine.ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH:

                DataFinshed(dwObjectType);
                break;
        }
    }


    //进入营业厅的回调，跳转到业务列表
    private void AnyChatEnterAreaResult(int dwObjectType, int dwObjectId,
                                        int dwParam1) {
        //dwParam1 进入营业厅返回结果，0表示进入营业厅成功

        //客户角色
        if(mApplication.getUserType() == 0){

            Intent in=new Intent();
            in.setClass(FuncMenuActivity.this, YeWuActivity.class);
            startActivity(in);
            waitingpd.dismiss();
            //座席角色
        }else if(mApplication.getUserType() == 2){

            Intent in=new Intent();
            in.setClass(FuncMenuActivity.this,AgentServiceActivity.class);
            in.putExtra("isAutoMode",isAutoMode);
            in.putExtra("userSetting", mUserSetting);// 1服务端设置，0客户端设置
            startActivity(in);
            waitingpd.dismiss();
        }


    }
    public void showIndeterminate1(){
        waitingpd.setMessage("加载营业厅...");
        waitingpd.setCancelable(true);
        waitingpd.setProgress(ProgressDialog.STYLE_HORIZONTAL);
        waitingpd.setIndeterminate(true);
        waitingpd.show();
    }
    public void showIndeterminate2(){
        waitingpd.setMessage("进入营业厅...");
        waitingpd.setCancelable(true);
        waitingpd.setProgress(ProgressDialog.STYLE_HORIZONTAL);
        waitingpd.setIndeterminate(true);
        waitingpd.show();
    }

    private void DataFinshed(int dwObjectType) {
        // TODO Auto-generated method stub

        waitingpd.dismiss();
        if(dwObjectType == AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA)
        {
            //适配器的数据获取
            mArrItem = new ArrayList<HashMap<String, Object>>();
            for (int index = 0; index < mobject.size(); index++) {

                String name = AnyChatCoreSDK.ObjectGetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA,mobject.get(index), AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME);

                HashMap<String, Object> itemMap = new HashMap<String, Object>();
                itemMap.put("ItemImage", arrFuncIcons[index%4]);
                itemMap.put("ItemText",name);
                mArrItem.add(itemMap);
            }
            SimpleAdapter sMenuItemAdapter = new SimpleAdapter(this, mArrItem,
                    R.layout.funcmenu_cell,
                    new String[] { "ItemImage", "ItemText" }, new int[] {
                    R.id.funcItemImage, R.id.funcItemText });

            mMenuGridView.setAdapter(sMenuItemAdapter);
            //设置监听事件
            mMenuGridView.setOnItemClickListener(new OnItemClickListener() {
                public void onItemClick(AdapterView<?> arg0, View arg1,
                                        int arg2, long arg3) {
                    // TODO Auto-generated method stub

                    showIndeterminate2();
                    mApplication.setCurrentAreaId(mobject.get(arg2));
                    //控制指令
                    AnyChatCoreSDK.ObjectControl(
                            AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, mobject.get(arg2),
                            AnyChatObjectDefine.ANYCHAT_AREA_CTRL_USERENTER, 0, 0, 0,
                            0, "");
                }
            });
        }

    }
}