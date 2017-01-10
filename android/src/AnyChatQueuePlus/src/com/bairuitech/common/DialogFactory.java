package com.bairuitech.common;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatObjectDefine;
import com.bairuitech.main.BussinessCenter;
import com.bairuitech.main.LoginActivity;
import com.bairuitech.main.QueueActivity;
import com.example.anychatqueueplusplus.R;




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
	 *            对话框数据参数
	 * @param context
	 *            对话框位于的上下文
	 * @return 对话框实例
	 */
	public static Dialog getDialog(int dwDialogId, Object object,
			Activity context,CustomApplication mApplication) {
		mDialogFactory.initDialog(dwDialogId, object, context,mApplication);
		return mDialog;
	}

	public static int getCurrentDialogId() {
		return mCurrentDialogId;
	}

	public void initDialog(int dwDialogId, Object object, Activity context,CustomApplication mApplication) {
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
			initCallingDialog(mDialog, object,mApplication);
			break;
		case DIALOGID_CALLRESUME:
			initCallResume(mDialog, object);
			break;
		case DIALOGID_ENDCALL:
			initEndSessionResumeDialg1(mDialog, context,object,mApplication);
			break;
		case DIALOGID_EXIT:
			initQuitResumeDialg(mDialog,mApplication);
			break;
		case DIALOGID_REQUEST:
			initCallReceivedDialg(mDialog, object,mApplication);
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
		View view = mLayoutInlater.inflate(R.layout.dialog_config, null);
		mEditPort = (EditText) view.findViewById(R.id.edit_serverport);
		
		mEditPort.setText(configEntity.port + "");
		mEditIP = (EditText) view.findViewById(R.id.edit_serverip);
		mEditIP.setText(configEntity.ip);
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
				ConfigService.SaveConfig(mContext,
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

		dialog.setContentView(view, new LayoutParams(LayoutParams.WRAP_CONTENT,	LayoutParams.WRAP_CONTENT));
	}

	/***
	 * 初始化呼叫对话框
	 * @param dialog
	 * @param object
	 */
	public void initCallingDialog(final Dialog dialog, Object object, final CustomApplication mApplication) {
		final int userId = (Integer) object;
		View view = mLayoutInlater.inflate(R.layout.dialog_calling, null);
		ImageView buttonCancel = (ImageView) view.findViewById(R.id.btn_cancel);
		buttonCancel.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				BussinessCenter.VideoCallControl(
								AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY,
								userId,
								AnyChatDefine.BRAC_ERRORCODE_SESSION_QUIT,
								0, 0, "");
				dialog.dismiss();
                BussinessCenter.VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH, userId, 0, 0, 0, "");
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
				BussinessCenter.VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_REQUEST, userId, 0,	0, 0, "");
				mDialog.dismiss();
			}
		});
		String strTitle = "";
		
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
					mContext.stopService(new Intent(BaseConst.ACTION_BACK_SERVICE));
				
					intent = new Intent();
					intent.putExtra("INTENT", BaseConst.APP_EXIT);
					intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
					intent.setClass(mContext, LoginActivity.class);
					mContext.startActivity(intent);
					break;
				case DIALOG_SERCLOSE:
					mContext.stopService(new Intent(BaseConst.ACTION_BACK_SERVICE));
				
					intent = new Intent();
					intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
					intent.setClass(mContext, LoginActivity.class);
					mContext.startActivity(intent);
					break;
				case DIALOG_NETCLOSE:
					mContext.stopService(new Intent(BaseConst.ACTION_BACK_SERVICE));
					
					intent = new Intent();
					intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
					intent.setClass(mContext, LoginActivity.class);
					mContext.startActivity(intent);
					break;
				default:
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
			break;
		case DIALOG_NETCLOSE:
			strTitle = mContext.getString(R.string.str_networkcheck);
			break;
		default:
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
	public void initCallReceivedDialg(final Dialog dialog, final Object object,CustomApplication mApplication) {
		final int userId = (Integer) object;
		
		View view = mLayoutInlater.inflate(R.layout.dialog_requesting, null);
		TextView buttonAccept = (TextView) view.findViewById(R.id.btn_accept);
		TextView buttonRefuse = (TextView) view.findViewById(R.id.btn_refuse);
		TextView showView = (TextView) view.findViewById(R.id.txt_dialog_prompt);
        if (TextUtils.isEmpty(mApplication.getReceivedTips())) {
            showView.setText("座席"+mApplication.getTargetUserName()+"请求与您视频通话");
        } else {
            showView.setText(mApplication.getReceivedTips());
        }
		showView.setTextColor(Color.BLUE);
		buttonAccept.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generate)d method stub
				BussinessCenter.VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY, userId,
						AnyChatDefine.BRAC_ERRORCODE_SUCCESS, 0, 0, "");
				dialog.dismiss();
			}
		});
		
		buttonRefuse.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				BussinessCenter.VideoCallControl(
						AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY, userId,
						AnyChatDefine.BRAC_ERRORCODE_SESSION_REFUSE, 0, 0,
						"");
				dialog.dismiss();
				BussinessCenter.getBussinessCenter().stopSessionMusic();
                BussinessCenter.VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH, userId, 0, 0, 0, "");
			}
		});
		
		dialog.setContentView(view);
	}

	/***
	 * 初始化出挂断对话框
	 * @param dialog
	 */
	public void initQuitResumeDialg(final Dialog dialog,final CustomApplication mApplication) {
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
				//暂停服务
				Intent intent = new Intent();
				intent.setAction(BaseConst.ACTION_BACK_SERVICE);
				mContext.stopService(intent);
				
				//退出队列
				AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,mApplication.getCurrentQueueId(), AnyChatObjectDefine.ANYCHAT_QUEUE_CTRL_USERLEAVE, 0, 0, 0, 0, "");
				
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
	public void initEndSessionResumeDialg1(final Dialog dialog, final Activity context,
			final Object object,final CustomApplication mApplication) {
		final int userId = (Integer) object;
		Log.e("userID", userId+"");
		View view = mLayoutInlater
				.inflate(R.layout.dialog_resumeorcancel, null);
		TextView buttonPuase = (TextView) view.findViewById(R.id.btn_resume);
		TextView buttonCancel = (TextView) view.findViewById(R.id.btn_cancel);
		buttonPuase.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generate)d method stub
				
				//退出队列
				AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,mApplication.getCurrentQueueId(), AnyChatObjectDefine.ANYCHAT_QUEUE_CTRL_USERLEAVE, 0, 0, 0, 0, "");
				//调用内核方法执行；
				BussinessCenter.VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH, userId, 0,
						0, BussinessCenter.selfUserId, "");
                BaseMethod.showToast("正在结束视频通话...", context);
				
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
		mTextViewTitle = (TextView) view.findViewById(R.id.txt_dialog_prompt);
		mTextViewTitle.setTextColor(Color.BLUE);
		mTextViewTitle.setText(strTitle);
	}

	private void initDialogTitle(View view, final String strTitle,
			final int userId) {
		mTextViewTitle = (TextView) view.findViewById(R.id.txt_dialog_prompt);
		mTextViewTitle.setTextColor(Color.BLUE);
		mTextViewTitle.setTextSize(20);
		mTextViewTitle.setText(strTitle);
	}

}
