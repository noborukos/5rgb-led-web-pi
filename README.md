# 5rgb-led-web-pi
<P>ラズベリーパイ3にPCA9685を接続し5個のRGB-LEDをブラウザ経由でコントロール</p>
<p> C言語によるCGIとJavascriptの連携を試す<p>
<p>ハードウェア<br>
  Raspberry Pi 3<br>
  PCA9685 <a href="http://www.nxp.com/ja/products/power-management/lighting-driver-and-controller-ics/ic-led-display-control/16-channel-12-bit-pwm-fm-plus-ic-bus-led-controller:PCA9685">16-channel, 12-bit PWM Fm+ I²C-bus LED controller<a><br>
</p>
<p>ソフトウエア<br>
  OS  Raspbian<br>
  HTTPD Apache2<br>
  GPIO,I2Cライブラリー  <a href="http://wiringpi.com/">WiringPi</a><br>
  Javascriptライブラリ  <a href="http://jscolor.com/">jscolor.js</a><br>
</p>
<p>開発環境<br>
  NetBeanes IDE（C言語、リモート開発）<br>
</p>
<p>
メモ<br>
  1. コンパイルオプションに -lwiringPi を追加<br>
  2. 生成した実行ファイル"5rgb_led_pwm.cgi"はApache2の設定でCGIを動かす場所にコピー<br>
  3. led_script.js の cgi_path を設定する<br>
  4. demo.html<br>
     led_script.js<br>
     jscolor.js は同じ場所に置く<br>
</p>
<p>
写真資料<br>
</p>
