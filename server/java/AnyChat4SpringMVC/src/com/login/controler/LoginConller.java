package com.login.controler;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.mvc.multiaction.MultiActionController;

import com.login.bean.User;

public class LoginConller extends MultiActionController {
	public ModelAndView onSub(HttpServletRequest request,HttpServletResponse response)
	{
		String uname = request.getParameter("uname");
		String upass = request.getParameter("upass");
		User user = new User(uname,upass);
		return new ModelAndView("index","user",user);   
	}
}
