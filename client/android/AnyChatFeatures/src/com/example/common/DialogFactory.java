package com.example.common;

import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.example.anychatfeatures.R;
import com.example.funcActivity.CallingCenter;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.graphics.Color;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class DialogFactory extends Activity{
	private Activity mContext;
	private static Dialog mDialog;
	private LayoutInflater mLayoutInlater;
	private TextView mTextViewTitle;
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
	
	private AnyChatCoreSDK anyChatSDK;

	private DialogFactory() {
		anyChatSDK = AnyChatCoreSDK.getInstance(this);
	}

	public static DialogFactory getDialogFactory() {
		if (mDialogFactory == null) {
			mDialogFactory = new DialogFactory();
		}
		return mDialogFactory;
	}
	
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
		case DIALOGID_REQUEST:
			initCallReceivedDialg(mDialog, object);
			mDialog.setCancelable(false);
			break;
		case DIALOGID_EXIT:
			initEndConfirmDialg(mDialog, object);
			break;
		}
	}
	
	public void initCallingDialog(final Dialog dialog, Object object) {
		final int userId = (Integer) object;
		View view = mLayoutInlater.inflate(R.layout.dialog_calling, null);
		ImageView buttonCancel = (ImageView) view.findViewById(R.id.btn_cancel);
		buttonCancel.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				CallingCenter.getInstance().VideoCallControl(
						AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY,
						userId,
						AnyChatDefine.BRAC_ERRORCODE_SESSION_QUIT,
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
				CallingCenter.getInstance().VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_REQUEST, userId, 0,	0, 0, "");
				mDialog.dismiss();
			}
		});
		String strTitle = "";
		strTitle = "准备向" + anyChatSDK.GetUserName(userId) + "发起视频会话";
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
				CallingCenter.getInstance().VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_FINISH, userId, 0,
						0, -1, "");
				
				if (mContext != null)
					mContext.finish();
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
				CallingCenter.getInstance().VideoCallControl(AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY, userId,
						AnyChatDefine.BRAC_ERRORCODE_SUCCESS, 0, 0, "");
				dialog.dismiss();
			}
		});
		
		buttonRefuse.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				CallingCenter.getInstance().VideoCallControl(
						AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY, userId,
						AnyChatDefine.BRAC_ERRORCODE_SESSION_REFUSE, 0, 0,
						"");
				dialog.dismiss();
				
				CallingCenter.getInstance().stopSessionMusic();
			}
		});
		
		String strTitle = anyChatSDK.GetUserName(userId) + mContext.getString(R.string.sessioning_reqite);
		initDialogTitle(view, strTitle, userId);
		dialog.setContentView(view);
	}

	private void initEndConfirmDialg(final Dialog dialog, final Object object)
	{
		View view = mLayoutInlater
				.inflate(R.layout.dialog_resumeorcancel, null);
		Button buttonPuase = (Button) view.findViewById(R.id.btn_resume);
		Button buttonCancel = (Button) view.findViewById(R.id.btn_cancel);
		buttonPuase.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				if (mContext != null)
					mContext.finish();
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
					CallingCenter.getInstance().VideoCallControl(
							AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY, userId,
							AnyChatDefine.BRAC_ERRORCODE_SESSION_QUIT, 0,
							0, "");
				} else if (mCurrentDialogId == DIALOGID_REQUEST) {
					CallingCenter.getInstance().VideoCallControl(
							AnyChatDefine.BRAC_VIDEOCALL_EVENT_REPLY, userId,
							AnyChatDefine.BRAC_ERRORCODE_SESSION_REFUSE, 0,
							0, "");
					
					//BussinessCenter.getBussinessCenter().stopSessionMusic();
				}
				mDialog.dismiss();
			}
		});
		mTextViewTitle.setText(strTitle);
	}

}
