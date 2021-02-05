package com.bairuitech.demo;

import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

import com.bairuitech.anychat.AnyChatCoreSDK;

public class LoginJFrame extends JFrame implements ActionListener {
	private static final long serialVersionUID = 1L;
	public JPanel mPanlLogin1;
	public JPanel mPanlLogin2;
	public JPanel mPanlLogin3;
	public JPanel mPanlLogin4;
	public JLabel mLabelLogin;
	public JLabel mLabelName;
	public JLabel mLabelPWD;
	public JTextField mTxtName;
	public JTextField mTxtServeIp;
	public JTextField mTxtServePort;
	public JPasswordField mTxtPwd;
	public JButton mBtnLogin;
	public JCheckBox mCheckAnnymous;
	public JButton mBtnSeting;
	private AnyChatCoreSDK anychat;
	public static final String SERVER_IP = "192.168.11.250";
//	public static final String SERVER_IP = "127.0.0.1";
	public static final int SERVER_PORT = 8906;

	public LoginJFrame(AnyChatCoreSDK anychat) {
		mPanlLogin1 = new JPanel();
		mPanlLogin2 = new JPanel();
		mPanlLogin3 = new JPanel();
		mPanlLogin4 =new JPanel();
		mLabelLogin = new JLabel();
		mLabelName = new JLabel();
		mLabelPWD = new JLabel();
		mTxtName = new JTextField();
		mTxtServeIp = new JTextField(SERVER_IP);
		mTxtServePort= new JTextField(String.valueOf(SERVER_PORT));
		mTxtPwd = new JPasswordField();
		mBtnLogin = new JButton();
		mBtnSeting = new JButton();
		mCheckAnnymous=new JCheckBox();
		this.anychat = anychat;
		initJFrame();

	}
	public void initJFrame() {
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 设置关闭框架的同时结束程序
		this.setSize(350, 250);// 设置框架大小为长300,宽200
		this.setResizable(false);// 设置框架不可以改变大小
		this.setTitle("用户登录");// 设置框架标题
		this.mPanlLogin1.setLayout(null);// 设置面板布局管理
		this.mPanlLogin1.setBackground(Color.cyan);// 设置面板背景颜色
		this.mPanlLogin2.setBackground(Color.blue);// 设置面板背景颜色
		this.mPanlLogin3.setBackground(Color.blue);// 设置面板背景颜色
		this.mPanlLogin4.setBackground(Color.yellow);// 设置面板背景颜色
		this.mPanlLogin2.setLayout(new BoxLayout(mPanlLogin2, BoxLayout.Y_AXIS));
		this.mLabelLogin.setText("用户登录");// 设置标签标题
		this.mLabelLogin.setFont(new Font("宋体", Font.BOLD | Font.ITALIC, 14));// 设置标签字体
		this.mLabelLogin.setForeground(Color.RED);// 设置标签字体颜色
		this.mLabelName.setText("用户名:");
		this.mLabelPWD.setText("密    码:");
		this.mBtnLogin.setText("登录");
		mBtnLogin.addActionListener(this);
		mBtnSeting.addActionListener(this);
		this.mBtnSeting.setText("设置");
		mCheckAnnymous.setText("游客登陆");
		this.mLabelLogin.setBounds(120, 15, 60, 20);// 设置标签x坐标120,y坐标15,长60,宽20
		this.mLabelName.setBounds(50, 55, 60, 20);
		this.mLabelPWD.setBounds(50, 85, 60, 25);
		this.mTxtName.setBounds(110, 55, 120, 20);
		this.mTxtPwd.setBounds(110, 85, 120, 20);
		this.mCheckAnnymous.setBounds(150, 115, 80, 20);
		this.mPanlLogin1.add(mLabelLogin);// 加载标签到面板
		this.mPanlLogin1.add(mLabelName);
		this.mPanlLogin1.add(mLabelPWD);
		this.mPanlLogin1.add(mTxtName);
		this.mPanlLogin1.add(mTxtPwd);
		this.mPanlLogin1.add(mCheckAnnymous);
		this.mPanlLogin3.add(mBtnSeting);
		this.mPanlLogin3.add(mBtnLogin);
		mPanlLogin4.add(new JLabel("服务器地址:"));
		this.mPanlLogin4.add(mTxtServeIp);
		mPanlLogin4.add(new JLabel("服务器端口:"));
		this.mPanlLogin4.add(mTxtServePort);
		this.mPanlLogin2.add(mPanlLogin3);
		this.mPanlLogin2.add(mPanlLogin4);
		this.add(mPanlLogin1, "Center");// 加载面板到框架
		this.add(mPanlLogin2, "South");// 加载面板到框架
		mPanlLogin4.setVisible(false);
		this.setVisible(true);// 设置框架可显
	}

	public void hideLogin() {
		this.setVisible(false);
		this.dispose();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if (e.getSource() == mBtnLogin) {
			
			String strName = mTxtName.getText();
			String strPasswd = String.valueOf(mTxtPwd.getPassword());
			String strServerIp=mTxtServeIp.getText();
			String strServerPort=mTxtServePort.getText();
			if(strServerIp.length()==0&&strServerPort.length()==0)
				return;
			anychat.Connect(strServerIp, Integer.valueOf(strServerPort));
			boolean bAnnyous=mCheckAnnymous.isSelected();
			if(bAnnyous)
			{
				anychat.Login("java", "");
				return;
			}
			if (strName.length() == 0) {
				JOptionPane.showMessageDialog(null, "账号不能为空", "错误",
						JOptionPane.ERROR_MESSAGE);
			} else if (strPasswd.length() == 0) {
				JOptionPane.showMessageDialog(null, "密码不能为空", "错误",
						JOptionPane.ERROR_MESSAGE);
			} else {
				anychat.Login(strName, strPasswd);
			}
		}
		if (e.getSource() == mBtnSeting) {
			
			System.out.println("btnset");
			if(mPanlLogin4.isVisible())
			{
				mPanlLogin4.setVisible(false);
				mBtnSeting.setText("设置");
			}
			else 
			{
				mPanlLogin4.setVisible(true);
				mBtnSeting.setText("隐藏");
			}
		}
	}
}
