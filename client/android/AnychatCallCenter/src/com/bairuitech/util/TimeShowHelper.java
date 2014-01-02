package com.bairuitech.util;

public class TimeShowHelper {

	static int min;
	static int secord;
	static int hour;
	public static void initTimer()
	{
		min=0;
		secord=0;
		hour=0;
	}
	public  static void handleShowTime()
	{
		if(++secord>=60)
		{
			secord=0;
			min++;
			if(min>=60)
			{
				min=0;
				hour++;
			}
			if(hour>=60)
				hour=0;
		}
			
	}
	 public static String getTimeShowString()
		{
			String strShow=new String();
			if(secord/10>0)
			{
				if(min/10>0)
				{
					if(hour/10>0)
					{
						strShow=hour+":"+min+":"+secord;
					}
					else
						strShow="0"+hour+":"+min+":"+secord;
				}
				else
				{
					if(hour/10>0)
					{
						strShow=hour+"0"+min+":"+secord;
					}
					else
						strShow="0"+hour+":"+"0"+min+":"+secord;
				}
				
			}
			
			else
			{
				if(min/10>0)
				{
					if(hour/10>0)
					{
						strShow=hour+":"+min+":"+"0"+secord;
					}
					else
						strShow="0"+hour+":"+min+":"+"0"+secord;
				}
				else
				{
					if(hour/10>0)
					{
						strShow=hour+"0"+min+":"+"0"+secord;
					}
					else
						strShow="0"+hour+":"+"0"+min+":"+"0"+secord;
				}
			}
			return strShow;
				
		}
}
