package other.third.files;

import com.alibaba.sdk.android.AlibabaSDK;
import com.alibaba.sdk.android.callback.InitResultCallback;
import com.alibaba.sdk.android.login.LoginService;
import com.alibaba.sdk.android.login.callback.LoginCallback;
import com.alibaba.sdk.android.login.callback.LogoutCallback;
import com.alibaba.sdk.android.session.model.Session;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

public class JniTaoBaoSdk {
	private Context mContext;
	Boolean mIsLogin  = false;
	String 	mUserId   = "";
	String  mUserName = "";
	String	mUserIcon = "";

	
	
	public JniTaoBaoSdk(final Context pContext) {
		mContext = pContext;
		
		this.init();
	} 
	
	//native
	public static native void NativeSetInfo(String uId,String uName,String uIcon,Boolean isLogin);					//获取淘宝用户信息
	public static native void NativeLoginOut(int isSuccess);	//非0表示成功
	
	private void SetInfoSuccess() {
		Log.d("java","return");	
		}
	private void init() {
		Log.d("java", "taobaoSdkInit!!!");
		
		//淘宝初始化
		AlibabaSDK.asyncInit(mContext, new InitResultCallback() {
			
			@Override
			public void onFailure(int arg0, String arg1) {
				// TODO Auto-generated method stub
				Log.d("java","taobao sdk init Fail!!");
			}
			
			@Override
			public void onSuccess() {
				// TODO Auto-generated method stub
				Log.d("java","taobao sdk init success!!"); 
				JniTaoBaoSdk.NativeSetInfo(mUserId,mUserName,mUserIcon,mIsLogin);
			}
		});
	}	
	
	//登陆服务
	public void showLogin() {
		LoginService _server = AlibabaSDK.getService(LoginService.class);
		_server.showLogin((Activity) mContext, new LoginCallback() {
			
			@Override
			public void onFailure(int arg0, String arg1) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onSuccess(Session arg0) {
				// TODO Auto-generated method stub
				LoginService _server = AlibabaSDK.getService(LoginService.class);
				mIsLogin 	= _server.getSession().isLogin();
				mUserId 	= _server.getSession().getUser().id;
				mUserName 	= _server.getSession().getUser().nick;
				mUserIcon 	= _server.getSession().getUser().avatarUrl;
				Log.d("java",mUserId);
				Log.d("java",mUserName);
				Log.d("java",mUserIcon);
				
				JniTaoBaoSdk.NativeSetInfo(mUserId,mUserName,mUserIcon,mIsLogin);
			}
		});
	}
	
	
	//登出服务
	public void closeLogin() {
		LoginService _server = AlibabaSDK.getService(LoginService.class);
		_server.logout((Activity)mContext, new LogoutCallback() {
			
			@Override
			public void onFailure(int arg0, String arg1) {
				// TODO Auto-generated method stub
				NativeLoginOut(0);
			}
			
			@Override
			public void onSuccess() {
				// TODO Auto-generated method stub
				NativeLoginOut(1);
			}
		});
	}
}
