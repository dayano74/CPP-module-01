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