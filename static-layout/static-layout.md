---
title: "Static-layout types"
document: D0xxxR0
date: today
audience: Library Evolution Group
author:
  - name: Lauri Vasama
    email: <wg21@vasama.org>
toc: true
---

# Introduction


The `offsetof` macro is also changed to be unconditionally-supported for static-layout class types, and ill formed for other types.

# Proposed wording

## Add to section 21.3.3 Header `<type_traits>` Synopsis `[meta.type.synop]`

```
namespace std {

:::add
  template<class T> struct is_static_layout;

  template<class T>
  inline constexpr bool is_static_layout_v = is_static_layout<T>::value;
:::

}
```

:::add

Add to section 11.2 Properties of classes [class.prop]

A _static-layout class_ is a class with a single layout applicable to all objects of the class. A _standard-layout class_ is a _static-layout class_.

:::

## Modify section 17.2.4 Sizes, alignments, and offsets `[support.types.layout]`

The macro `offsetof(type, member-designator)` has the same semantics as the corresponding macro in the C standard library header `<stddef.h>`, but accepts a restricted set of _type_ arguments in this document. Use of the `offsetof` macro with a _type_ other than a [standard-layout class]{.rm} [static-layout class]{.add} ([class.prop]) is ill formed. The expression `offsetof(type, member-designator)` is never type-dependent and it is value-dependent if and only if _type_ is dependent. The result of applying the `offsetof` macro to a static data member or a function member is undefined. No operation invoked by the `offsetof` macro shall throw an exception and `noexcept(offsetof(type, member-designator))` shall be true.

