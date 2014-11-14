package com.example.funcActivity;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.example.anychatfeatures.R;
import com.example.common.ScreenInfo;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager.LayoutParams;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;


public class FileExplorer extends ListActivity {
	private List<Map<String, Object>> mFileData;
	private String mStrDir="/mnt/sdcard";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		Intent intent = this.getIntent();
		Uri uri = intent.getData();
		mStrDir = uri.getPath();

		setTitle(R.string.dialog_read_from_dir);
		mFileData = getFileData();
		MyAdapter adapter = new MyAdapter(this);
		setListAdapter(adapter);

		LayoutParams layoutParams = getWindow().getAttributes();
		layoutParams.height = (int) (ScreenInfo.HEIGHT * 0.8);
		layoutParams.width = (int) (ScreenInfo.WIDTH * 0.95);
		getWindow().setAttributes(layoutParams);
	}
	
	private List<Map<String, Object>> getFileData()
	{
		List<Map<String, Object>> list = new ArrayList<Map<String, Object>>();
		Map<String, Object> map = null;
		File f = new File(mStrDir);
		File[] files = f.listFiles();

		if (!mStrDir.equals("/mnt/sdcard")) {
			map = new HashMap<String, Object>();
			map.put("title", "Back to ../");
			map.put("info", f.getParent());
			map.put("img", R.drawable.ex_folder);
			list.add(map);
		}
		if (files != null) {
			for (int i = 0; i < files.length; i++) {
				map = new HashMap<String, Object>();
				map.put("title", files[i].getName());
				map.put("info", files[i].getPath());
				
				if (files[i].isDirectory())
					map.put("img", R.drawable.ex_folder);
				else
					map.put("img", R.drawable.ex_doc);
				list.add(map);
			}
		}
		return list;
	}
	
	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {
		if ((Integer) mFileData.get(position).get("img") == R.drawable.ex_folder) {
			mStrDir = (String) mFileData.get(position).get("info");
			mFileData = getFileData();
			MyAdapter adapter = new MyAdapter(this);
			setListAdapter(adapter);
		} else {
			finishWithResult((String) mFileData.get(position).get("info"));
		}
	}

	public final class ViewHolder {
		public ImageView img;
		public TextView title;
		public TextView info;
	}

	public class MyAdapter extends BaseAdapter {
		private LayoutInflater mInflater;

		public MyAdapter(Context context) {
			this.mInflater = LayoutInflater.from(context);
		}

		public int getCount() {
			return mFileData.size();
		}

		public Object getItem(int arg0) {
			return null;
		}

		public long getItemId(int arg0) {
			return 0;
		}

		public View getView(int position, View convertView, ViewGroup parent) {
			ViewHolder holder = null;
			if (convertView == null) {
				holder = new ViewHolder();
				convertView = mInflater.inflate(R.layout.fileexplorer, null);
				holder.img = (ImageView) convertView.findViewById(R.id.fileIcon);
				holder.title = (TextView) convertView.findViewById(R.id.fileTitle);
				holder.info = (TextView) convertView.findViewById(R.id.fileInfo);
				convertView.setTag(holder);
			} else {
				holder = (ViewHolder) convertView.getTag();
			}

			holder.img.setBackgroundResource((Integer) mFileData.get(position).get(
					"img"));
			holder.title.setText((String) mFileData.get(position).get("title"));
			holder.info.setText((String) mFileData.get(position).get("info"));
			return convertView;
		}
	}
	
	private void finishWithResult(String path) {
		Intent intent = new Intent();
		intent.putExtra("filePath", path);
		setResult(RESULT_OK, intent);
		finish();
	}
}
