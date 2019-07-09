package com.example.common;

import com.example.anychatfeatures.R;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.ColorDrawable;
import android.support.v4.view.ViewPager.LayoutParams;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.PopupWindow;

public class RecordListMenu extends PopupWindow {
	private Button mRecordSelfBtn;
	private Button mRecordRemoteBtn;
	private Button mHybridRecordBtn;
	private Button mCancelBtn;
	private View mMenuView;
	
	public RecordListMenu(Activity content, OnClickListener itemsOnclick) {
		super(content);
		LayoutInflater inflater = (LayoutInflater)content.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		mMenuView = inflater.inflate(R.layout.localrecordmenu, null);
		mRecordSelfBtn = (Button)mMenuView.findViewById(R.id.btn_recordself);
		mRecordRemoteBtn = (Button)mMenuView.findViewById(R.id.btn_recordremote);
		mHybridRecordBtn = (Button)mMenuView.findViewById(R.id.btn_hybridrecord);
		mCancelBtn = (Button)mMenuView.findViewById(R.id.btn_cancel);
		
		mCancelBtn.setOnClickListener(itemsOnclick);
		mRecordSelfBtn.setOnClickListener(itemsOnclick);
		mRecordRemoteBtn.setOnClickListener(itemsOnclick);
		mHybridRecordBtn.setOnClickListener(itemsOnclick);
		
		this.setContentView(mMenuView);
		this.setWidth(LayoutParams.FILL_PARENT);
		this.setHeight(LayoutParams.WRAP_CONTENT);
		this.setFocusable(true);
		this.setAnimationStyle(R.style.AnimBottom);
		ColorDrawable dw = new ColorDrawable(0xb0000000);
		this.setBackgroundDrawable(dw);
		
		mMenuView.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				int height = mMenuView.findViewById(R.id.pop_layout).getTop();
				int y = (int)event.getY();
				if (event.getAction() == MotionEvent.ACTION_UP){
					if (y < height){
						dismiss();
					}
				}
				
				return true;
			}
		});
	}
	
	
}
