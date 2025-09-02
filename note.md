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

// ...existing code...

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