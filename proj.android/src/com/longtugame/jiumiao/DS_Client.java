
package com.longtugame.jiumiao;

import org.CrossApp.lib.Cocos2dxActivity;
import org.CrossApp.lib.Cocos2dxGLSurfaceView;

import com.alibaba.sdk.android.AlibabaSDK;
import com.alibaba.sdk.android.callback.CallbackContext;
import com.alibaba.sdk.android.callback.InitResultCallback;
import com.alibaba.sdk.android.login.LoginService;
import com.alibaba.sdk.android.login.callback.LoginCallback;
import com.alibaba.sdk.android.login.callback.LogoutCallback;
import com.alibaba.sdk.android.session.model.Session;
import com.taobao.tae.sdk.SessionListener;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

public class DS_Client extends Cocos2dxActivity{
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		
		AlibabaSDK.asyncInit(this, new InitResultCallback() {
			
			@Override
			public void onFailure(int arg0, String arg1) {
				// TODO Auto-generated method stub
				Toast.makeText(DS_Client.this, "初始化失败", Toast.LENGTH_SHORT)
                .show();

			}
			
			@Override
			public void onSuccess() {
				// TODO Auto-generated method stub
				//Log.d("-----------!!!!","pppppppppppp");
				//Toast.makeText(DS_Client.this, "初始化成功", Toast.LENGTH_SHORT).show();

				
				//唤起授权页面
				LoginService loginService = AlibabaSDK.getService(LoginService.class);
				loginService.showLogin(DS_Client.this,new LoginCallback() {
					
					@Override
					public void onFailure(int arg0, String arg1) {
						// TODO Auto-generated method stub
						
					}
					
					@Override
					public void onSuccess(Session arg0) {
						// TODO Auto-generated method stub
						//Log.d("-----------!!!!","aaaaaaaaaaaaaaaa");
					}
				} );
				
				
				
			}
		});
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// DS_Client should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("CrossApp_cpp");
    }  
    
    @Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
    	if (resultCode == RESULT_OK) {
            // 返回成功，淘宝将返回正确的信息，信息保存在intent中的result项中.
            Toast.makeText(this, data.getStringExtra("result"), Toast.LENGTH_SHORT).show();
        } else if (resultCode == RESULT_CANCELED) {
            // 用户主动取消操作.
        } else if (resultCode == -2) {
            // error,淘宝将返回错误码，同样解析intent中的result项，形式如下：
            Toast.makeText(this, data.getStringExtra("result"), Toast.LENGTH_SHORT).show();
        }
        CallbackContext.onActivityResult(requestCode, resultCode, data);
}

}
