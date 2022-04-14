---
title: "Accessing data member offsets"
document: D0xxxR0
date: today
audience: Library Evolution Group
author:
  - name: Lauri Vasama
    email: <wg21@vasama.org>
toc: true
---

# Introduction

Today the concept of a standard layout type is used a catch-all for constraining any layout related operations. However, because its primary use and the use case which restricts the set of applicable types the most is communication with foreign languages and systems, it ends up being overly restricted to fully cover certain other use cases. This paper proposes a new named superset of standard layout types: static layout types. A static layout type is a type which layout does not vary between different objects of the type. All commercially relevant C++ implementations today use static layouts for the majority of types, the sole exception being types employing virtual inheritance. Thus what this paper proposes is standardising the existing industry practice of static type layouts by giving it a name, and exposing it to the language user in the form of a new standard library type trait.

# Proposed wording

```
namespace std {

  template<typename T>
  struct is_static_layout
  {
    static constexpr bool value = /* implementation defined */ ;
  };

  template<typename T>
  inline constexpr bool is_static_layout_v = is_static_layout<T>::value;

}
```

:::add

Add to section 11.2 Properties of classes [class.prop]

A _static-layout class_ is a class with a single layout applicable to all objects of the class. A _standard-layout class_ is a _static-layout class_.

:::

Modify section 17.2.4 Sizes, alignments, and offsets [support.types.layout]:

The macro offsetof(type, member-designator) has the same semantics as the corresponding macro in the C standard library header <stddef.h>, but accepts a restricted set of type arguments in this document. Use of the offsetof macro with a type other than a [standard-layout class]{.rm} [static-layout class]{.add} ([class.prop]) is conditionally-supported.173 The expression offsetof(type, member-designator) is never type-dependent and it is value-dependent if and only if type is dependent. The result of applying the offsetof macro to a static data member or a function member is undefined. No operation invoked by the offsetof macro shall throw an exception and noexcept(offsetof(type, member-designator)) shall be true.

