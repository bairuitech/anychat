package com.bairuitech.demo;

import java.awt.Color;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import com.bairuitech.anychat.AnyChatCoreSDK;

public class RoomListJFrame extends JFrame implements ActionListener {
	private static final long serialVersionUID = 1L;
	public JPanel mPanlRoomlist;
	public JPanel mPanlRoomlist1;
	public JLabel mLabelEnterRomTip;
	public JLabel mLabelRoomTip;
	public JLabel mLabelIdTag;
	public JLabel mLabelNameTag;
	public JLabel mLabelLevelTag;
	public JLabel mLabelIdValue;
	public JLabel mLabelNameValue;
	public JLabel mLabelLevelValue;
	public JEditorPane mTxtRoomId;
	public JButton mBtnEnterRoom;
	public JButton mBtnExit;
	public JButton mBtnRoom1;
	public JButton mBtnRoom2;
	public JButton mBtnRoom3;
	public JButton mBtnRoom4;
	public JComboBox<String> mJComboBox1;//创建摄像头下拉列表框
	public JComboBox<String> mJComboBox2;//创建麦克风下拉列表框
	public JLabel JLabel1;
	public JLabel JLabel2;
	private AnyChatCoreSDK anychat;
	public RoomListJFrame(AnyChatCoreSDK anychat, int userId) {
		mPanlRoomlist = new JPanel();
		mPanlRoomlist1 = new JPanel();
		mLabelEnterRomTip = new JLabel("(温馨提示:双击房间名进入房间)");
		mLabelNameTag = new JLabel("昵称:");
		mLabelRoomTip = new JLabel("自定义房间:");
		mLabelIdTag = new JLabel("用户Id:");
		mLabelLevelTag = new JLabel("等级:");
		mBtnEnterRoom = new JButton("进入房间");
		mBtnExit = new JButton("退出系统");
		mLabelNameValue = new JLabel();
		mLabelLevelValue = new JLabel();
		mLabelIdValue = new JLabel();
		mBtnRoom1 = new JButton("测试房间1");
		mBtnRoom2 = new JButton("测试房间2");
		mBtnRoom3 = new JButton("测试房间3");
		mBtnRoom4 = new JButton("测试房间4");
		mJComboBox1 = new JComboBox<String>();
		mJComboBox2 = new JComboBox<String>();
		JLabel1 = new JLabel("请选择摄像头:");
		JLabel2 = new JLabel("请选择麦克风:");
		mTxtRoomId = new JEditorPane();
		this.anychat = anychat;
		initJFrame();

	}

	public void initJFrame() {
		Insets margins = new Insets(10, 10, 10, 10);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 设置关闭框架的同时结束程序
//		this.setSize(600, 400);// 设置框架大小为长300,宽200
		this.setSize(600, 500);// 设置框架大小为长300,宽200
		this.setResizable(false);// 设置框架不可以改变大小
		this.setTitle("AnyChat大厅");// 设置框架标题
		this.setForeground(Color.lightGray);
		this.setLayout(null);
		mPanlRoomlist1.setLayout(new BoxLayout(mPanlRoomlist1, BoxLayout.X_AXIS));
		mBtnEnterRoom.addActionListener(this);
		mBtnExit.addActionListener(this);
		mBtnRoom1.addActionListener(this);
		mBtnRoom2.addActionListener(this);
		mBtnRoom3.addActionListener(this);
		mBtnRoom4.addActionListener(this);
		mBtnRoom1.setBounds(45, 100, 120, 50);
		mBtnRoom2.setBounds(178, 100, 120, 50);
		mBtnRoom3.setBounds(305, 100, 120, 50);
		mBtnRoom4.setBounds(435, 100, 120, 50);
		mTxtRoomId.setMargin(margins);
		mBtnEnterRoom.setMargin(margins);
		this.mPanlRoomlist1.add(mLabelRoomTip);
		this.mPanlRoomlist1.add(mTxtRoomId);
		this.mPanlRoomlist1.add(mBtnEnterRoom);
		this.mPanlRoomlist1.add(mBtnExit);
		this.mPanlRoomlist1.setBounds(150, 400, 350, 30);
		this.add(mBtnRoom1);
		this.add(mBtnRoom2);
		this.add(mBtnRoom3);
		this.add(mBtnRoom4);
		

		JLabel1.setBounds(50, 220, 150, 30);
		this.add(JLabel1);
		final String[] cameras = anychat.EnumVideoCapture();
		if(cameras!=null&&cameras.length>0){
			for(String str:cameras){
				mJComboBox1.addItem(str);
			}
		}
		mJComboBox1.setBounds(150, 220, 350, 30);
		this.add(mJComboBox1);
		mJComboBox1.addItemListener(new ItemListener(){
            public void itemStateChanged(ItemEvent e){
                //如果选中了一个
                if (e.getStateChange() == ItemEvent.SELECTED)
                {
                	String name=(String) mJComboBox1.getSelectedItem();
                	int cameraindex = 0;
                	 for (int i = 0; i < cameras.length; i++) {
                         if (name.equals(cameras[i])) {
                        	 cameraindex = i;
                        	 AnyChatDemo.initCamera(cameraindex, name);
                             System.out.println(name);
                         }
                	 }
                }
            }
        });
		
		
		JLabel2.setBounds(50, 300, 150, 30);
		this.add(JLabel2);	
		String[] audios = anychat.EnumAudioCapture();
		if(audios!=null&&audios.length>0){
			for(String str:audios){
				mJComboBox2.addItem(str);
			}
		}
		mJComboBox2.setBounds(150, 300, 350, 30);
		this.add(mJComboBox2);
		mJComboBox2.addItemListener(new ItemListener(){
            public void itemStateChanged(ItemEvent e){
                //如果选中了一个
                if (e.getStateChange() == ItemEvent.SELECTED)
                {
                    String name=(String) mJComboBox2.getSelectedItem();
                    AnyChatDemo.initAudio(0, name);
                    System.out.println(name);
                }
            }
 
        });
		
		
		this.add(mPanlRoomlist1);
		this.setVisible(true);// 设置框架可显
	}

	public void hideLogin() {
		this.setVisible(false);
		this.dispose();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if (e.getSource() == mBtnEnterRoom) {
			int dwRoomId=0;
			String strRoomId = mTxtRoomId.getText();
			if (strRoomId.length() == 0) {
				JOptionPane.showMessageDialog(null, "请输入房间号", "错误",
						JOptionPane.ERROR_MESSAGE);
			} else {
				try
				{
				 dwRoomId = Integer.valueOf(strRoomId);
				}
				catch (Exception k) {
					// TODO: handle exception
					System.out.println(k.toString());
					dwRoomId=0;
				}
				if(dwRoomId!=0)
				 anychat.EnterRoom(dwRoomId, "");
			}
		}
		if (e.getSource() == mBtnExit) {
			anychat.Release();
			this.dispose();
		}
		if(e.getSource()==mBtnRoom1)
		{
			anychat.EnterRoom(1, "");
		}
		if(e.getSource()==mBtnRoom2)
		{
			anychat.EnterRoom(2, "");
		}
		if(e.getSource()==mBtnRoom3)
		{
			anychat.EnterRoom(3, "");
		}
		if(e.getSource()==mBtnRoom4)
		{
			anychat.EnterRoom(4, "");
		}
	}
}
