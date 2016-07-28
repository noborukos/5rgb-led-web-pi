//
// LED設定CGIを呼び出すスクリプト
//
var cgi_path = '../cgi-bin/5rgb_led_pwm.cgi?';
var handleContent;
var req;
var TextNode;
var req;

// 初期化
function proc_onload()
{
	req = new XMLHttpRequest();
	//CGIのレスポンス表示エリア
	handleContent = document.getElementById('cgi-res-text');
	var text = document.createTextNode('');
	TextNode = handleContent.appendChild(text);
}

// 文字列先頭の"#"を"0x"に置き換え
function col2hex( s )
{
	var s1 = s.replace("#","0x");
	return s1;	
}

//送信要求用関数
function proc_req( led_num )
{
	if( led_num < 0 )
	{
		param_txt="-1,0x000000";	// led番号-1はLSI初期化とすべてのpwm値を設定
		req.onreadystatechange = proc_readdata;	//レスポンス
		req.open("get",cgi_path + param_txt, true);
		req.send("");
	}
	else
	{
		var led_s = ( led_num + '' );	//文字変換
		param_txt = ( led_s );
		param_txt = param_txt + "," + col2hex(document.getElementById( 'color'+led_s ).value);
		param_txt = param_txt + "\r\n";
		req.onreadystatechange = proc_readdata;	//レスポンス
		req.open("get",cgi_path + param_txt, true);
		req.send("");
	}
}

//受信用関数
function proc_readdata()
{
	if(req.readyState == 4)
	{
		var text = document.createTextNode(req.responseText);
		handleContent.removeChild(TextNode);
		TextNode = handleContent.appendChild(text,TextNode);
	}
}
