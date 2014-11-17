package com.example.anychatfeatures;

import java.util.ArrayList;

import android.R.color;
import android.content.Context;
import android.graphics.Color;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;

public class MessageListView extends ListView implements
		android.widget.AdapterView.OnItemClickListener {

	private FileListAdapter mFileListAdapter;
	private ArrayList<String> mFileList = new ArrayList<String>();
	private Context mContext;

	public MessageListView(Context cont) {
		super(cont);
		mContext = cont;
		this.setCacheColorHint(0);
		mFileListAdapter = new FileListAdapter(mContext);
		setAdapter(mFileListAdapter);
		this.setOnItemClickListener(this);
	}

	public void SetFileList(ArrayList<String> userList) {
		mFileList = userList;
		// Log.e("************UserListView**********", fileList.size()+"");
		mFileListAdapter = new FileListAdapter(mContext);
		setAdapter(mFileListAdapter);
		this.invalidate();
	}

	@Override
	public void onItemClick(AdapterView<?> parent, View view, int position,
			long id) {

	}

	private class FileListAdapter extends BaseAdapter {
		private Context context;

		public FileListAdapter(Context context) {
			this.context = context;
		}

		@Override
		public int getCount() {
			return mFileList.size();
		}

		@Override
		public Object getItem(int position) {
			return mFileList.get(position);
		}

		@Override
		public long getItemId(int position) {
			return position;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			TextView tv = new TextView(context);
			tv.setTextColor(Color.BLACK);
			tv.setPadding(0, 2, 0, 2);
			tv.setTextSize(18);
			tv.setBackgroundColor(color.black);
			tv.setText(mFileList.get(position));
			return tv;
		}
	}
}