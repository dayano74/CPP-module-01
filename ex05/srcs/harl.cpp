// #include "../incs/Harl.hpp"
// // ...existing code...

// void Harl::complain(std::string level) {
//   // Step 1) 「メンバ関数ポインタ型」を別名で用意
//   // これは「引数なし・戻り値voidの Harl のメンバ関数」を指すポインタの型
//   typedef void (Harl::*Action)();

//   // Step 2) 1行分のレコード型：キーと対応するメンバ関数ポインタ
//   struct Entry {
//     const char* key; // 例: "DEBUG"（文字列リテラル。std::string と == で比較可）
//     Action fn;       // 例: &Harl::debug（メンバ関数の“アドレス”）
//   };

//   // Step 3) 固定のディスパッチテーブル
//   // static: 最初の呼び出し時に一度だけ作られ再利用
//   // const : 誤って書き換えない
//   static const Entry table[] = {
//     {"DEBUG",   &Harl::debug},
//     {"INFO",    &Harl::info},
//     {"WARNING", &Harl::warning},
//     {"ERROR",   &Harl::error},
//   };

//   // Step 4) 一致するキーを探し、該当メソッドを this に対して呼ぶ
//   for (size_t i = 0; i < sizeof(table) / sizeof(table[0]); ++i) {
//     if (level == table[i].key) {
//       Action f = table[i].fn;   // 呼ぶべきメソッド（のポインタ）を取り出す
//       // メンバ関数ポインタの呼び出し構文：
//       //   (オブジェクトポインタ->*メンバ関数ポインタ)();
//       // ここでは this は Harl* なので ->* を使う
//       (this->*f)();
//       return;
//     }
//   }

//   // 未知レベルは何もしない
// }
