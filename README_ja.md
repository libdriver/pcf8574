[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCF8574

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pcf8574/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCF8574 / 74Aは、2線式双方向I2Cバス（シリアルクロック（SCL）、シリアルデータ（SDA））を介して汎用リモートI / O拡張を提供します。デバイスは、8つの準双方向ポート、100kHzI2C-で構成されます。バスインターフェース、3つのハードウェアアドレス入力、および2.5 V〜6 Vで動作する割り込み出力。準双方向ポートは、割り込みステータスまたはキーパッドを監視するための入力として、またはLEDなどのインジケータデバイスをアクティブにするための出力として個別に割り当てることができます。システムマスターは、単一のレジスタを介して入力ポートから読み取りまたは出力ポートに書き込むことができます。 2.5 uA（通常、静的）の低消費電流は、モバイルアプリケーションに最適であり、ラッチされた出力ポートはLEDを直接駆動します。PCF8574とPCF8574Aは、スレーブアドレスの固定部分が異なることを除いて同じです。 3つのハードウェアアドレスピンにより、各デバイスの8つを同じI2Cバス上に配置できるため、これらのI/OエクスパンダPCF8574/74Aを同じI2Cバス上に最大16個まとめて、最大128個のI/Oをサポートできます。 （たとえば、128個のLED）アクティブLOWオープンドレイン割り込み出力（INT）は、マイクロコントローラの割り込みロジックに接続でき、入力状態が対応する入力ポートレジスタ状態と異なる場合にアクティブになります。これは、入力状態が変化し、マイクロコントローラがI2Cバスを介して入力レジスタを継続的にポーリングせずにデバイスに問い合わせる必要があることをマイクロコントローラに示すために使用されます。内部パワーオンリセット（POR）は、I/Oを次のように初期化します。弱い内部プルアップ100uA電流源を備えた入力。 PCF8574は、LED標識およびディスプレイ、サーバー、キーパッド、産業用制御、医療機器、PLC、携帯電話、モバイルデバイス、ゲーム機、および計装テスト測定で使用されます。

LibDriver PCF8574は、LibDriverによって起動されたPCF8574の全機能ドライバーであり、I / O書き込み、I/O読み取りおよびその他の機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver PCF8574のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver PCF8574用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver PCF8574ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver PCF8574プログラミング例が含まれています。

/ docディレクトリには、LibDriver PCF8574オフラインドキュメントが含まれています。

/ datasheetディレクトリには、PCF8574データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_pcf8574_basic.h"

uint8_t res;
pcf8574_pin_level_t level;

/* basic init */
res = pcf8574_basic_init(PCF8574_ADDRESS_A000);
if (res != 0)
{
    return 1;
}

...

/* read pin */
res = pcf8574_basic_read(PCF8574_PIN_0, (pcf8574_pin_level_t *)&level);
if (res != 0)
{
    (void)pcf8574_basic_deinit();

    return 1;
}

/* write pin */
res = pcf8574_basic_write(PCF8574_PIN_0, PCF8574_PIN_LEVEL_HIGH);
if (res != 0)
{
    (void)pcf8574_basic_deinit();

    return 1;
}

...

(void)pcf8574_basic_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/pcf8574/index.html](https://www.libdriver.com/docs/pcf8574/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。