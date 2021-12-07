---
title: "Explicit implicit_cast"
document: D0xxxR0
date: today
audience: Library Evolution Group
author:
  - name: Lauri Vasama
    email: <lauri@vasama.org>
toc: true
---

# Introduction

# Motivation

* Passing references or pointers to base class. In this case a `static_cast` is too powerful as it can perform a down-cast as well as an up-cast.
  ```
  void f(auto& object);
  f(implicit_cast<base&>(derived));
  ```
* 

# Proposed wording

## Synopsis

```cpp
namespace std {
  template<typename To, typename From>
  constexpr To implicit_cast(From&& from);
}
```


```cpp
namespace std {

  template<typename _To>
  void __implicitly_convertible_function(_To) noexcept;

  template<typename _From, typename _To>
  concept __implicitly_convertible = requires(_From&& __from) {
    __implicitly_convertible_function<_To>(static_cast<_From&&>(__from));
  };

  template<typename _To, __implicitly_convertible<_To> _From>
  constexpr _To implicit_cast(_From&& __from) noexcept(noexcept(__implicitly_convertible_function<_To>(static_cast<_From&&>(__from))))
  {
    return static_cast<_From&&>(__from);
  }

}
```
