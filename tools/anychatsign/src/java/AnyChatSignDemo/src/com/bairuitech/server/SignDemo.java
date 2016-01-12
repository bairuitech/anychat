package com.bairuitech.server;

import com.bairuitech.anychat.*;

public class SignDemo {
	
	/**
	 * 实现非对称加密算法（RSA）的签名
	 * 通常来说，非对称加密签名及验证的工作流程为：
	 *	1、业务服务器只需要实现使用私钥进行签名（RsaSign），然后将签名结果（timestamp、sigstr）反馈给客户端；
	 *	2、在客户端调用LoginEx接口进行登录；
	 *	3、AnyChat服务器收到登录请求后，会使用公钥进行签名信息验证（RsaVerify），确认登录者身份，反馈结果给客户端；
	 *	4、客户端将触发登录回调事件：OnAnyChatLoginResult(int errorcode)，如果errorcode=0表示身份验证成功。
	 */
	public static void main(String[] args)
	{
		String privatekey =  
				"-----BEGIN RSA PRIVATE KEY-----\n" +
				"MIICWwIBAAKBgQDc/sgvXXKZrr8lX9pZgZMO9y8jRq/s3YYlJ/BayEvj9EIVhiXG\r"+
				"A3rZwhh0+L4UdkPE5o/t6Bh1oY6nlGvkFuENgFwkRzrn2qP7wl3MgJD8WW6OM4JA\r"+
				"1fd2Wwt/TUENQeoN30bluy4ZQPby+bGl3ic5JW0hXhEWHAjk7e0ruSxRbwIDAQAB\r"+
				"AoGALbcSyCGHlFz+s4eJjpxsRFtDyANWXyRQHJ2PbegjMsuTZAp1A+oyXpt1HbVa\r"+
				"9LamPDQJsAgkDylVbjsYun01Hoh0i+lV5rOwWpwZC1jo4ohS1MAVPaRofCD2BlCJ\r"+
				"ML3i+qIznqJu7VpC2YjULTVphUf5guUetr+iP1lkNrKhRNkCQQDxwn7BO9qw5V53\r"+
				"/5CG9z+PAPYR2Be+cD/cuGP8ooovkZ+tJ76UXSkwXwveDFf8civdkUB9v0P/EKyS\r"+
				"UMp8u4hNAkEA6gMtlFA1+ju6pTjMnxa8cmgPYXinY70OxgpOfyz7Erp2Xmq+4J3Y\r"+
				"AQeerY/aJ3K4itKgyyPXsi9cCPxv6UxeqwJAQHAS0PZfJ986+skHgLHOIxOigscS\r"+
				"LRRGMVKEdAXuxxcNdF2vkmPyYo4y35ByszrLLldU1S9xtD6BgM4/6lch0QJASVEn\r"+
				"laEv2C+ggaVzDqD798g8kWhQ4YHZQBj4kQXRwANllJ1TImKxy1jM0UoRqmxZ/zyQ\r"+
				"njSjnrMR3crhcTG5MwJANPjy150Mf+J3SHz6s1aRddggzLOMzDtObUs60ZQRi6PS\r"+
				"88K3sAbX5C1in9B0Dg5TOPanEEzsonYVIs1UZ6DqAg==\r"+
				"\n-----END RSA PRIVATE KEY-----\n"; 
		
		String publickey =   
				"-----BEGIN PUBLIC KEY-----\n"+
				"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDc/sgvXXKZrr8lX9pZgZMO9y8j\r"+
				"Rq/s3YYlJ/BayEvj9EIVhiXGA3rZwhh0+L4UdkPE5o/t6Bh1oY6nlGvkFuENgFwk\r"+
				"Rzrn2qP7wl3MgJD8WW6OM4JA1fd2Wwt/TUENQeoN30bluy4ZQPby+bGl3ic5JW0h\r"+
				"XhEWHAjk7e0ruSxRbwIDAQAB\r"+
				"\n-----END PUBLIC KEY-----\n";
		
		AnyChatOutParam signResult = new AnyChatOutParam();
		int userid = -1;
		String appid = "CED78A73-134B-4403-9992-83B79702C4A0";
		int errorcode = AnyChatSign.RsaSign(userid, appid, privatekey, signResult);
		if(errorcode == 0)
		{
			int timestamp = signResult.GetIntValue();
			String sigstr = signResult.GetStrValue();
			System.out.print("rsa sign result, timestamp: " + timestamp + " sigstr: " + sigstr + "\r\n");
			
			errorcode = AnyChatSign.RsaVerify(userid, appid, sigstr, timestamp, publickey);
			System.out.print("rsa verify result, errorcode: " + errorcode + "\r\n");
		}
	}
	

}
