package com.bairuitech.demo;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowEvent;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Hashtable;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.SwingConstants;

import net.sf.json.JSONArray;
import net.sf.json.JSONObject;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatRecordEvent;
import com.bairuitech.anychat.AnyChatStateChgEvent;
import com.bairuitech.anychat.AnyChatTextMsgEvent;

public class VideoJFrame extends JFrame implements AnyChatBaseEvent,
		AnyChatTextMsgEvent, AnyChatStateChgEvent, ActionListener,AnyChatRecordEvent,ItemListener {

	private static final long serialVersionUID = 1L;
	private AnyChatCoreSDK anychat;
	private int dwSelfUserId;
	private JPanel mPanlVideoSelf;
	private JPanel mPanelVideoRemote;
	private JPanel mPanelVideoLocal;
	private JPanel mPanlEditChat;
	private JList<String> mJListOnline;
	private int dwOnlines[];
	private DefaultListModel<String> mListModel;
	private JScrollPane mJScrollList;
	private JTextArea mTxtChatMsg;
	private JEditorPane mEditChatMsg;
	private JButton mBtnSend;
	private JLabel jlabelSelf;
	private JLabel jlabelRemote;
	private JLabel jRemoteLabel;
	private JLabel jlabelOnlineNum;
	private JProgressBar mProgressRemote;
	private JProgressBar mProgressLocal;
	private Hashtable<String, Integer> hashtable;
	private int dwRemoteUserid = 0;
	private JFrame jRoomListFrame;
	private static Timer mTimer;
	private static TimerTask mTimerTask;
	
	private JLabel JLabelRecord;
	private JLabel JLabelRecordMode;
	
	private JRadioButton rb_self;    
	private JRadioButton rb_remote;    
	private JRadioButton rb_both;    
	
	private JRadioButton rb_record_local;    
	private JRadioButton rb_record_server;  

	private ButtonGroup group1;
	private ButtonGroup group2;
	
	private JButton mBtnRecord;
	
	private int recordType = 0;
	private int recordMode = 0;
	private boolean recordFlag;
	
	//是否windows系统
	private boolean isWindows;
	
	public VideoJFrame(final AnyChatCoreSDK anychat, final int userId,
			final JFrame roomlistFrame) {
		this.anychat = anychat;
		this.dwSelfUserId = userId;
		jRoomListFrame = roomlistFrame;
		hashtable = new Hashtable<String, Integer>();
		
		mProgressRemote = new JProgressBar();
		mProgressLocal = new JProgressBar();
		mPanelVideoRemote = new JPanel();
		mPanelVideoLocal = new JPanel();
		
		mPanlEditChat = new JPanel();
		mJListOnline = new JList<String>();
		mTxtChatMsg = new JTextArea();
		mTxtChatMsg.setEditable(false);
		mEditChatMsg = new JEditorPane();
		mBtnSend = new JButton("发送");
		mJScrollList = new JScrollPane(mJListOnline);
		mPanlVideoSelf = new JPanel();
		jRemoteLabel = new JLabel();
		jRemoteLabel.setHorizontalAlignment(SwingConstants.CENTER);
		jRemoteLabel.setText("远程视频");
		
		JLabelRecord = new JLabel("录制对象:");
		JLabelRecordMode = new JLabel("录制模式:");
		
		rb_self = new JRadioButton("自己");    
		rb_remote = new JRadioButton("对方");
		rb_both = new JRadioButton("双方");
		
		rb_record_local = new JRadioButton("本地录制");    
		rb_record_server = new JRadioButton("服务器录制");    
		
		group1 = new ButtonGroup();
		group2 = new ButtonGroup();
		
		mBtnRecord = new JButton("开始录制");
		
		String strSelfName = anychat.GetUserName(dwSelfUserId);
		dwOnlines = anychat.GetOnlineUser();
		mListModel = new DefaultListModel<String>();
		mListModel.addElement(strSelfName);
		hashtable.put(strSelfName, dwSelfUserId);
		isWindows = System.getProperty("os.name").toLowerCase().contains("win");
		initVideoJFrame();
		initSDK();
		InitUserList();
		
//		initTimeTask();
	}

	public void initSDK() {
		anychat.SetBaseEvent(this);
		anychat.SetTextMessageEvent(this);
		anychat.SetStateChgEvent(this);
		anychat.SetRecordSnapShotEvent(this);
		anychat.bindVideo(dwSelfUserId, mPanelVideoLocal);
		if(isWindows){
			anychat.SetSDKOptionString(AnyChatDefine.BRAC_SO_RECORD_TMPDIR, "d:\\record\\video\\");
		}else{
			String path =System.getProperty("user.dir")+"//Record";
			anychat.SetSDKOptionString(AnyChatDefine.BRAC_SO_RECORD_TMPDIR, path);
		}
	}

	public int getRemoteId() {
		return dwRemoteUserid;
	}

	public JLabel getRemoteView() {
		return jlabelRemote;
	}

	// 初始化声音刷新计时器
	public void initTimeTask() {
		if (mTimer == null) {
			mTimer = new Timer();
		} else {
			mTimer.cancel();
			mTimer = null;
		}
		if (mTimerTask == null) {
			mTimerTask = new TimerTask() {

				@Override
				public void run() {
					mProgressLocal.setValue(anychat
							.GetUserSpeakVolume(dwSelfUserId));
					if (dwRemoteUserid != 0)
						mProgressRemote.setValue(anychat
								.GetUserSpeakVolume(dwRemoteUserid));

				}
			};
			mTimer.schedule(mTimerTask, 100, 100);
		} else {
			mTimerTask = null;
		}

	}

	public void initVideoJFrame() {
		this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);// 设置关闭框架的同时结束程序
		this.setSize(840, 730);// 设置框架大小为长300,宽200
		this.setResizable(false);// 设置框架不可以改变大小
		// this.enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		this.mPanlVideoSelf.setLayout(null);
		this.setTitle("AnyChat房间");// 设置框架标题
		this.setForeground(Color.lightGray);
		jlabelOnlineNum = new JLabel();
		int dwNum = dwOnlines.length + 1;
		jlabelOnlineNum.setText("在线列表:" + "(" + dwNum + "人" + ")");
		jlabelOnlineNum.setForeground(Color.blue);
		jlabelOnlineNum.setBounds(10, 10, 250, 15);
		mJScrollList.setBounds(10, 30, 250, 400);
		mJListOnline.setBackground(Color.white);
		jlabelSelf = new JLabel("本地视频:");
		jlabelSelf.setBackground(Color.green);
		jlabelSelf.setBounds(10, 440, 250, 200);
		mProgressLocal.setMaximum(100);
		mProgressLocal.setBounds(10, 650, 250, 10);
		mProgressLocal.setForeground(Color.blue);
		jRemoteLabel.setBounds(395, 5, 300, 12);
		jlabelRemote = new JLabel();
		jlabelRemote.setBackground(Color.green);
		jlabelRemote.setBounds(270, 20, 550, 400);
		mProgressRemote.setMaximum(100);
		mProgressRemote.setBounds(270, 430, 550, 10);
		mProgressRemote.setForeground(Color.blue);
		JScrollPane jPanTxtMsg = new JScrollPane(mTxtChatMsg);
		jPanTxtMsg.setBounds(270, 455, 550, 170);
		mPanlEditChat.setLayout(new BoxLayout(mPanlEditChat, BoxLayout.X_AXIS));
		mPanlEditChat.setBounds(270, 635, 550, 30);
		mPanlEditChat.add(new JLabel("文字聊天："));
		mPanlEditChat.add(mEditChatMsg);
		mBtnSend.addActionListener(this);
		
		mPanelVideoRemote.setBounds(290, 30, 500, 360);
		mPanelVideoLocal.setBounds(10, 440, 250, 200);
		
		JLabelRecord.setBounds(10, 670, 70, 30);
		JLabelRecordMode.setBounds(290, 670, 70, 30);
		rb_self.setBounds(80, 670, 70, 30);
		rb_remote.setBounds(150, 670, 70, 30);
		rb_both.setBounds(220, 670, 70, 30);
		rb_self.setSelected(true);
		rb_remote.addItemListener(this);
		rb_both.addItemListener(this);
		
		rb_record_local.setBounds(350, 670, 90, 30);
		rb_record_server.setBounds(440, 670, 90, 30);
		rb_record_local.setSelected(true);
		
		mBtnRecord.setBounds(600, 670, 90, 30);
		mBtnRecord.addActionListener(this);
		
		group1.add(rb_self);
		group1.add(rb_remote);
		group1.add(rb_both);
		
		group2.add(rb_record_local);
		group2.add(rb_record_server);
		
		mPanlVideoSelf.add(mPanelVideoRemote);
		mPanlVideoSelf.add(mPanelVideoLocal);
		
		mPanlEditChat.add(mBtnSend);
		mPanlVideoSelf.add(jlabelOnlineNum);
		mPanlVideoSelf.add(mJScrollList);
		mPanlVideoSelf.add(jRemoteLabel);
		mPanlVideoSelf.add(jlabelRemote);
		mPanlVideoSelf.add(mProgressLocal);
		mPanlVideoSelf.add(mProgressRemote);
		mPanlVideoSelf.add(jPanTxtMsg);
		mPanlVideoSelf.add(mPanlEditChat);		
		mPanlVideoSelf.add(JLabelRecord);		
		mPanlVideoSelf.add(JLabelRecordMode);	
		mPanlVideoSelf.add(rb_self);		
		mPanlVideoSelf.add(rb_remote);	
		mPanlVideoSelf.add(rb_both);	
		mPanlVideoSelf.add(rb_record_local);	
		mPanlVideoSelf.add(rb_record_server);
		mPanlVideoSelf.add(mBtnRecord);

		this.add(mPanlVideoSelf);
		this.setVisible(true);

	}

	@Override
	protected void processWindowEvent(WindowEvent arg0) {
		if (arg0.getID() == WindowEvent.WINDOW_CLOSING) {
			int tag = JOptionPane.showConfirmDialog(null, "确定关闭吗？", "温馨提示",
					JOptionPane.YES_NO_OPTION);

			if (tag == 0) {
				anychat.unbindVideo(dwSelfUserId);
				anychat.UserCameraControl(-1, 0);
				anychat.UserSpeakControl(-1, 0);
				if (dwRemoteUserid != 0) {
					anychat.unbindVideo(dwRemoteUserid);
					anychat.UserCameraControl(dwRemoteUserid, 0);
					anychat.UserSpeakControl(dwRemoteUserid, 0);
					dwRemoteUserid = 0;
				}
				anychat.LeaveRoom(-1);
				jRoomListFrame.setVisible(true);
				AnyChatDemo.initSdk();
				VideoJFrame.this.dispose();
			} else {
				return;
			}

		}
	}

	// 初始化在线用户列表
	public void InitUserList() {
		for (int i = 0; i < dwOnlines.length; i++) {
			int dwuserid = dwOnlines[i];
			String strUserName = anychat.GetUserName(dwuserid);
			mListModel.addElement(strUserName);
			hashtable.put(strUserName, dwuserid);
		}
		mJListOnline.setModel(mListModel);
		mJListOnline.addMouseListener(new MouseAdapter() {

			@Override
			public void mouseClicked(MouseEvent e) {
				if (e.getClickCount() == 2) {
					Object target = mJListOnline.getSelectedValue();
					int dwTargetId = (Integer) (hashtable.get(target));
					System.out.println("选择的用户是："+dwTargetId + "");
					if (dwTargetId != dwRemoteUserid
							&& dwTargetId != dwSelfUserId) {
						if (dwRemoteUserid != 0) {
							anychat.UserSpeakControl(dwRemoteUserid, 0);
							anychat.UserCameraControl(dwRemoteUserid, 0);
							anychat.unbindVideo(dwRemoteUserid);
							dwRemoteUserid = 0;
						}

						refreshRemoteVideo(dwTargetId);
					}

				}
				super.mouseClicked(e);
			}

		});
		refreshRemoteVideo(-1);
	}

	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {

	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {

	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {

	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {

	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		String strName = anychat.GetUserName(dwUserId);
		dwOnlines = anychat.GetOnlineUser();
		if (bEnter) {
			mListModel.add(1,strName);
			hashtable.put(strName, dwUserId);
			if(dwRemoteUserid==0){
				refreshRemoteVideo(dwUserId);
			}

		} else {
			mListModel.removeElement(strName);
			hashtable.remove(strName);
			if (dwUserId == dwRemoteUserid) {
				anychat.UserSpeakControl(dwRemoteUserid, 0);
				anychat.UserCameraControl(dwRemoteUserid, 0);
				anychat.unbindVideo(dwRemoteUserid);
				dwRemoteUserid = 0;
				refreshRemoteVideo(-1);
			}
			if(dwRemoteUserid==0){
				rb_self.setSelected(true);
			}

		}
		
		int dwNum = dwOnlines.length + 1;
		jlabelOnlineNum.setText("在线列表:" + "(" + dwNum + "人" + ")");
		
	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {

	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == mBtnSend) {
			String strContent = mEditChatMsg.getText();
			int dwTargetId;
			Object target = mJListOnline.getSelectedValue();
			try {
				dwTargetId = (Integer) (hashtable.get(target));
			} catch (Exception k) {
				dwTargetId = -1;
			}
			if (strContent.length() != 0) {
				anychat.SendTextMessage(dwTargetId, 0, strContent);
				String strTarget = formatChatMsg(dwSelfUserId, dwTargetId,
						strContent);
				mTxtChatMsg.append(strTarget + "\n");
			}
		}else if (e.getSource() == mBtnRecord) {
			if(rb_self.isSelected()){
				recordType = 0;
			}else if(rb_remote.isSelected()){
				recordType = 1;
			}else if(rb_both.isSelected()){
				recordType = 2;
			}
			if(rb_record_local.isSelected()){
				recordMode = 0;
			}else if(rb_record_server.isSelected()){
				recordMode = 1;
			}
			
			int dwFlags=AnyChatDefine.ANYCHAT_RECORD_FLAGS_VIDEO+AnyChatDefine.ANYCHAT_RECORD_FLAGS_AUDIO;//录制音视频
			int userId = dwSelfUserId;
			if(recordType == 1){
				userId = dwRemoteUserid;
			}
			JSONObject jsonObject = new JSONObject();
			if(recordType == 2){
				dwFlags = dwFlags + AnyChatDefine.ANYCHAT_RECORD_FLAGS_MULTISTREAM+AnyChatDefine.BRAC_RECORD_FLAGS_ABREAST
						+AnyChatDefine.ANYCHAT_RECORD_FLAGS_MIXAUDIO+AnyChatDefine.ANYCHAT_RECORD_FLAGS_MIXVIDEO;
				jsonObject.put("recordlayout", 2);
				
				JSONArray array = new JSONArray();
				JSONObject jsonObject1 = new JSONObject();
				jsonObject1.put("userid",dwSelfUserId );
				jsonObject1.put("streamindex",0 );
				jsonObject1.put("recordindex",0 );
				array.add(jsonObject1);
				JSONObject jsonObject2 = new JSONObject();
				jsonObject2.put("userid",dwRemoteUserid );
				jsonObject2.put("streamindex",0 );
				jsonObject2.put("recordindex",1 );
				array.add(jsonObject2);
				
				jsonObject.put("streamlist", array);
			}
			if(recordMode==1){
				dwFlags = dwFlags+AnyChatDefine.ANYCHAT_RECORD_FLAGS_SERVER+AnyChatDefine.ANYCHAT_RECORD_FLAGS_LOCALCB;
			}
			if(!recordFlag){	
				if(recordType==2){
					anychat.StreamRecordCtrlEx(-1, 1, dwFlags, 0,jsonObject.toString());
				}else{
					anychat.StreamRecordCtrlEx(userId, 1, dwFlags, 1,"录制视频");
				}				
				recordFlag = true;
				System.out.println("开始录制");
				mBtnRecord.setText("停止录制");
			}else{
				if(recordType==2){
					anychat.StreamRecordCtrlEx(-1, 0, dwFlags, 0,jsonObject.toString());
				}else{
					anychat.StreamRecordCtrlEx(userId, 0, dwFlags, 1,"录制视频");
				}
				mBtnRecord.setText("开始录制");
				System.out.println("停止录制");
				recordFlag = false;
			}		
		}
	}

	@Override
	public void OnAnyChatTextMessage(int dwFromUserid, int dwToUserid,
			boolean bSecret, String message) {
		String strTarget = formatChatMsg(dwFromUserid, dwToUserid, message);
		mTxtChatMsg.append(strTarget + "\n");
	}

	public String formatChatMsg(int dwFromUserid, int dwToUserid, String message) {
		StringBuffer strChat = new StringBuffer();
		String strTarget;
		String strFrom;
		if (dwFromUserid == dwSelfUserId)
			strFrom = "我";
		else
			strFrom = anychat.GetUserName(dwFromUserid);
		if (dwToUserid == dwSelfUserId)
			strTarget = "我";
		else if (dwToUserid == -1)
			strTarget = "所有人";
		else
			strTarget = anychat.GetUserName(dwFromUserid);
		strChat.append(strFrom + " 对 " + strTarget + " 说: " + message + " "
				+ getCurrentTime());
		return strChat.toString();
	}

	public String getCurrentTime() {
		SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
		Date date = new Date(System.currentTimeMillis());
		String strTime = "";
		try {
			strTime = sdf.format(date);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return strTime;
	}

	// 刷新远程视频
	public void refreshRemoteVideo(int dwUserid) {
		if (dwRemoteUserid != 0) {
			return;
		}
		jRemoteLabel.setText("远程视频");
		if (dwUserid == -1) {
			for (int i = 0; i < dwOnlines.length; i++) {
				int dwuserid = dwOnlines[i];
				int dwCameraStatus = anychat.GetCameraState(dwuserid);
				if (dwCameraStatus == 2) {
					dwRemoteUserid = dwuserid;
					break;
				}
			}
		} else {
			dwRemoteUserid = dwUserid;
		}
		if (dwRemoteUserid != 0) {
			String strRname = anychat.GetUserName(dwRemoteUserid);
			jRemoteLabel.setText("远程视频:  用户名:" + strRname + "  用户ID:"
					+ dwRemoteUserid);
			anychat.UserSpeakControl(dwRemoteUserid, 1);
			anychat.UserCameraControl(dwRemoteUserid, 1);
			anychat.bindVideo(dwRemoteUserid, mPanelVideoRemote);

			// 选中远程用户
			int position = 1;
			for (int i = 0; i < dwOnlines.length; i++) {
				if (dwOnlines[i] == dwRemoteUserid)
					break;
				position++;
			}
			System.out.println("position"+position);
			mJListOnline.setSelectedIndex(position);
		}
	}

	@Override
	public void OnAnyChatMicStateChgMessage(int dwUserId, boolean bOpenMic) {

	}

	@Override
	public void OnAnyChatCameraStateChgMessage(int dwUserId, int dwState) {
		if (dwState == 2) {
			refreshRemoteVideo(-1);
		}
	}

	@Override
	public void OnAnyChatChatModeChgMessage(int dwUserId, boolean bPublicChat) {

	}

	@Override
	public void OnAnyChatActiveStateChgMessage(int dwUserId, int dwState) {

	}

	@Override
	public void OnAnyChatP2PConnectStateMessage(int dwUserId, int dwState) {

	}

	@Override
	public void OnAnyChatRecordEvent(int dwUserId, int dwErrorCode,
			String lpFileName, int dwElapse, int dwFlags, int dwParam,
			String lpUserStr) {
		System.out.println(lpFileName);
		
	}

	@Override
	public void OnAnyChatSnapShotEvent(int dwUserId, int dwErrorCode,
			String lpFileName, int dwFlags, int dwParam, String lpUserStr) {
		
	}

	@Override
	public void itemStateChanged(ItemEvent e) {
		if(e.getSource()==rb_both||e.getSource()==rb_remote){
			if(dwRemoteUserid==0){
				rb_self.setSelected(true);
				System.out.println("没有其他人");
			}
		}
	}
	
}
