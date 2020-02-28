package com.bairuitech.main;



import java.util.List;
import java.util.Map;

import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatObjectDefine;
import com.bairuitech.common.CustomApplication;
import com.example.anychatqueueplusplus.R;



import android.app.ProgressDialog;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.TextView;

public class YeWuAdapter extends BaseAdapter {
	private Context mcontext;
	private LayoutInflater inflater;
	private List<Map<String, Object>> list;
	private ProgressDialog pd;
	public CustomApplication mCustomApplication;
	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return list.size();
	}

	public YeWuAdapter(Context context,List<Map<String, Object>>list ,ProgressDialog pd,CustomApplication mApplication) {
		super();
		this.mcontext = context;
		this.list = list;
		this.pd = pd;
		this.mCustomApplication = mApplication;
	}

	@Override
	public Object getItem(int arg0) {
		// TODO Auto-generated method stub
		return list.get(arg0);
	}

	@Override
	public long getItemId(int position) {
		// TODO Auto-generated method stub
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		// TODO Auto-generated method stub
		ViewHolder viewHolder = null;
		if(convertView == null){
			
			inflater = LayoutInflater.from(parent.getContext());
			convertView = inflater.inflate(R.layout.yewu_item, null);
			viewHolder = new ViewHolder();
			viewHolder.button = (Button) convertView.findViewById(R.id.yewu_button);
			viewHolder.people = (TextView) convertView.findViewById(R.id.yewu_tv);
			viewHolder.name = (TextView) convertView.findViewById(R.id.yewu_name);
			convertView.setTag(viewHolder);
		}else{
			viewHolder = (ViewHolder) convertView.getTag();
		}
		String titleStr = list.get(position).get("name").toString();
		int number =(Integer) list.get(position).get("number");
		final int Id = (Integer) list.get(position).get("id");
		
		viewHolder.people.setText("当前队列有"+number+"人等待...");
		viewHolder.name.setText(titleStr);
		
		viewHolder.button.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				//进度提示
				showprogess();
				//保存进入队列的Id
				mCustomApplication.setCurrentQueueId(Id);
				//进入队列的控制指令
				AnyChatCoreSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE,Id, AnyChatObjectDefine.ANYCHAT_QUEUE_CTRL_USERENTER, 0, 0, 0, 0, "");
			
			}

			private void showprogess() {
				pd.setMessage("进入业务排队...");
				pd.setCancelable(true);
				pd.setProgress(ProgressDialog.STYLE_HORIZONTAL);
				pd.setIndeterminate(true);
				pd.show();
			}
		});

		return convertView;
	}
	public class ViewHolder{
		public Button button;
		public TextView people;
		public TextView name;
	}
}
