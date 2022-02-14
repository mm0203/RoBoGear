# RoBoGear

作品名 : 「 RoBoGear 」 : 個人製作

制作者 : HAL名古屋　松野将之

【操作方法】
※基本的な操作及びルールは、ゲーム内で確認できます。

◆基本操作

カーソル : WASD or ↑←↓→

決定 : Enter

終了 : ESC or ×をクリック

◆ゲーム本編

移動 : WASD

操作説明 ：R

ポーズ : P

デバックモード(カメラフリー、シェーダ表示切替) : F1

◆エディットモード

オブジェクト変更、歩数変更ロード、セーブのマップ切り替え : ←→　or QE


【作品概要・ゲームシステム】

RoBoGearは、決められた歩数以内にゴールを目指すパズルゲームです。

全10ステージあり、様々なギミックを上手く使いゴールを目指します。

ゴールへの正解ルートは１つしかありません。

【制作背景・アピールポイント】

今回は、制作するうえでユーザーが一目見て分かりやすく遊びやすいゲームになるように心がけました。

UIでの操作説明表示やポーズ機能におけるやり直しなど細かい部分にもこだわり、ストレスなく手軽に遊んでもらえるゲームになっていると思います。

設計部分では、オブジェクト指向に基づいた構造で制作しました。

様々な部分で設計を練り仕様変更等にも柔軟に対応できようように心掛けました。

他には、ステージ生成ができるエディット機能を実装しておりステージ制作を手軽に行うことができます。

ステージの読み込みはCVSから行っており、ステージを作る際に外部ファイルを触る必要がありましたが、エディット機能により読み込みと書き込みを行えるようにしたで、ゲーム内のみでのステージ生成が完結できるようになりました。

また、ゲームとして見栄えが悪くないらないようにグラフィック部分においても、トゥーンシェーダ、アウトラインシェーダ、バンプマッピング、環境マッピングなど実装しました。

ゲーム内部だけでなく見た目も悪くない内容になっていると思います。

次回はデータ指向やECSなどでゲーム制作したいと考えているので、今回の作品が足掛かりになればと思っています。

【著作物】

・いらすとや　https://www.irasutoya.com/

・魔王魂　https://maoudamashii.jokersounds.com/music_se.html

・効果音ラボ　https://soundeffect-lab.info/

# 画像

![title](https://user-images.githubusercontent.com/95344747/153701751-5a5c95fd-6f39-4caf-bd76-ef91b39da794.png)

![github1](https://user-images.githubusercontent.com/95344747/153841710-e7a27db6-ba2b-41d4-aa62-70c2bc9ab140.png)

![edit](https://user-images.githubusercontent.com/95344747/153849661-fdb1a847-c71f-4fbc-b276-cc598aea69d0.png)
