package com.login.bean;

public class User {
	private String uname;
	private String upass;
	public User()
	{
		
	}
	public User(String uname,String upass)
	{
		this.uname = uname;
		this.upass = upass;
	}
	public String getUname() {
		return uname;
	}
	public void setUname(String uname) {
		this.uname = uname;
	}
	public String getUpass() {
		return upass;
	}
	public void setUpass(String upass) {
		this.upass = upass;
	}
	
	
}
