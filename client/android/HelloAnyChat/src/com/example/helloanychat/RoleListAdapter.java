package com.example.helloanychat;

import java.util.List;
import java.util.Random;

import android.R.raw;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

public class RoleListAdapter extends BaseAdapter {
	private Context mContext;
	private List<RoleInfo> mRoleList;

	public RoleListAdapter(Context context, List<RoleInfo> roleInfos) {
		super();
		mContext = context;
		mRoleList = roleInfos;
	}

	@Override
	public int getCount() {
		return mRoleList.size();
	}

	@Override
	public Object getItem(int position) {
		return mRoleList.get(position);
	}

	@Override
	public long getItemId(int position) {
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		ViewHolder holder = null;
		if (convertView == null) {
			holder = new ViewHolder();
			convertView = LayoutInflater.from(mContext).inflate(
					R.layout.role_list, null);
			holder.mname = (TextView) convertView.findViewById(R.id.mname);
			holder.mRoleID = (TextView) convertView.findViewById(R.id.mRoleID);
			convertView.setTag(holder);
			//设置白色底图透明度
			ImageView imageView = (ImageView)convertView.findViewById(R.id.cellBackground);
			imageView.setAlpha(position *25);
			//随机设置角色头像
			setRoleHeader(convertView);
		} else {
			holder = (ViewHolder) convertView.getTag();
		}
		RoleInfo info = mRoleList.get(position);
		holder.mname.setText("" + info.getName());
		holder.mRoleID.setText("" + info.getUserID());
		
		return convertView;
	}
	
	private void setRoleHeader(View convertView)
	{
		ImageView roleHeaderImg = (ImageView)convertView.findViewById(R.id.roleHeaderImg);
		int number = new Random().nextInt(5) + 1;
		if (number==1)
		{
			roleHeaderImg.setImageResource(R.drawable.role_1);
		}else if (number==2) {
			roleHeaderImg.setImageResource(R.drawable.role_2);
		}else if (number==3) {
			roleHeaderImg.setImageResource(R.drawable.role_3);
		}else if (number==4) {
			roleHeaderImg.setImageResource(R.drawable.role_4);
		}else if (number==5) {
			roleHeaderImg.setImageResource(R.drawable.role_5);
		}
	}

	public class ViewHolder {
		TextView mname;
		TextView mRoleID;
	}
}
