package com.bairuitech.server;

import java.awt.*;
import java.awt.event.*;
import java.io.UnsupportedEncodingException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.Vector;
import javax.swing.*;
import javax.swing.table.*;

import com.bairuitech.anychat.*;

/**
 * AnyChat Platform Core SDK ---- Business Server
 */
public class BusinessServer extends JFrame implements AnyChatServerEvent {
	private static final long serialVersionUID = 1L;
	public AnyChatServerSDK anyChatSDK;
	public StringBuilder message = new StringBuilder();
	public JTextArea showMessage;
	public JScrollPane jPanlMsg;
	public JScrollPane jPanlUser;
	public JPanel jContent;
	public JTable jTableUser;
	public JLabel jServerStatus;
	public GridBagLayout gridBagLayout;
	public GridBagConstraints gridConstraints;
	public Vector<String> tableTitles = new Vector<String>();
	public DefaultTableModel model;
	public static int iUserIdSeed = 1;
	public static final int COLUM_COUNT = 5;
	public static final int ROOM_INDEX = 3;

	// 在线用户列表
	public static ArrayList<Integer> onlineusers = new ArrayList<Integer>();
	
	
	public BusinessServer() {

		initView();
	}

	private void initUserTable() {

		tableTitles.addElement("用户ID");
		tableTitles.addElement("用户姓名");
		tableTitles.addElement("用户IP");
		tableTitles.addElement("房间ID");
		tableTitles.addElement("登录时间");
		model = new DefaultTableModel() {
			public boolean isCellEditable(int row, int column) {
				return false;
			}

		};
		// jTableUser = new JTable(tableRows, tableTitles);
		jTableUser = new JTable(model);
		jTableUser.setForeground(Color.white);
		jTableUser.setRowHeight(20);
		jTableUser.setPreferredScrollableViewportSize(new Dimension(200, 200));
		jTableUser.doLayout();
		// jTableUser.setEnabled(false);

		jTableUser.setGridColor(Color.gray);
		for (int i = 0; i < 5; i++) {
			model.addColumn(tableTitles.get(i));
		}
		DefaultTableCellRenderer render = new DefaultTableCellRenderer() {

			public void setValue(Object value) {
				// TODO Auto-generated method stub
				setForeground(Color.blue);
				super.setValue(value);

			}

		};
		render.setHorizontalAlignment(SwingConstants.CENTER);
		render.setVerticalAlignment(SwingConstants.CENTER);
		jTableUser.setDefaultRenderer(Object.class, render);
		DefaultTableCellRenderer hendRender = (DefaultTableCellRenderer) jTableUser
				.getTableHeader().getDefaultRenderer();
		Dimension d = render.getSize();
		d.height = 20;
		hendRender.setPreferredSize(d);

	}

	/**
	 * 插入登录记录
	 */
	private void updateUserData(int userId, String name, String ip, String time) {
		// 添加
		if (userId != 0) {
			Vector<Object> verctor = new Vector<Object>();
			verctor.addElement(userId);
			verctor.addElement(name);
			verctor.addElement(ip);
			verctor.addElement("");
			verctor.addElement(time);
			model.addRow(verctor);
		}

	}

	/**
	 * 删除登录记录
	 */
	private void updateUserData(int userId) {

		int index = -1;
		if ((index = findUserDataById(userId)) != -1) {
			model.removeRow(index);
		}
	}

	/**
	 * 更新用户登录房间状态讯息
	 */
	@SuppressWarnings("unchecked")
	private void updateUserData(int userId, int roomId) {
		int index = -1;
		if ((index = findUserDataById(userId)) != -1) {

			if (roomId != -1)
				model.setValueAt(roomId, index, ROOM_INDEX);
			else
				model.setValueAt("", index, ROOM_INDEX);
			jTableUser.updateUI();
			
		}
	}

	/**
	 * 根据userid查找用户讯息的相关列
	 */
	private int findUserDataById(int userId) {
		int index = -1;
		Vector userDatas = model.getDataVector();
		int size=userDatas.size();
		System.out.print(size);
		for (int i = 0; i < size; i++) {
			index = i;
			Vector<Object> vector = (Vector<Object>) userDatas.get(i);
			if (vector != null &&  vector.indexOf(userId) != -1)
				return index;
		}
		return -1;
	}

	/**
	 * 获取当前时间
	 */
	private String getCurrentTime() {
		Date date = new Date(System.currentTimeMillis());
		SimpleDateFormat sdf = new SimpleDateFormat("MM-dd HH:mm:ss:SS");
		String strTime = "";
		try {
			strTime = sdf.format(date);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return strTime;

	}

	/**
	 * 初始化界面
	 */
	public void initView() {
		// 设置panl的布局方式
		this.setLayout(null);
		showMessage = new JTextArea();
		showMessage.setEditable(false);
		jContent = new JPanel();
		jContent.setLayout(new GridLayout(2, 1));
		jPanlMsg = new JScrollPane(showMessage);
		jPanlMsg.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		jPanlMsg.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		initUserTable();
		jPanlUser = new JScrollPane(jTableUser);
		jPanlUser
				.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		jPanlUser
				.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		jPanlUser.getViewport().setBackground(Color.white);
		jServerStatus = new JLabel();
		jContent.add(jPanlUser);
		jContent.add(jPanlMsg);
		jContent.setBounds(0, 0, 850, 540);
		jServerStatus.setBounds(620, 540, 200, 30);
		this.add(jContent);
		this.add(jServerStatus);
		this.setSize(850, 600);
		this.setLocation(400, 150); // 设置程序启动默认桌面位置
		this.setResizable(false);
		this.setTitle("AnyChat Server SDK for Java 示例 (V4.8.1)");
		Toolkit toolkit = Toolkit.getDefaultToolkit();
		Image image = toolkit.createImage("bairuitech.png");
		this.setIconImage(image); // 设置图标
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 点击关闭按钮默认退出程序
		this.addWindowListener(new WindowsEvent()); // 添加窗体事件
		this.setVisible(true);
	}

	/**
	 * 初始化AnyChat Sdk
	 */
	private void initSdk() {
		anyChatSDK = new AnyChatServerSDK();
		anyChatSDK.SetServerEvent(this); // 设置回调
		anyChatSDK.InitSDK(0); // 初始化SDK
		String sdkVersion = anyChatSDK.GetSDKVersion();
		message.append(sdkVersion + "\r\n");
		showMessage.setText(message.toString());
	}

	private void generateLog(String str) {
		message.append(getCurrentTime() + "  ");
		message.append(str);
		message.append("\n");
		showMessage.setText(message.toString());
	}

	/**
	 * 主程序
	 */
	public static void main(String[] args) {

		BusinessServer anychat = new BusinessServer();
		anychat.initSdk();
	}

	/**
	 * 窗体关闭事件
	 */
	class WindowsEvent extends WindowAdapter {
		@Override
		public void windowClosing(WindowEvent e) {
			try {
				// 退出程序 释放SDK占用资源
				anyChatSDK.Release();
			} catch (Exception exception) {
				exception.printStackTrace();
			}
		}
	}

	/**
	 * 连接核心服务器回调消息
	 */
	@Override
	public void OnAnyChatServerAppMessageCallBack(int dwMsg) {
		String str = "";
		if (dwMsg == 1) {
			str = "Connect AnyChatCoreServer successed!";
			jServerStatus.setForeground(new Color(0, 128, 0));
			jServerStatus.setText(str);
		} else {
			str = "Connect AnyChatCoreServer failed!";
			jServerStatus.setForeground(Color.red);
			jServerStatus.setText(str);
		}
		generateLog(str);
		
		onlineusers.clear();
	}

	/**
	 * 用户登录验证函数，可以在此函数中进行验证登录，赋值客户端userid等操作
	 */
	@Override
	public int OnAnyChatVerifyUserCallBack(String szUserName, String szPassword, AnyChatVerifyUserOutParam outParam) {
		outParam.SetUserId(iUserIdSeed);
		outParam.SetUserLevel(0);
		outParam.SetNickName(szUserName);
		iUserIdSeed += 1;
		String str = "OnVerifyUserCallBack: userid:" + iUserIdSeed + " username: " + szUserName;
		generateLog(str);
		return 0;
	}

	/**
	 * 用户登录成功回调
	 */
	@Override
	public void OnAnyChatUserLoginActionCallBack(int dwUserId, String szUserName, int dwLevel, String szIpAddr) {
		System.out.print("OnUserLoginActionCallBack: userid:" + dwUserId
				+ " username: " + szUserName + "\r\n");
		// 测试扩展透明通道发送数据
/*		AnyChatTransTaskOutParam outParam = new AnyChatTransTaskOutParam();
		byte[] sendbuf = new byte[100];
		int ret = AnyChatServerSDK.TransBufferEx(dwUserId, sendbuf,
				sendbuf.length, 0, 0, 0, outParam);
		System.out.print("TransBufferEx: ret:" + ret + " taskid: "
				+ outParam.GetTaskId() + "\r\n");
*/
		String str = "OnAnyChatUserLoginActionCallBack: userid:" + dwUserId + " username: " + szUserName + " Ip: " + szIpAddr;
		generateLog(str);
		updateUserData(dwUserId, szUserName, szIpAddr, getCurrentTime());	
	}

	/**
	 * 用户退出登录回调
	 */
	@Override
	public void OnAnyChatUserLogoutActionCallBack(int dwUserId) {
		String str = "OnUserLogoutActionCallBack: userid:" + dwUserId;
		generateLog(str);
		updateUserData(dwUserId);
		
		// 从在线用户列表中删除
	    Iterator<Integer> it = onlineusers.iterator();
	    while(it.hasNext())
	    {
	        if(it.next() == dwUserId)
	        {
	        	it.remove();
	        	break;
	        }
	    }
	    // 核心服务器会通知其它用户（如果是好友），提示好友下线，不需要业务服务器干预

	}

	/**
	 * 用户退出登录回调
	 */
	@Override
	public int OnAnyChatPrepareEnterRoomCallBack(int dwUserId, int dwRoomId,
			String szRoomName, String szPassword) {
		String str = "OnPrepareEnterRoomCallBack: userid:" + dwUserId
				+ " roomid: " + dwRoomId;
		generateLog(str);
		return 0;
	}

	/**
	 * 用户进入房间验证回调，可以在此函数中验证登录房间
	 */
	@Override
	public void OnAnyChatUserEnterRoomActionCallBack(int dwUserId, int dwRoomId) {
		String str = "OnUserEnterRoomActionCallBack: userid:" + dwUserId
				+ " roomid: " + dwRoomId;
		generateLog(str);
		updateUserData(dwUserId, dwRoomId);
	}

	/**
	 * 用户进入房间验证回调，可以在此函数中验证登录房间
	 */
	@Override
	public void OnAnyChatUserLeaveRoomActionCallBack(int dwUserId, int dwRoomId) {
		String str = "OnAnyChatUserLeaveRoomActionCallBack: userid:" + dwUserId
				+ " roomid: " + dwRoomId;
		generateLog(str);
		updateUserData(dwUserId, -1);
	}

	/**
	 * 接收文件回调
	 */

	@Override
	public void OnAnyChatTransFile(int dwUserId, String szFileName,
			String szTempFilePath, int dwFileLength, int wParam, int lParam,
			int dwTaskId) {
		// TODO Auto-generated method stub
		String str = "OnAnyChatTransFile->" + "from:" + dwUserId + ";filename:"
				+ szFileName + "path:" + szTempFilePath;
		generateLog(str);
		showMessage.setText(message.toString());

	}

	/**
	 * 接收透明头道数据回调，
	 */
	@Override
	public void OnAnyChatTransBuffer(int dwUserId, byte[] lpBuf, int dwLen) {
		// TODO Auto-generated method stub
		String str = "";
		try {
			str = new String(lpBuf, "GB2312");
			System.out.println(str);
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		generateLog("OnAnyChatTransBuffer:" + " fromUserid:" + dwUserId + str);
	}

	/**
	 * 接收扩展透明头道数据回调，
	 */
	@Override
	public void OnAnyChatTransBufferEx(int dwUserId, byte[] lpBuf, int dwLen,
			int wParam, int lParam, int dwTaskId) {
		// TODO Auto-generated method stub

		String str = "";
		try {
			str = new String(lpBuf, "GB2312");
			System.out.println(str);
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		message.append("OnAnyChatTransBufferEx:" + " fromUserid:" + dwUserId
				+ str);
		generateLog("OnAnyChatTransBufferEx:" + " fromUserid:" + dwUserId + str);
	}

	/**
	 * 接收SDKfilter数据回调
	 */
	@Override
	public void OnAnyChatSDKFilterData(int dwUserId, byte[] lpBuf, int dwLen) {

		String str = "";
		try {
			str = new String(lpBuf, "GB2312");
			System.out.println(str);
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		message.append("OnAnyChatSDKFilterData:" + " fromUserid:" + dwUserId
				+ str);
		generateLog("OnAnyChatSDKFilterData:" + " fromUserid:" + dwUserId + str);

	}

	@Override
	public void OnAnyChatTimerEventCallBack() {
		System.out.print("OnTimerEventCallBack\r\n");

	}

	/**
	 * 文字消息回调，客户端调用文字发送api会触发该回调
	 */
	@Override
	public void OnAnyChatRecvUserTextMsgCallBack(int dwRoomId, int dwSrcUserId,
			int dwTarUserId, int bSecret, String szTextMessage, int dwLen) {
		String str = "OnAnyChatRecvUserTextMsgCallBack: " + dwSrcUserId
				+ " to " + dwTarUserId + " " + szTextMessage;
		generateLog(str);

	}

	/**
	 * 服务器录像回调函数，由中心录像服务器触发
	 * 参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=20&extra=page%3D1
	 */
	@Override
	public void OnAnyChatServerRecordCallBack(int dwUserId, int dwParam,
			int dwRecordServerId, int dwElapse, String szRecordFileName) {
		// TODO Auto-generated method stub

		String str = "OnAnyChatServerRecordCallBack: dwUserId" + dwUserId + " szRecordFileName:" + szRecordFileName;
		generateLog(str);
	}

	/**
	 * 视频呼叫事件回调，客户端调用API：BRAC_VideoCallControl会触发该回调
	 */
	@Override
	public int OnAnyChatVideoCallEventCallBack(int dwEventType,
			int dwSrcUserId, int dwTarUserId, int dwErrorCode, int dwFlags,
			int dwParam, String lpUserStr) {
		String str = "OnAnyChatVideoCallEventCallBack: dwEventType:" + dwEventType + " dwSrcUserId:" + dwSrcUserId + 
			" dwTarUserId:" + dwTarUserId + " dwErrorCode:" + dwErrorCode + " dwFlags:" + dwFlags + " dwParam:" + dwParam + " lpUserStr:" + lpUserStr;
		generateLog(str);
		return 0;
	}

	/**
	 *	用户信息控制回调，客户端调用API：BRAC_UserInfoControl会触发该回调
	 */
	@Override
	public int OnAnyChatUserInfoCtrlCallBack(int dwSendUserId, int dwUserId, int dwCtrlCode, int wParam, int lParam, String lpStrValue) {
		String str = "OnAnyChatUserInfoCtrlCallBack: dwSendUserId:" + dwSendUserId + " dwUserId:" + dwUserId + " dwCtrlCode:" + 
			dwCtrlCode + " wParam:" + wParam + " lParam:" + lParam + " lpStrValue:" + lpStrValue;
		generateLog(str);
		return 0;
	}
	
	
}
