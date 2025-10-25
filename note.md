# C++ - Module 01
keywords: Memory allocation, pointers to members,references and switch statement

## ex00
stackで生成したオブジェクトとheapで生成したオブジェクトの違いを理解する
```
Zombie* heapZombie = newZombie("HeapFoo"); // new で生成
heapZombie->announce();
delete heapZombie; // delete で解放。開放しないとメモリリークが発生

std::cout << "-----" << std::endl;

randomChump("StackBar"); // stack で生成。スコープを抜けると自動で解放
```

## ex01 要点

### API
- Zombie* zombieHorde(int N, std::string name);
  - N <= 0 なら NULL を返す
  - new[] で N 体を一括確保し、各要素に同じ name を設定
  - 解放は必ず delete[] horde

### つまずきポイントと対策
- 配列生成にはデフォルトコンストラクタが必須
  - Zombie() をヘッダで宣言してから実装する
  - 配列生成時に呼ばれるのは Zombie()（引数なし）。引数つきは単体生成用
- ヘッダで <string> をインクルード
  - std::string 使用のため
- new(std::nothrow) と例外
  - new は失敗時 std::bad_alloc を throw
  - new(std::nothrow) は例外を投げず NULL を返すので if (!p) でチェック
- delete と delete[] の違い
  - 配列は delete[] を使用
- 同名ヘッダにジャンプしてしまう
  - 相対インクルード("../incs/…")、compile_commands.json を設定、または includePath で ex01 を優先

### std::string と NULL について
- std::string は C の文字列（char*）とは異なり、NULL を扱わない
- std::string str = NULL; はコンパイル可能であるが、未定義動作を引き起こす

[参考リンク](https://zenn.dev/kmitsunami/articles/b3dc647e5cf73d)

### new(std::nothrow) について

1．通常のnew
```cpp
Zombie* horde = new Zombie[N]; // メモリ確保に失敗すると例外をスローする
```
通常のnewは、メモリ確保に失敗した場合にstd::bad_alloc例外をスローする。初学者は扱いにくい場合がある。というか、CではNULLチェックが一般的なので、例外処理に慣れていないと混乱する。

2．new(std::nothrow)
```cpp
Zombie* horde = new(std::nothrow) Zombie[N]; // 失敗時は例外ではなくNULLを返す
```
- メモリ確保に失敗した場合、例外をスローしない
- 変わりにNULLまたはnullptrを返す
- 呼び出し側でNULLチェックを行う必要がある。Cのmallocと似たスタイル。

3．使い分けの例
```
try {
	Zombie* horde = new Zombie[N]; // 例外を使いたい場合
	// 使用コード
} catch (const std::bad_alloc& e) {
	std::cerr << "Memory allocation failed: " << e.what() << std::endl;
}

Zombie* horde = new(std::nothrow) Zombie[N]; // 例外を使いたくない場合
if (!horde) {
	std::cerr << "Memory allocation failed" << std::endl;
	// エラーハンドリング
}
```

### delete と delete[] の違い
- delete: 単一オブジェクトのメモリを解放
- delete[]: 配列のメモリを解放

例:
```cpp
Zombie* singleZombie = new Zombie("Solo");
delete singleZombie; // 単一オブジェクトの解放

Zombie* zombieHorde = new Zombie[10];
delete[] zombieHorde; // 配列の解放
```

## ex02 要点

目的
- 参照とポインタの基本を、同一オブジェクトを指す3通りで確認する。

要件
- brain: "HI THIS IS BRAIN"
- stringPTR: std::string* = &brain
- stringREF: std::string& = brain
- 出力: アドレス（&brain, stringPTR, &stringREF）と値（brain, *stringPTR, stringREF）

実装メモ
- <iostream> と <string> を明示的にインクルード（間接インクルードに依存しない）
- 参照は別名: &stringREF == &brain
- ポインタはアドレス保持: stringPTR == &brain, 参照外し *stringPTR == brain

確認
- 3つのアドレスが一致
- 3つの値が一致
- *stringPTR や stringREF で値を変更すると brain も変わる

### ポインタと参照の違い

【ポインタ】
- アドレスを格納する「変数」
- 複数の対象を指しなおせる
- NULLポインタの可能性
- メモリ消費あり

【参照】
- 元の変数の「別名」
- 初期化後は対象を変更できない
- 常に有効（NULL不可）
- メモリ消費なし

```
// ===== ポインタの場合 =====
std::string str1 = "First";
std::string str2 = "Second";

std::string* ptr = &str1;
std::cout << *ptr << std::endl;  // "First"

ptr = &str2;  // ✅ ポインタは別の変数を指すように変更可能
std::cout << *ptr << std::endl;  // "Second"


// ===== 参照の場合 =====
std::string& ref = str1;
std::cout << ref << std::endl;   // "First"

ref = str2;  // ❌ これは参照の対象を変更しようとする
             // 実際には str1 の内容が str2 の内容に変わる
std::cout << ref << std::endl;   // "Second"
std::cout << str1 << std::endl;  // "Second" ← str1も変わっている！
```
```
std::string brain = "HI THIS IS BRAIN";
std::string& ref = brain;

// 参照を通じて変更すると、元の変数も変わる
ref = "MODIFIED";
std::cout << brain << std::endl;  // "MODIFIED" ← 元の変数も変わった！

// 参照はあくまで同じ対象を指しているだけ
```
```
// ポインタ：後で初期化できる
std::string* ptr;
ptr = &brain;  // ✅ OK

// 参照：宣言時に必ず初期化しなければならない
std::string& ref;       // ❌ コンパイルエラー！
std::string& ref = brain;  // ✅ OK（初期化が必須）
```


## ex03 要点（Unnecessary violence）

目的
- 参照（Weapon&）とポインタ（Weapon*）の使い分けを体感する。

設計
- Weapon
  - メンバ: std::string type
  - 明示コンストラクタ: explicit Weapon(const std::string& type)
  - 取得: const std::string& getType() const
  - 変更: void setType(const std::string& newType)
- HumanA（常に武装）
  - メンバ: std::string name; Weapon& weapon;
  - Ctor: HumanA(const std::string& name, Weapon& weapon)
  - attack(): "<name> attacks with their <weapon type>"
- HumanB（未装備あり）
  - メンバ: std::string name; Weapon* weapon; // 初期値 NULL
  - Ctor: explicit HumanB(const std::string& name)
  - setWeapon(Weapon& w) // weapon = &w;
  - attack(): weapon が NULL の場合の扱いを用意

動作要件
- 同じ Weapon を共有するため、club.setType(...) の変更は両者の attack() 出力に反映される。

引っ掛かりポイントと対策
- 参照かポインタか
  - 常に所持 → 参照（非NULLを型で保証、付け替え不可）
  - 未装備/付け替えあり → ポインタ（NULL可、差し替え可）
- 参照の初期化
  - 参照は“別名”のため必ずコンストラクタ初期化子で結び付ける。後から付け替え不可
  - ポインタは NULL 初期化可。後から setWeapon で設定
- explicit の意味
  - 単引数コンストラクタの“暗黙変換”を禁止し、明示的に Weapon("club") と書かせる
- const の意味（getType）
  - 返り値 const std::string&: 高速・読み取り専用
  - メソッド末尾 const: 内部を変更しない契約（const オブジェクトからも呼べる）
- インクルード
  - 各ヘッダで <string> を明示的にインクルード（間接インクルードに依存しない）
- 所有権と寿命
  - HumanA/B は Weapon を所有しない（delete 不要）。Weapon の寿命が Human より長い前提

チェック
- HumanA: ctor 初期化子で weapon を初期化
- HumanB: weapon を NULL で初期化し、attack 前に NULL チェック
- 出力形式どおり（山括弧は出さない）
- valgrind --leak-check=full でリークなし

### explicit キーワードについて
explicitは、暗黙的な方変換を防ぐキーワード

1. explicitがない場合の危険性
```
// explicitなしの場合
class Weapon {
 public:
  Weapon(const std::string& type);  // explicitがない
};

// 暗黙的な変換が起こる！
Weapon w = "Sword";  // ✅ コンパイルされる
                      // std::string("Sword") が自動的に作られて
                      // Weapon のコンストラクタに渡される
```

2. explicitがある場合の安全性
```
// explicitありの場合
class Weapon {
 public:
  explicit Weapon(const std::string& type);  // explicit付き
};

Weapon w = "Sword";           // ❌ コンパイルエラー！暗黙変換は禁止
Weapon w("Sword");            // ✅ OK：明示的な呼び出し
Weapon w(std::string("Sword")); // ✅ OK：明示的な呼び出し
```

3. explicitがないと何が悪いのか？
```
// 問題のあるシナリオ
class Weapon {
 public:
  Weapon(const std::string& type);  // explicitなし
};

void selectWeapon(const Weapon& weapon) {
    // 武器を選択する処理
}

// 間違った使い方が許されてしまう
selectWeapon("Sword");  // 👈 文字列を渡しているのに、自動的にWeaponに変換される
                         // プログラマの意図が不明確
                         // バグの原因になる可能性

// explicitがあれば...
selectWeapon("Sword");  // ❌ コンパイルエラー！プログラマのミスを防げる
selectWeapon(Weapon("Sword"));  // ✅ 明示的で意図が明確
```

4. 使い分けのポイント

**判断フロー：**
- 単一引数のコンストラクタ？
  - YES → explicit を付ける（デフォルト）
  - NO → explicit なしでOK

- ただし「値をそのまま包むだけ」の場合は例外
  - UserId(int) のように、型名が値の別の言い方に過ぎない場合
  - explicit なしでも許容される（ただし付けても良い）

**具体例：**
```cpp
// ❌ explicit が必須：値を「概念化」している
explicit class Temperature(double celsius);  // 数字 ≠ 温度
explicit class Weapon(const std::string& type);  // 文字列 ≠ 武器

// ✅ explicit なしでもOK：値をそのまま「格納」するだけ
class UserId(int id);      // int = UserId（本質的に同じ）
class Counter(int count);  // int = Counter（単なる別名）
std::string("text");       // 標準ライブラリの例
```

**結論：迷ったら explicit を付ける。安全性が上がり、意図が明確になる。**


## ex04 要点（Sed is for losers）

目的
- ファイル内の文字列 s1 を s2 に“全置換”し、<filename>.replace を出力

ルール
- C のファイル関数禁止（fopen 等）
- std::string::replace 禁止（find/erase/insert などは可）
- 予期しない入力とエラーを適切に処理

設計
- FileReplacer: _in, _out(_in + ".replace"), _s1, _s2
- run(err): 読み込み → 置換 → 書き込み（失敗時 false と err）
- replacerAll(src, from, to): find + erase + insert のループで全置換

実装メモ
- 入力: std::ifstream(_in.c_str(), std::ios::in | std::ios::binary)
- 出力: std::ofstream(_out.c_str(), std::ios::out | std::ios::binary)
- 置換:
  - while ((pos = result.find(from, pos)) != std::string::npos) { erase(pos, from.length()); insert(pos, to); pos += to.length(); }
- C++98: c_str() を渡す

エラー処理
- 引数不足 → Usage 表示（終了コード 1）
- s1 空 → "s1 must not be empty"
- 入力/出力 open 失敗、読取/書込失敗 → メッセージ設定し false

テスト
- 基本: 一致1件
- 複数一致
- 一致なし（内容不変）
- s1 空（エラー）
- 入力ファイルなし（エラー）
- from==to（不変）
- s2 空（削除になる）

注意点
- フラグ結合は |（ビットOR）。|| は不可
- from が空だと無限ループ → 事前チェック必須
- 置換後は pos を to.length() 進める


## ex05 要点（Harl 2.0）

目的
- **ポインタ・トゥ・メンバ関数**（Member Function Pointers）を使用して、複数の メンバ関数を動的に呼び出す
- `if/else if/else` の「森」を避けることが必須要件

設計
- Harl クラス
  - プライベート メンバ関数（4つ）:
    - void debug(void);     // DEBUG レベルのメッセージ出力
    - void info(void);      // INFO レベルのメッセージ出力
    - void warning(void);   // WARNING レベルのメッセージ出力
    - void error(void);     // ERROR レベルのメッセージ出力
  - パブリック メンバ関数:
    - void complain(std::string level); // レベルに応じてメンバ関数を呼び出す

肝となる実装：ポインタ・トゥ・メンバ関数とテーブル駆動設計

1. メンバ関数ポインタの型定義
```cpp
typedef void (Harl::*Action)();
```
- `(Harl::*Action)()` = Harl クラスのメンバ関数で、引数なし、返り値void のポインタ型
- `Action` という型エイリアスを定義

2. テーブル駆動設計
```cpp
struct Entry { const char* key; Action fn; };
static const Entry table[] = {
  {"DEBUG",   &Harl::debug},
  {"INFO",    &Harl::info},
  {"WARNING", &Harl::warning},
  {"ERROR",   &Harl::error},
};
```
- 文字列（レベル名）と対応するメンバ関数ポインタをペアで保持
- static const でコンパイル時に確定

3. テーブルをループで検索・実行
```cpp
for (size_t i = 0; i < sizeof(table)/sizeof(table[0]); ++i) {
  if (level == table[i].key) {
    (this->*table[i].fn)();  // メンバ関数ポインタを通じて実行
    return;
  }
}
```
- level に合致する Entry を探す
- `(this->*table[i].fn)()` でメンバ関数を呼び出す
  - `this->*` = メンバ関数ポインタを逆参照
  - `()` = 関数を実行

実装メモ
- ヘッダファイル:
  - <string> をインクルード
  - プライベート メンバ関数を宣言
  - パブリック メンバ関数 complain() を宣言
- ソースファイル:
  - 各メンバ関数は独立した実装
  - complain() 内でテーブルと typedef を定義
  - 大文字小文字を区別（"DEBUG" ≠ "debug"）

メリット
- 拡張性: 新しいレベルを追加する場合、テーブルにエントリを追加するだけ
- 保守性: if/else if/else の複雑なネスト構造がない
- 読みやすさ: テーブルを見るだけでマッピングが理解できる

チェック
- complain() が if/else を使っていない ✅
- メンバ関数ポインタを正しく使用している ✅
- すべてのレベル（DEBUG, INFO, WARNING, ERROR）を処理できる ✅
- 合致しないレベルは何もしない（関数を呼ばない）✅

テスト例
```cpp
Harl harl;
harl.complain("DEBUG");    // debug() が呼ばれる
harl.complain("INFO");     // info() が呼ばれる
harl.complain("WARNING");  // warning() が呼ばれる
harl.complain("ERROR");    // error() が呼ばれる
harl.complain("INVALID");  // 何も起こらない
```
