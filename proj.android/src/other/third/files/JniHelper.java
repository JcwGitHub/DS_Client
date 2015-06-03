package other.third.files;

import android.content.Context;

public class JniHelper {

	public static JniTelephone sC_Telephone;
	public static JniTaoBaoSdk sC_TaoBaoSdk;
	
	
	
	public static void init(final Context pContext) {
		
		//初始化电话
		JniHelper.sC_Telephone = new JniTelephone(pContext);
		
		//初始化淘宝sdk
		JniHelper.sC_TaoBaoSdk = new JniTaoBaoSdk(pContext);
	}
	
	
	
	//电话
	public static void JniHelper_CallPhone(final String pNumber)
	{
		JniHelper.sC_Telephone.JniTelephoneCall(pNumber);
	}
	public static void JniHelper_CallPhone_DiAl(final String pNumber)
	{
		JniHelper.sC_Telephone.JniTelephoneCall_DiAl(pNumber);
	}
	
	
	//淘宝sdk
	public static void JniHelper_TB_ShowLogin() {
		
	}
	
	
}
