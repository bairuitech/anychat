package com.bairuitech.util;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.bussinesscenter.BussinessCenter;
import com.bairuitech.bussinesscenter.UserItem;
import com.bairuitech.bussinesscenter.VideoCallContrlHandler;
import com.bairuitech.callcenter.LoginActivity;
import com.bairuitech.callcenter.R;

public class DialogFactory {
	private Activity mContext;
	private static Dialog mDialog;
	private LayoutInflater mLayoutInlater;
	private TextView mTextViewTitle;
	private EditText mEditIP;
	private EditText mEditPort;
	private ConfigEntity configEntity;

	public static int mCurrentDialogId = 0;

	public static final int DIALOGID_CALLING = 1;
	public static final int DIALOGID_REQUEST = 2;
	public static final int DIALOGID_RESUME = 3;
	public static final int DIALOGID_CALLRESUME = 4;
	public static final int DIALOGID_ENDCALL = 5;
	public static final int DIALOGID_EXIT = 6;
	public static final int DIALOGID_CONFIG = 7;
	public static final int DIALOGID_MEETING_INVITE = 8;
	public static final int DIALOG_SERCLOSE = 1;
	public static final int DIALOG_AGAINLOGIN = 2;
	public static final int DIALOG_NETCLOSE = 3;
	public static DialogFactory mDialogFactory = new DialogFactory();

	private DialogFactory() {
	}

	public static DialogFactory getDialogFactory() {
		if (mDialogFactory == null) {
			mDialogFactory = new DialogFactory();
		}
		return mDialogFactory;
	}

	/**
	 * 获取指定类型的对话框实例
	 * 
	 * @param dwDialogId
	 *            对话框类型
	 * @param object
	 *            对话框数据
	 * @param context
	 *            对话框位于的上下文
	 * @return 对话框实例
	 */
	public static Dialog getDialog(int dwDialogId, Object object,
			Activity context) {
		mDialogFactory.initDialog(dwDialogId, object, context);
		return mDialog;
	}

	public static int getCurrentDialogId() {
		return mCurrentDialogId;
	}

	public void initDialog(int dwDialogId, Object object, Activity context) {
		if (mContext != context) {
			mContext = context;
			mLayoutInlater = (LayoutInflater) mContext
					.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		}
		mCurrentDialogId = dwDialogId;
		mDialog = new Dialog(mContext, R.style.CommonDialog);
		mDialog.setCanceledOnTouchOutside(false);
		mDialog.setCancelable(false);
		switch (dwDialogId) {
		case DIALOGID_CALLING:
			initCallingDialog(mDialog, object);

			break;
		case DIALOGID_CALLRESUME:
			initCallResume(mDialog, object);
			break;
		case DIALOGID_ENDCALL:
			initEndSessionResumeDialg1(mDialog, object);
			break;
		case DIALOGID_EXIT:
			initQuitResumeDialg(mDialog);
			break;
		case DIALOGID_REQUEST:
			initCallReceivedDialg(mDialog, object);
			mDialog.setCancelable(false);
			break;
		case DIALOGID_RESUME:
			initResumeDialg(mDialog, object);
			break;
		case DIALOGID_CONFIG:
			initConfigDialog(mDialog, object);
			break;
		}

	}

	public static void releaseDialog() {
		mCurrentDialogId = 0;
		mDialog = null;
		mDialogFactory = null;
	}

	// 初始化设置对话框
	public void initConfigDialog(final Dialog dialog, final Object object) {
		configEntity = (ConfigEntity) object;
		View view = mLayoutInlater.inflate(
				com.bairuitech.callcenter.R.layout.dialog_config, null);
		mEditPort = (EditText) view.findViewById(R.id.edit_serverport);
		mEditPort.setText(configEntity.port + "");
		mEditIP = (EditText) view.findViewById(R.id.edit_serverip);
		mEditIP.setText(configEntity.ip);
		ImageView imageView = (ImageView) view.findViewById(R.id.image_cancel);
		Button buttonR = (Button) view.findViewById(R.id.btn_resume);
		buttonR.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				final String strServerIP = mEditIP.getText().toString();
				final String strPort = mEditPort.getText().toString();
				String strMessage = mContext
						.getString(R.string.str_serveripinput);
				if (strServerIP.length() == 0) {
					strMessage = mContext.getString(R.string.str_serveripinput);
					BaseMethod.showToast(strMessage, mContext);
					return;
				}
				if (strPort.length() == 0) {
					strMessage = mContext
							.getString(R.string.str_serverportinput);
					BaseMethod.showToast(strMessage, mContext);
					return;
				}
				configEntity.ip = strServerIP;
				configEntity.port = Integer.valueOf(strPort);
				ConfigHelper.getConfigHelper().SaveConfig(mContext,
						configEntity);
				dialog.dismiss();

			}
		});
		Button buttonC = (Button) view.findViewById(R.id.btn_cancel);
		buttonC.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				dialog.dismiss();
			}
		});
		imageView.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				dialog.dismiss();

			}
		});

		dialog.setContentView(view, new LayoutParams(LayoutParams.WRAP_CONTENT,
				LayoutParams.WRAP_CONTENT));
	}

	/***
	 * 初始化呼叫对话框
	 * 
	 * @param dialog
	 * @param object
	 */
	public void initCallingDialog(final Dialog dialog, Object object) {
		final int userId = (Integer) object;
		View view = mLayoutInlater.inflate(R.layout.dialog_calling, null);
		ImageView buttonCancel = (ImageView) view.findViewById(R.id.btn_cancel);
		buttonCancel.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				BussinessCenter
						.VideoCallContrl(
								AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY,
								userId,
								VideoCallContrlHandler.ERRORCODE_SESSION_QUIT,
								0, 0, "");
				dialog.dismiss();
			}
		});
		String strTitle = mContext.getString(R.string.str_calling);
		initDialogTitle(view, strTitle, userId);
		dialog.setContentView(view);
	}

	/***
	 * 初始化呼叫确认对话框
	 * 
	 * @param dialog
	 * @param object
	 */
	public void initCallResume(final Dialog dialog, Object object) {
		final int userId = (Integer) object;
		View view = mLayoutInlater.inflate(R.layout.dialog_call_resume, null);
		Button btnCall = (Button) view.findViewById(R.id.btn_call);
		btnCall.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generate)d method stub

				BussinessCenter.VideoCallContrl(
						AnyChatDefine.BRAC_VIDEOCALL_EVENT_REQUEST, userId, 0,
						0, 0, "");
				mDialog.dismiss();

			}
		});
		String strTitle = "";
		UserItem userItem = BussinessCenter.getBussinessCenter()
				.getUserItemByUserId(userId);
		if (userItem != null)
			strTitle = "准备向" + userItem.getUserName() + "发起视频会话";
		initDialogTitle(view, strTitle);
		dialog.setContentView(view);
	}

	/***
	 * 初始化确认对话框
	 * 
	 * @param dialog
	 * @param object
	 */
	public void initResumeDialg(final Dialog dialog, final Object object) {
		final int dwTag = (Integer) object;
		View view = mLayoutInlater.inflate(R.layout.dialog_resume, null);
		Button buttonResume = (Button) view.findViewById(R.id.btn_resume);
		buttonResume.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent intent;
				switch (dwTag) {
				case DIALOG_AGAINLOGIN:
					mContext.stopService(new Intent(
							BaseConst.ACTION_BACKSERVICE));
					intent = new Intent();
					intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
					intent.setClass(mContext, LoginActivity.class);
					mContext.startActivity(intent);
					break;
				case DIALOG_SERCLOSE:
					mContext.stopService(new Intent(
							BaseConst.ACTION_BACKSERVICE));
					intent = new Intent();
					intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
					intent.setClass(mContext, LoginActivity.class);
					mContext.startActivity(intent);
					break;
				case DIALOG_NETCLOSE:
					Intent intentSetting = new Intent();
					intentSetting
							.setAction(android.provider.Settings.ACTION_WIRELESS_SETTINGS);
					mContext.startActivity(intentSetting);
					break;

				}
				dialog.dismiss();
			}
		});

		String strTitle = "";
		switch (dwTag) {
		case DIALOG_AGAINLOGIN:
			strTitle = mContext.getString(R.string.str_againlogin);
			break;
		case DIALOG_SERCLOSE:
			strTitle = mContext.getString(R.string.str_servercolse);
			break;
		case DIALOG_NETCLOSE:
			strTitle = mContext.getString(R.string.str_networkcheck);
			break;
		}
		initDialogTitle(view, strTitle);
		dialog.setContentView(view);
	}

	/***
	 * 初始化接收到呼叫请求对话框
	 * 
	 * @param dialog
	 * @param object
	 */
	public void initCallReceivedDialg(final Dialog dialog, final Object object) {
		final int userId = (Integer) object;
		View view = mLayoutInlater.inflate(R.layout.dialog_requesting, null);
		ImageView buttonAccept = (ImageView) view.findViewById(R.id.btn_accept);
		ImageView buttonRefuse = (ImageView) view.findViewById(R.id.btn_refuse);
		// buttonAccept.setText(mContext.getString(R.string.str_resume));
		buttonAccept.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generate)d method stub
				BussinessCenter.VideoCallContrl(
						AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY, userId,
						VideoCallContrlHandler.ERRORCODE_SUCCESS, 0, 0, "");
				dialog.dismiss();

			}

		});
		buttonRefuse.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				BussinessCenter.VideoCallContrl(
						AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY, userId,
						VideoCallContrlHandler.ERRORCODE_SESSION_REFUSE, 0, 0,
						"");
				dialog.dismiss();
				BussinessCenter.sessionItem = null;
				BussinessCenter.getBussinessCenter().stopSessionMis();

			}
		});
		UserItem userItem = BussinessCenter.getBussinessCenter()
				.getUserItemByUserId(userId);
		String strTitle = "";
		if (userItem != null)
			strTitle = userItem.getUserName()
					+ mContext.getString(R.string.sessioning_reqite);

		initDialogTitle(view, strTitle, userId);
		dialog.setContentView(view);
	}

	/***
	 * 初始化退出程序对话框
	 * 
	 * @param dialog
	 */
	public void initQuitResumeDialg(final Dialog dialog) {
		View view = mLayoutInlater
				.inflate(R.layout.dialog_resumeorcancel, null);
		Button buttonQuit = (Button) view.findViewById(R.id.btn_resume);
		Button buttonCancel = (Button) view.findViewById(R.id.btn_cancel);
		buttonQuit.setText(mContext.getString(R.string.str_exit));
		buttonCancel.setText(mContext.getString(R.string.str_cancel));
		buttonQuit.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generate)d method stub
				Intent intent = new Intent();
				intent.setAction(BaseConst.ACTION_BACKSERVICE);
				mContext.stopService(intent);
				intent = new Intent();
				intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
				intent.setClass(mContext, LoginActivity.class);
				mContext.startActivity(intent);
				dialog.dismiss();

			}
		});
		buttonCancel.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				dialog.dismiss();
			}
		});

		String strTitle = mContext.getString(R.string.str_exitresume);
		initDialogTitle(view, strTitle);
		dialog.setContentView(view);
	}

	/***
	 * 初始化通话结束确认对话框
	 * 
	 * @param dialog
	 * @param object
	 */
	public void initEndSessionResumeDialg1(final Dialog dialog,
			final Object object) {
		final int userId = (Integer) object;
		View view = mLayoutInlater
				.inflate(R.layout.dialog_resumeorcancel, null);
		Button buttonPuase = (Button) view.findViewById(R.id.btn_resume);
		Button buttonCancel = (Button) view.findViewById(R.id.btn_cancel);
		buttonPuase.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generate)d method stub
				BussinessCenter.VideoCallContrl(
						AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH, userId, 0,
						0, BussinessCenter.selfUserId, "");
			}
		});
		buttonCancel.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				dialog.dismiss();
			}
		});
		String strTitle = mContext.getString(R.string.str_endsession);
		initDialogTitle(view, strTitle);
		dialog.setContentView(view);
	}

	private void initDialogTitle(View view, final String strTitle) {
		ImageView imageView = (ImageView) view.findViewById(R.id.image_cancel);
		mTextViewTitle = (TextView) view.findViewById(R.id.txt_dialog_prompt);
		mTextViewTitle.setTextColor(Color.BLUE);
		mTextViewTitle.setTextSize(20);
		imageView.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				if (mCurrentDialogId == DIALOGID_CALLING) {

				} else if (mCurrentDialogId == DIALOGID_REQUEST) {

				}
				mDialog.dismiss();
			}
		});
		mTextViewTitle.setText(strTitle);
	}

	private void initDialogTitle(View view, final String strTitle,
			final int userId) {
		ImageView imageView = (ImageView) view.findViewById(R.id.image_cancel);
		mTextViewTitle = (TextView) view.findViewById(R.id.txt_dialog_prompt);
		mTextViewTitle.setTextColor(Color.BLUE);
		mTextViewTitle.setTextSize(20);
		imageView.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				if (mCurrentDialogId == DIALOGID_CALLING) {
					BussinessCenter.VideoCallContrl(
							AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY, userId,
							VideoCallContrlHandler.ERRORCODE_SESSION_QUIT, 0,
							0, "");
				} else if (mCurrentDialogId == DIALOGID_REQUEST) {
					BussinessCenter.VideoCallContrl(
							AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY, userId,
							VideoCallContrlHandler.ERRORCODE_SESSION_REFUSE, 0,
							0, "");
					BussinessCenter.sessionItem = null;
					BussinessCenter.getBussinessCenter().stopSessionMis();
				}
				mDialog.dismiss();
			}
		});
		mTextViewTitle.setText(strTitle);
	}

}
