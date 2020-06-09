package com.example.helloanychat;

import android.app.AlertDialog;
import android.content.*;
import android.content.res.Resources;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.view.ContextThemeWrapper;
import android.view.KeyEvent;
import android.view.inputmethod.InputMethodManager;
import android.widget.Toast;
import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.example.config.ConfigEntity;
import com.example.config.ConfigService;


public class MainActivity extends FragmentActivity implements AnyChatBaseEvent {
    private AnyChatCoreSDK anyChatSDK;
    private final int LOCALVIDEOAUTOROTATION = 1; // 本地视频自动旋转控制
    // 视频配置界面标识
    public static final int ACTIVITY_ID_VIDEOCONFIG = 1;
    private LoginFragment loginFragment;
    private RoleListFragment roleListFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initSDK();
        initFragment();
        ApplyVideoConfig();
        // 注册广播
        registerBroadcastReceiver();
    }

    private void initSDK() {
        if (anyChatSDK == null) {
            anyChatSDK = AnyChatCoreSDK.getInstance(this);
            anyChatSDK.SetBaseEvent(this);
            anyChatSDK.InitSDK(android.os.Build.VERSION.SDK_INT, 0);
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION,
                    LOCALVIDEOAUTOROTATION);
        }
    }
    public AnyChatCoreSDK getAnyChatSDK(){
        initSDK();
        return anyChatSDK;
    }
    private void initFragment() {
        loginFragment = new LoginFragment();
        roleListFragment = new RoleListFragment();
        replaceFragment(loginFragment);
    }

    @Override
    protected void onResume() {
        super.onResume();
//        hideKeyboard();
    }

    public void backFragment() {
        releaseAnyChatSDK();
        replaceFragment(loginFragment);
    }

    public void replaceFragment(Fragment fragment) {
        FragmentManager manager = getSupportFragmentManager();
        FragmentTransaction transaction = manager.beginTransaction();
        transaction.replace(R.id.fragmentContent, fragment);
        transaction.commitAllowingStateLoss();
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // TODO Auto-generated method stub
        if (resultCode == RESULT_OK && requestCode == ACTIVITY_ID_VIDEOCONFIG) {
            ApplyVideoConfig();
        }
    }

    // 根据配置文件配置视频参数
    private void ApplyVideoConfig() {
        ConfigEntity configEntity = ConfigService.LoadConfig(this);
        if (configEntity.mConfigMode == 1) // 自定义视频参数配置
        {
            // 设置本地视频编码的码率（如果码率为0，则表示使用质量优先模式）
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_BITRATECTRL,
                    configEntity.mVideoBitrate);
//			if (configEntity.mVideoBitrate == 0) {
            // 设置本地视频编码的质量
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_QUALITYCTRL,
                    configEntity.mVideoQuality);
//			}
            // 设置本地视频编码的帧率
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_FPSCTRL,
                    configEntity.mVideoFps);
            // 设置本地视频编码的关键帧间隔
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_GOPCTRL,
                    configEntity.mVideoFps * 4);
            // 设置本地视频采集分辨率
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL,
                    configEntity.mResolutionWidth);
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL,
                    configEntity.mResolutionHeight);
            // 设置视频编码预设参数（值越大，编码质量越高，占用CPU资源也会越高）
            AnyChatCoreSDK.SetSDKOptionInt(
                    AnyChatDefine.BRAC_SO_LOCALVIDEO_PRESETCTRL,
                    configEntity.mVideoPreset);
        }
        // 让视频参数生效
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_LOCALVIDEO_APPLYPARAM,
                configEntity.mConfigMode);
        // P2P设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_NETWORK_P2PPOLITIC,
                configEntity.mEnableP2P);
        // 本地视频Overlay模式设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_LOCALVIDEO_OVERLAY,
                configEntity.mVideoOverlay);
        // 回音消除设置
        AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_ECHOCTRL,
                configEntity.mEnableAEC);
        // 平台硬件编码设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_CORESDK_USEHWCODEC,
                configEntity.mUseHWCodec);
        // 视频旋转模式设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_LOCALVIDEO_ROTATECTRL,
                configEntity.mVideoRotateMode);
        // 本地视频采集偏色修正设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA,
                configEntity.mFixColorDeviation);
        // 视频GPU渲染设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_VIDEOSHOW_GPUDIRECTRENDER,
                configEntity.mVideoShowGPURender);
        // 本地视频自动旋转设置
        AnyChatCoreSDK.SetSDKOptionInt(
                AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION,
                configEntity.mVideoAutoRotation);
    }

    private void hideKeyboard() {
        InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        if (imm.isActive()) {
            if(getCurrentFocus().getApplicationWindowToken()!=null) {
                imm.hideSoftInputFromWindow(getCurrentFocus()
                                .getApplicationWindowToken(),
                        InputMethodManager.HIDE_NOT_ALWAYS);
            }
        }
    }

    // 广播
    private BroadcastReceiver mBroadcastReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (action.equals("VideoActivity")) {
                Toast.makeText(MainActivity.this, "网络已断开！", Toast.LENGTH_SHORT)
                        .show();
                int dwErrorCode= intent.getExtras().getInt("dwErrorCode");
                releaseAnyChatSDK();
                loginFragment.setBtnVisible(LoginFragment.SHOWLOGINSTATEFLAG);
                loginFragment.setConnectMsg("连接关闭，errorCode：" + dwErrorCode);
                replaceFragment(loginFragment);
            }
        }
    };

    public void registerBroadcastReceiver() {
        IntentFilter myIntentFilter = new IntentFilter();
        myIntentFilter.addAction("VideoActivity");
        // 注册广播
        registerReceiver(mBroadcastReceiver, myIntentFilter);
    }

    public void unRegisterBroadcastReceiver() {
        // 注册广播
        unregisterReceiver(mBroadcastReceiver);
    }

    @Override
    public void OnAnyChatConnectMessage(boolean bSuccess) {
        if (!bSuccess) {
            loginFragment.setBtnVisible(LoginFragment.SHOWLOGINSTATEFLAG);
            loginFragment.setConnectMsg("连接服务器失败，自动重连，请稍后...");
            System.out.println("connect failed");
        }
    }

    @Override
    public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
        if (dwErrorCode == 0) {
            loginFragment.saveLoginData();
//            hideKeyboard();
            loginFragment.setConnectMsg("Connect to the server success.");
            int roomId = Integer.valueOf(loginFragment.getRoomId());
            anyChatSDK.EnterRoom(roomId, "");
            roleListFragment.setMySelfUserId(dwUserId);
        } else {
            loginFragment.setBtnVisible(LoginFragment.SHOWLOGINSTATEFLAG);
            loginFragment.setConnectMsg("登录失败，errorCode：" + dwErrorCode);
        }
    }

    @Override
    public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
        System.out.println("OnAnyChatEnterRoomMessage" + dwRoomId + "err:"
                + dwErrorCode);
        if (dwErrorCode == 0) {
            roleListFragment.setRoomId(dwRoomId);
            replaceFragment(roleListFragment);
        }else {
            releaseAnyChatSDK();
            loginFragment.setBtnVisible(LoginFragment.SHOWLOGINSTATEFLAG);
            loginFragment.setConnectMsg("进入房间失败，errorCode：" + dwErrorCode);
        }
    }

    @Override
    public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
        if (roleListFragment != null) {
            roleListFragment.updateUserList();
        }
    }

    @Override
    public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
        if (roleListFragment != null) {
            if (bEnter) {
                roleListFragment.addRole(dwUserId);
            } else {
                roleListFragment.removeRole(dwUserId);
            }
        }
    }

    @Override
    public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
        Fragment fragment=getSupportFragmentManager().findFragmentById(R.id.fragmentContent);
        if (fragment instanceof LoginFragment){
            releaseAnyChatSDK();
            loginFragment.setBtnVisible(LoginFragment.SHOWLOGINSTATEFLAG);
            loginFragment.setConnectMsg("连接关闭，errorCode：" + dwErrorCode);
        }else if(fragment instanceof  RoleListFragment){
            loginFragment.setBtnVisible(LoginFragment.SHOWLOGINSTATEFLAG);
            loginFragment.setConnectMsg("连接关闭，errorCode：" + dwErrorCode);
            backFragment();
        }

    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (event.getKeyCode() == KeyEvent.KEYCODE_BACK) {
            backOrFinish();
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }
    public void exitDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage("是否退出房间?")
                .setCancelable(false)
                .setPositiveButton("是",
                        new DialogInterface.OnClickListener() {

                            @Override
                            public void onClick(DialogInterface dialog,
                                                int which) {
                                loginFragment.setBtnVisible(LoginFragment.SHOWLOGINSTATEFLAG);
                                loginFragment.setConnectMsg("Not connect to the server");
                                backFragment();
                                dialog.cancel();
                            }
                        })
                .setNegativeButton("否", new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.cancel();
                    }
                }).show();
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        if(anyChatSDK!=null) {
            anyChatSDK.SetBaseEvent(this);
        }
        if (roleListFragment != null) {
            roleListFragment.updateUserList();
        }
    }

    private void backOrFinish() {
        Fragment fragment=getSupportFragmentManager().findFragmentById(R.id.fragmentContent);
        if (fragment instanceof LoginFragment){
            finish();
        }else if(fragment instanceof  RoleListFragment){
            exitDialog();
        }
    }
    private void releaseAnyChatSDK(){
        if(anyChatSDK!=null) {
            anyChatSDK.LeaveRoom(-1);
            anyChatSDK.Logout();
        }
        anyChatSDK=null;
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        unRegisterBroadcastReceiver();
        releaseAnyChatSDK();
    }
}
