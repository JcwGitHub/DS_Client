package other.third.files;

import android.R.integer;
import android.R.string;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;

public class JniTelephone {

	private Context mContext;
	
	
	
	
	public JniTelephone(final Context _context) {
		this.mContext = _context;
		this.initData();
	}
	
	private void initData() {
		//数据初始化
	}
	
	//一键拨号
	public void JniTelephoneCall(final String number) {
		Intent _intent = new Intent(Intent.ACTION_CALL,Uri.parse("tel:" + number));
		mContext.startActivity(_intent);
	}
	
	//显示拨号界面
	public void JniTelephoneCall_DiAl(final String numbrer) {
		Intent _intent = new Intent(Intent.ACTION_DIAL,Uri.parse("tel:" + numbrer));
		mContext.startActivity(_intent);
	}
}
