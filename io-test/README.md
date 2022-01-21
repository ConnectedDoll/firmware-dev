# io-test
Wi-Fi 利用時の IOの動作確認のためのシンプルなサンプル

# 開発環境
[開発環境](https://github.com/ConnectedDoll/firmware#%E9%96%8B%E7%99%BA%E7%92%B0%E5%A2%83) を参考に構築

# ビルド & 導入方法
github より一式をダウンロードして PlatformIO IDE for VSCode で ビルド & 書き込みができる。

```
git clone https://github.com/ConnectedDoll/firmware-dev.git

# 必要ライブラリ 導入
cd firmware-dev/io-test/lib
./install.sh

cd ../
# cd firmware-dev/io-test/
code .
```

# Wi-Fi での接続確認

1. 電源 投入
2. SSID ConnectedDoll-DEV に接続
3. 開発環境のルーターなどの SSID,パスワード を設定する
4. Chrome 等ブラウザから `http://connecteddoll-dev.local/api/ip` へ接続してみる
5. IPアドレスの入った json が表示される筈



