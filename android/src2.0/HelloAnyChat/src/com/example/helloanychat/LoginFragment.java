package com.example.helloanychat;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.*;
import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;


public class LoginFragment extends Fragment {
    private EditText mEditIP;
    private EditText mEditPort;
    private EditText mEditName;
    private EditText mEditRoomID;
    private TextView mBottomConnMsg;
    private TextView mBottomBuildMsg;
    private Button mBtnStart;
    private Button mBtnLogout;
    private Button mBtnWaiting;
    private LinearLayout mWaitingLayout;
    private LinearLayout mProgressLayout;
    private String mStrIP = "demo.anychat.cn";
    private String mStrName = "name";
    private int mSPort = 8906;
    private int mSRoomID = 1;
    public static final int SHOWLOGINSTATEFLAG = 1; // 显示的按钮是登陆状态的标识
    public static final int SHOWWAITINGSTATEFLAG = 2; // 显示的按钮是等待状态的标识
    public static final int SHOWLOGOUTSTATEFLAG = 3; // 显示的按钮是登出状态的标识
    private String connectMsg="Not connect to the server";


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_login,container,false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        initView(view);
        initListener();
        // 读取登陆配置表
        readLoginDate();
//        // 初始化登陆配置数据
        initLoginConfig();
//        initWaitingTips();
    }
    public AnyChatCoreSDK getAnyChatSDK(){
        if(getActivity()==null){
            return null;
        }
        return ((MainActivity)getActivity()).getAnyChatSDK();
    }
    private void initView(View view){
        mEditIP = (EditText) view.findViewById(R.id.mainUIEditIP);
        mEditPort = (EditText) view.findViewById(R.id.mainUIEditPort);
        mEditName = (EditText) view.findViewById(R.id.main_et_name);
        mEditRoomID = (EditText) view.findViewById(R.id.mainUIEditRoomID);
        mBottomConnMsg = (TextView) view.findViewById(R.id.mainUIbottomConnMsg);
        mBottomBuildMsg = (TextView) view
                .findViewById(R.id.mainUIbottomBuildMsg);
        mBtnStart = (Button) view.findViewById(R.id.mainUIStartBtn);
        mBtnLogout = (Button) view.findViewById(R.id.mainUILogoutBtn);
        mBtnWaiting = (Button) view.findViewById(R.id.mainUIWaitingBtn);
        mWaitingLayout = (LinearLayout) view.findViewById(R.id.waitingLayout);
        mWaitingLayout.setVisibility(View.INVISIBLE);
        mBottomConnMsg.setText("Not connect to the server");
        // 初始化bottom_tips信息
        mBottomBuildMsg.setText(" V" + AnyChatCoreSDK.getInstance(getActivity()).GetSDKMainVersion() + "."
                + AnyChatCoreSDK.getInstance(getActivity()).GetSDKSubVersion() + "  Build time: "
                + AnyChatCoreSDK.getInstance(getActivity()).GetSDKBuildTime());
        mBottomBuildMsg.setGravity(Gravity.CENTER_HORIZONTAL);
    }

    private void initListener(){
        mBtnStart.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {


                //普通登录
                if (checkInputData()) {

                    setBtnVisible(SHOWWAITINGSTATEFLAG);
                    mSRoomID = Integer.parseInt(mEditRoomID.getText().toString().trim());
                    mStrName = mEditName.getText().toString().trim();
                    mStrIP = mEditIP.getText().toString().trim();
                    mSPort = Integer.parseInt(mEditPort.getText().toString().trim());

                    /**
                     *AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
                     *连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
                     *连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
                     */
                    getAnyChatSDK().Connect(mStrIP, mSPort);

                    /***
                     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，
                     * 详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
                     */
                    getAnyChatSDK().Login(mStrName, "");
                }
            }
        });

        mBtnLogout.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {

                setBtnVisible(SHOWLOGINSTATEFLAG);
                getAnyChatSDK().LeaveRoom(-1);
                getAnyChatSDK().Logout();
                mBottomConnMsg.setText("Not connect to the server");
            }
        });
    }

    private void initLoginConfig() {
        mEditIP.setText(mStrIP);
        mEditName.setText(mStrName);
        mEditPort.setText(String.valueOf(mSPort));
        mEditRoomID.setText(String.valueOf(mSRoomID));
    }

    // 读取登陆数据
    private void readLoginDate() {
        SharedPreferences preferences = getActivity().getSharedPreferences("LoginInfo", 0);
        mStrIP = preferences.getString("UserIP", "demo.anychat.cn");
        mStrName = preferences.getString("UserName", "Android01");
        mSPort = preferences.getInt("UserPort", 8906);
        mSRoomID = preferences.getInt("UserRoomID", 1);
    }

    // 保存登陆相关数据
    public void saveLoginData() {
        SharedPreferences preferences = getActivity().getSharedPreferences("LoginInfo", 0);
        SharedPreferences.Editor preferencesEditor = preferences.edit();
        preferencesEditor.putString("UserIP", mStrIP);
        preferencesEditor.putString("UserName", mStrName);
        preferencesEditor.putInt("UserPort", mSPort);
        preferencesEditor.putInt("UserRoomID", mSRoomID);
        preferencesEditor.commit();
    }
    public String getRoomId(){
        return mEditRoomID.getEditableText().toString();
    }

    private boolean checkInputData() {
        String ip = mEditIP.getText().toString().trim();
        String port = mEditPort.getText().toString().trim();
        String name = mEditName.getText().toString().trim();
        String roomID = mEditRoomID.getText().toString().trim();
        if (ValueUtils.isStrEmpty(ip)) {
            mBottomConnMsg.setText("请输入IP");
            return false;
        } else if (ValueUtils.isStrEmpty(port)) {
            mBottomConnMsg.setText("请输入端口号");
            return false;
        } else if (ValueUtils.isStrEmpty(name)) {
            mBottomConnMsg.setText("请输入姓名");
            return false;
        } else if (ValueUtils.isStrEmpty(roomID)) {
            mBottomConnMsg.setText("请输入房间号");
            return false;
        } else {
            return true;
        }
    }

    // 控制登陆，等待和登出按钮状态
    public void setBtnVisible(int index) {
        if (index == SHOWLOGINSTATEFLAG) {
            mBtnStart.setVisibility(View.VISIBLE);
            mBtnLogout.setVisibility(View.GONE);
            mBtnWaiting.setVisibility(View.GONE);
            mWaitingLayout.setVisibility(View.INVISIBLE);
        } else if (index == SHOWWAITINGSTATEFLAG) {
            mBtnStart.setVisibility(View.GONE);
            mBtnLogout.setVisibility(View.GONE);
            mBtnWaiting.setVisibility(View.GONE);
            mWaitingLayout.setVisibility(View.VISIBLE);
        } else if (index == SHOWLOGOUTSTATEFLAG) {
            mBtnStart.setVisibility(View.GONE);
            mBtnLogout.setVisibility(View.VISIBLE);
            mBtnWaiting.setVisibility(View.GONE);
            mWaitingLayout.setVisibility(View.INVISIBLE);
        }
    }

    // init登陆等待状态UI
    private void initWaitingTips() {
        if (mProgressLayout == null) {
            mProgressLayout = new LinearLayout(getActivity());
            mProgressLayout.setOrientation(LinearLayout.HORIZONTAL);
            mProgressLayout.setGravity(Gravity.CENTER_VERTICAL);
            mProgressLayout.setPadding(1, 1, 1, 1);
            LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
                    ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
            params.setMargins(5, 5, 5, 5);
            ProgressBar progressBar = new ProgressBar(getActivity(), null,
                    android.R.attr.progressBarStyleLarge);
            mProgressLayout.addView(progressBar, params);
            mProgressLayout.setVisibility(View.GONE);
            mWaitingLayout.addView(mProgressLayout, new ViewGroup.LayoutParams(params));
        }
    }

    public void setConnectMsg(String connectMsg){
        Log.e("setConnectMsg","mBottomConnMsg:"+mBottomConnMsg);
        Log.e("setConnectMsg",""+connectMsg);
        this.connectMsg=connectMsg;
        if(mBottomConnMsg!=null)
            mBottomConnMsg.setText(connectMsg);
    }

    @Override
    public void onResume() {
        super.onResume();
        setConnectMsg(connectMsg);
    }
}
