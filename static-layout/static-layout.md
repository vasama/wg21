---
title: "Accessing data member offsets"
document: D0xxxR0
date: today
audience: Library Evolution Group
author:
  - name: Lauri Vasama
    email: <lauri@vasama.org>
toc: true
---

# Introduction

Today the concept of a standard layout type is used a catch-all for constraining any layout related operations. However, because its primary use and the use case which restricts the set of applicable types the most is communication with foreign languages and systems, it ends up being overly restricted to folly cover certain other use cases. This paper proposes a new named superset of standard layout types: static layout types. A static layout type is a type which layout does not vary between different objects of the type. All commercially relevant C++ implementations today use static layouts for the majority of types, the sole exception being types employing virtual inheritance. Thus what this paper proposes is standardising the existing industry practice of static type layouts by giving it a name, and exposing it to the language user in the form of a new standard library type trait.

# Proposed changes

```
namespace std {

  template<typename T>
  struct is_static_layout
  {
    static constexpr bool value = /* implementation defined */
  };

  template<typename T>
  static constexpr bool is_static_layout_v = is_static_layout<T>::value;

}
```
