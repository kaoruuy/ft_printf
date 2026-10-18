*This project has been created as part of the 42 curriculum by kayoshid.*

# ft_printf

## Description

標準出力に書き込み、出力したバイト数を返す `ft_printf` の実装です。
必須の変換 `%c`、`%s`、`%p`、`%d`、`%i`、`%u`、`%x`、`%X`、`%%` に対応します。
書き込み失敗や戻り値の `int` の範囲超過では `-1` を返します。
libft、動的メモリ確保、出力バッファは使用しません。
幅・精度・フラグを扱うボーナス部分は含みません。

Linux環境を対象とし、NULLの `%s` は `(null)`、NULLの `%p` は `(nil)` と表示します。
NULLの書式文字列、未対応の指定子、末尾だけの `%` は `-1` を返します。

## Instructions

`ft_printf/` 内で実行してください。

```sh
make        # libftprintf.a を生成
make clean  # オブジェクトファイルを削除
make fclean # ライブラリも削除
make re     # 再ビルド
```

利用側で `ft_printf.h` をインクルードし、ライブラリをリンクします。
次の内容を `main.c` に保存してください。

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello %s: %d, %x, %%\n", "42", -42, 42u);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o example
./example
```

## Algorithm and data structures

`ft_printf.c` は書式文字列を先頭から順に走査します。通常の文字はそのまま出力し、
`%` の次の文字に応じて `va_arg` で対応する型の引数を取得します。
`va_list` をポインタで渡すことで、次に取得する引数の位置を共有します。
`va_start` の後は、成功・失敗のどちらでも `va_end` を呼びます。

`ft_print.c` は文字、文字列、整数、ポインタの出力を担当します。
整数は基数で割った商を再帰的に出力し、その後で余りを1桁として出力します。
10進数と16進数で同じ処理を使えるため、変換用の配列やメモリ確保が不要です。
符号付き整数は符号を先に出力し、絶対値を符号なし整数の演算で求めます。
これにより `INT_MIN` を符号付き整数として反転する際のオーバーフローを避けます。
ポインタはLinuxの `unsigned long` で保持し、`0x` に続けて16進数を出力します。

出力処理は成功時のバイト数または失敗時の `-1` を返し、呼び出し元に失敗を伝えます。
全体の時間計算量は書式文字列と出力の長さに比例します。
追加メモリは整数の桁数に比例する再帰スタックのみで、構造体やグローバル変数は使いません。

## Resources

- 課題PDF: `ft_printf.pdf` Version 12.1。
- コーディング規約: The Norm Version 4.1（英語版・日本語版）。
- `man 3 printf`: 変換指定子と戻り値。
- `man 3 stdarg`: 可変長引数の扱い。
- `man 2 write`: 標準出力への書き込みとエラー。
- `man 1 ar`、`man 1 make`: 静的ライブラリの作成とビルド。
- AI使用: Codexを課題・規約の確認、全Cファイルとヘッダー、Makefile、READMEの作成、
  および動作・規約の検証に使用しました。
