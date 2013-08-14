package com.bairuitech.demo;
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
android.widget.AdapterView.OnItemClickListener{

	private FileListAdapter fileListAdapter;
	private ArrayList<String> fileList = new ArrayList<String>();
	private Context context;

	public MessageListView(Context cont) {
		super(cont);
		context = cont;
		this.setCacheColorHint(0);
		fileListAdapter = new FileListAdapter(context);
		setAdapter(fileListAdapter);
		this.setOnItemClickListener(this);
	}
	
	public void SetFileList(ArrayList<String> userList)
	{
		fileList = userList;
		//Log.e("************UserListView**********", fileList.size()+"");
		fileListAdapter = new FileListAdapter(context);
		setAdapter(fileListAdapter);
		this.invalidate();
	}

	@Override
	public void onItemClick(AdapterView<?> parent, View view, 
							int position,long id)
	{
		//m_HeaderActivity.ModifyMenu(fileList.get(position).getID());
		//m_RoomActivity.EnterVideo(position);
	}
	


	private class FileListAdapter extends BaseAdapter 
	{
		private Context context;

		public FileListAdapter(Context context) {
			this.context = context;
		}

		@Override
		public int getCount() {
			return fileList.size();
		}

		@Override
		public Object getItem(int position) {
			return fileList.get(position);
		}

		@Override
		public long getItemId(int position) {
			return position;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			TextView tv =  new TextView(context);
			tv.setTextColor(Color.BLACK);
			tv.setPadding(0, 2, 0, 2);
			tv.setTextSize(18);
			tv.setBackgroundColor(color.black);
			tv.setText(fileList.get(position));
			return tv;
		}
	}
}