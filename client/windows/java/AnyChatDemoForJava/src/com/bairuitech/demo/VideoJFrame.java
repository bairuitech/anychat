package com.bairuitech.demo;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Vector;

import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.SwingConstants;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatStateChgEvent;
import com.bairuitech.anychat.AnyChatTextMsgEvent;

public class VideoJFrame extends JFrame implements AnyChatBaseEvent,
		AnyChatTextMsgEvent, AnyChatStateChgEvent, ActionListener {

	private AnyChatCoreSDK anychat;
	private int dwSelfUserId;
	private JPanel mPanlVideoSelf;
	private JPanel mPanlVideoRemote;
	private JPanel mPanlEditChat;
	private JList mJListOnline;
	private int dwOnlines[];
	private DefaultListModel mListModel;
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
	private AnychatDemo mMainInstance;
	private static Timer mTimer;
	private static TimerTask mTimerTask;

	public VideoJFrame(final AnyChatCoreSDK anychat, final int userId,
			final JFrame roomlistFrame) {
		this.anychat = anychat;
		this.dwSelfUserId = userId;
		jRoomListFrame = roomlistFrame;
		hashtable = new Hashtable<String, Integer>();
		initSDK();
		mProgressRemote = new JProgressBar();
		mProgressLocal = new JProgressBar();
		mPanlVideoRemote = new JPanel();
		mPanlEditChat = new JPanel();
		mJListOnline = new JList();
		mTxtChatMsg = new JTextArea();
		mTxtChatMsg.setEditable(false);
		mEditChatMsg = new JEditorPane();
		mBtnSend = new JButton("发送");
		mJScrollList = new JScrollPane(mJListOnline);
		mPanlVideoSelf = new JPanel();
		jRemoteLabel = new JLabel();
		jRemoteLabel.setHorizontalAlignment(SwingConstants.CENTER);
		jRemoteLabel.setText("远程视频");
		String strSelfName = anychat.GetUserName(dwSelfUserId);
		dwOnlines = anychat.GetOnlineUser();
		mListModel = new DefaultListModel();
		mListModel.addElement(strSelfName);
		hashtable.put(strSelfName, dwSelfUserId);
		initVideoJFrame();
		InitUserList();
//		initTimeTask();
	}

	public void initSDK() {
		anychat.SetBaseEvent(this);
		anychat.SetTextMessageEvent(this);
		anychat.SetStateChgEvent(this);
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
					// TODO Auto-generated method stub
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
		this.setSize(840, 700);// 设置框架大小为长300,宽200
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
		mPanlEditChat.add(mBtnSend);
		mPanlEditChat.add(mBtnSend);
		mPanlVideoSelf.add(jlabelOnlineNum);
		mPanlVideoSelf.add(mJScrollList);
		mPanlVideoSelf.add(jRemoteLabel);
		mPanlVideoSelf.add(jlabelRemote);
		mPanlVideoSelf.add(mProgressLocal);
		mPanlVideoSelf.add(mProgressRemote);
		mPanlVideoSelf.add(jPanTxtMsg);
		mPanlVideoSelf.add(mPanlEditChat);
		// initRemoteVideoView();
		this.add(mPanlVideoSelf);
		this.setVisible(true);

	}

	@Override
	protected void processWindowEvent(WindowEvent arg0) {
		// TODO Auto-generated method stub
		if (arg0.getID() == WindowEvent.WINDOW_CLOSING) {
			int tag = JOptionPane.showConfirmDialog(null, "确定关闭吗？", "温馨提示",
					JOptionPane.YES_NO_OPTION);

			if (tag == 0) {
				anychat.UserCameraControl(-1, 0);
				anychat.UserSpeakControl(-1, 0);
				if (dwRemoteUserid != 0) {
					anychat.UserCameraControl(dwRemoteUserid, 0);
					anychat.UserSpeakControl(dwRemoteUserid, 0);
					dwRemoteUserid = 0;
				}
				anychat.LeaveRoom(-1);
				jRoomListFrame.setVisible(true);
				AnychatDemo.initSdk();
				VideoJFrame.this.dispose();
//				initTimeTask();
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
				// TODO Auto-generated method stub
				if (e.getClickCount() == 2) {
					Object target = mJListOnline.getSelectedValue();
					int dwTargetId = (Integer) (hashtable.get(target));
					System.out.println(dwTargetId + "");
					if (dwTargetId != dwRemoteUserid
							&& dwTargetId != dwSelfUserId) {
						if (dwRemoteUserid != 0) {
							anychat.UserCameraControl(dwRemoteUserid, 0);
							anychat.UserSpeakControl(dwRemoteUserid, 0);
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
		String strName = anychat.GetUserName(dwUserId);
		dwOnlines = anychat.GetOnlineUser();
		if (bEnter) {
			mListModel.addElement(strName);
			hashtable.put(strName, dwUserId);

		} else {
			mListModel.removeElement(strName);
			hashtable.remove(strName);
			if (dwUserId == dwRemoteUserid) {
				anychat.UserCameraControl(dwRemoteUserid, 0);
				anychat.UserSpeakControl(dwRemoteUserid, 0);
				dwRemoteUserid = 0;
				refreshRemoteVideo(-1);
			}

		}
		int dwNum = dwOnlines.length + 1;
		jlabelOnlineNum.setText("在线列表:" + "(" + dwNum + "人" + ")");

	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// TODO Auto-generated method stub

	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
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
		}
	}

	@Override
	public void OnAnyChatTextMessage(int dwFromUserid, int dwToUserid,
			boolean bSecret, String message) {
		// TODO Auto-generated method stub
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
			// TODO Auto-generated catch block
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
			anychat.UserCameraControl(dwRemoteUserid, 1);
			anychat.UserSpeakControl(dwRemoteUserid, 1);
			anychat.SetVideoPos(dwRemoteUserid, VideoJFrame.this, 290, 30, 790,
					390);
			// 选中远程用户
			int position = 1;
			for (int i = 0; i < dwOnlines.length; i++) {

				if (dwOnlines[i] == dwRemoteUserid)
					break;
				position++;
			}
			mJListOnline.setSelectedIndex(position);
			System.out.println("position" + position + "");
		}

	}

	@Override
	public void OnAnyChatMicStateChgMessage(int dwUserId, boolean bOpenMic) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatCameraStateChgMessage(int dwUserId, int dwState) {
		// TODO Auto-generated method stub
		if (dwState == 2) {

			refreshRemoteVideo(-1);
		}
	}

	@Override
	public void OnAnyChatChatModeChgMessage(int dwUserId, boolean bPublicChat) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatActiveStateChgMessage(int dwUserId, int dwState) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatP2PConnectStateMessage(int dwUserId, int dwState) {
		// TODO Auto-generated method stub

	}
}
