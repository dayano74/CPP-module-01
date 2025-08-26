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

## ex01
