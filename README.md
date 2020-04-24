# 『自作エミュレータで学ぶx86アーキテクチャ』をManjaroで学ぶ

## 概要

このリポジトリは『自作エミュレータで学ぶx86アーキテクチャ』のサンプルコードをManjaro（Linux）環境向けに改変したもののコレクションです．サンプルコードに同梱されているWindows用のgccやmakeを使わずに，代わりにManjaroのパッケージマネージャでインストール出来るものに置き換えています．

## 学習環境

- OS: Manjaro 20.0 Lysia
- gcc: 9.3.0

## Copyright

オリジナルのサンプルコード及びKentaが改変したソースコードは[zlibライセンス](LICENSE-origin)に従って利用，改変及び再配布して下さい．またKenta Araiが新たに作成したファイルのライセンスは別途ライセンスを明記しますので，それに従って下さい．

オリジナルのサンプルコードからの変更点は以下の通りです．

- Makefile内で参照しているツール(gcc, ndisasm等)を，サンプルコードと同梱されているものからpacmanとyay(Manjaroのパッケージマネージャ)でインストールしたものに修正
- bootsをフルスクラッチで開発しました（FAT32に対応．ただしFAT16を入力した場合の動作は未チェック．）

## リンク

- 内田公太, 上川大介, "自作エミュレータで学ぶx86アーキテクチャ コンピュータが動く仕組みを徹底理解！, " 株式会社 マイナビ出版, 2015年.: [https://book.mynavi.jp/ec/products/detail/id=41347](https://book.mynavi.jp/ec/products/detail/id=41347)
- オリジナルのサンプルコード: [tolset\_p86.zip](https://book.mynavi.jp/files/user/support/9784839954741/tolset_p86.zip)

## 連絡先

- [Twitter](https://twitter.com/isKenta14)
- [Qiita](https://qiita.com/Kenta11/items/b36efc2252272f11b105)
