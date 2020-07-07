package com.example.helloanychat;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.*;
import com.bairuitech.anychat.AnyChatCoreSDK;

import java.util.ArrayList;
import java.util.List;

import static com.example.helloanychat.MainActivity.ACTIVITY_ID_VIDEOCONFIG;


public class RoleListFragment extends Fragment {
    private ListView mRoleList;
    private int mySelfUserId;
    private RoleListAdapter mAdapter;
    private List<RoleInfo> mRoleInfoList;
    private LinearLayout backView;
    private TextView roomIdView;
    private int roomId;
    private int userSize=1;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_role_list, container, false);
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        initView(view);
    }

    public AnyChatCoreSDK getAnyChatSDK(){
        if(getActivity()==null){
            return null;
        }
        return ((MainActivity)getActivity()).getAnyChatSDK();
    }
    public void setMySelfUserId(int mySelfUserId) {
        this.mySelfUserId = mySelfUserId;
    }

    private void initView(View view) {
        backView = (LinearLayout) view.findViewById(R.id.backView);
        roomIdView = (TextView) view.findViewById(R.id.roomIdView);
        mRoleList = (ListView) view.findViewById(R.id.roleListView);
        backView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ((MainActivity) getActivity()).exitDialog();
            }
        });
    }

    public void updateUserList() {
        if (mRoleList!=null&&getAnyChatSDK()!=null) {
            if (mRoleInfoList == null)
                this.mRoleInfoList = new ArrayList<>();
            this.mRoleInfoList.clear();
            int[] userID = getAnyChatSDK().GetOnlineUser();
            RoleInfo userMySelfInfo = new RoleInfo();
            userMySelfInfo.setName(getAnyChatSDK().GetUserName(mySelfUserId));
            userMySelfInfo.setUserID(String.valueOf(mySelfUserId));
            userMySelfInfo.setRoleIconID(R.drawable.icon_myself_photo);
            userMySelfInfo.setMySelf(true);
            mRoleInfoList.add(userMySelfInfo);

            for (int index = 0; index < userID.length; ++index) {
                RoleInfo info = new RoleInfo();
                info.setName(getAnyChatSDK().GetUserName(userID[index]));
                info.setUserID(String.valueOf(userID[index]));
                info.setRoleIconID(R.drawable.icon_other_photo);
                info.setMySelf(false);
                mRoleInfoList.add(info);
            }

            mAdapter = new RoleListAdapter(getActivity(), this.mRoleInfoList);
            mRoleList.setAdapter(mAdapter);
            mRoleList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
                @Override
                public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
                                        long arg3) {
                    if (arg2 == 0) {
                        Intent intent = new Intent();
                        intent.setClass(getActivity(), VideoConfig.class);
                        startActivityForResult(intent, ACTIVITY_ID_VIDEOCONFIG);
                        return;
                    }
                    onSelectItem(arg2);
                }
            });
        }
    }

    public void addRole(int dwUserId) {
        if (mRoleList == null) {
            return;
        }
        if (mRoleInfoList == null||mRoleInfoList.isEmpty()) {
            updateUserList();
        }
        RoleInfo info = new RoleInfo();
        info.setName(getAnyChatSDK().GetUserName(dwUserId));
        info.setUserID(String.valueOf(dwUserId));
        info.setRoleIconID(R.drawable.icon_other_photo);
        info.setMySelf(false);
        mRoleInfoList.add(info);
        mAdapter.notifyDataSetChanged();
    }

    public void removeRole(int dwUserId) {
        if (mRoleInfoList==null||mRoleInfoList.isEmpty()) {
            return;
        }
        List<RoleInfo> deleteRoleInfos = new ArrayList<>();
        for (int i = 0; i < mRoleInfoList.size(); i++) {
            if (mRoleInfoList.get(i).getUserID().equals("" + dwUserId)) {
                deleteRoleInfos.add(mRoleInfoList.get(i));
            }
        }
        mRoleInfoList.removeAll(deleteRoleInfos);
        mAdapter.notifyDataSetChanged();
    }

    private void onSelectItem(int position) {
        String strUserID = mRoleInfoList.get(position).getUserID();
        Intent intent = new Intent();
        intent.putExtra("UserID", strUserID);
        intent.setClass(getActivity(), VideoActivity.class);
        startActivity(intent);
    }

    public void setRoomId(int roomId) {
        this.roomId = roomId;
        if (roomIdView != null) {
            roomIdView.setText("房间号：" + roomId);
        }
    }

    public void updateRoomUserSize(){
        if(mRoleInfoList!=null){
             userSize=mRoleInfoList.size();
        }
        if (roomIdView != null) {
            roomIdView.setText("房间号：" + roomId+"  ("+userSize+"人)");
        }
    }

    @Override
    public void onResume() {
        super.onResume();
        if (roomIdView != null) {
            roomIdView.setText("房间号：" + roomId);
        }
        updateUserList();

    }
}
