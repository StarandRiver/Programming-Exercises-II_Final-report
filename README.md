# Programming-Exercises-II_Final-report
プログラミング演習IIの最終課題 2023年8月3日締め切り<br>
作成プログラム「Gear Generator」

# 歯車簡易製作ツール「Gear Generator」

## 何が出来るか
一部のCADソフトだと手順が煩雑なインボリュート歯車の曲線の作成を簡単に行えるようにする
1. モジュールと歯数あるいはピッチ円直径を入力することで歯車の全パラメータを計算
1. 計算したパラメータから，インボリュート曲線の点を算出
1. 算出した点をもとにgnuplotを用いて，画面上に歯車の概形をプレビュー

## 動作環境
- Windows環境
- gnuplotがインストールされたPC：プロットのプレビューを行う場合のみ
- dxfファイルが読み込めるCAD

初期状態だとgnuplot.exeはC:/ProgramFiles/gnuplot/binに配置されていることを前提としています．

## 使用方法
1. プログラムを起動する
1. 画面に指示されたとおりに必要なパラメータを入力する
1. 歯車が作図される

## 実行例
以下の画像は本プログラムを動作させてモジュールm=3，歯数z=44としたときの実行結果である
![実行結果例](https://github.com/StarandRiver/Programming-Exercises-II_Final-report/assets/71925121/21a7af6a-7b3b-487f-b9c7-fc1d140d3f0e)

## (参考)実行中の動画
![実行動画](https://github.com/StarandRiver/Programming-Exercises-II_Final-report/assets/71925121/1f1f4a7d-5715-4f87-9d5a-fcf0a54efee9)
