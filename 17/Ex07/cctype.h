#pragma once

//	charactaristic classificationの実装
//	#define isdigit(x) ((x) >= '0' && (x) <= '9')みたいに書く方法は、
//	関数マクロの副作用(http://www.dd.e-mansion.com/~kumada/laboratory/column/c_macro.html)から使うべきではないので、
//	単語ごとのルックアップテーブルを作ってビット演算で分類する実装が主流のようだ

void _ccInitialize();
bool _isdigit(char ch);
bool _islower(char ch);
bool _isupper(char ch);
bool _isalpha(char ch);
bool _isalnum(char ch);

