---
title: "Strict aliasing 8-bit types"
document: D0xxxR0
date: today
audience: Library Evolution Group
author:
  - name: Lauri Vasama
    email: <lauri@vasama.org>
toc: true
---

```cpp
namespace std {
  using int8_strict_t  = signed integer type;   // optional
  using uint8_strict_t = unsigned integer type; // optional
}
```
