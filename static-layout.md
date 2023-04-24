---
title: "Static-layout types"
document: D0xxxR0
date: today
audience: Language Evolution Working Group
author:
  - name: Lauri Vasama
    email: <wg21@vasama.org>
toc: false
---

# Introduction

Today the concept of a _standard-layout type_ is used a catch-all for constraining any layout related operations. However, because its primary use and the use case which restricts the set of applicable types the most is communication with foreign languages and systems, it ends up being overly restricted to fully cover certain other use cases. This paper proposes a new named superset of _standard-layout types_: _static-layout types_. A _static-layout type_ is a type which layout does not vary between different objects of the type. All commercially relevant C++ implementations today use static layouts for the majority of types, the sole exception being types employing virtual inheritance. Thus what this paper proposes is standardising the existing industry practice of static type layouts by giving it a name, and exposing it to the language user in the form of a new standard library type trait.

The `offsetof` macro is also changed to be supported for static-layout class types, and ill formed for other types.

# Proposed wording

Modify __§6.8.1.9 [basic.types.general]__

Arithmetic types ([basic.fundamental]), enumeration types, pointer types, pointer-to-member types ([basic.compound]), `std​::​nullptr_­t`, and cv-qualified versions of these types are collectively called _scalar types_. Scalar types, trivially copyable class types ([class.prop]), arrays of such types, and cv-qualified versions of these types are collectively called _trivially copyable types_. Scalar types, trivial class types ([class.prop]), arrays of such types and cv-qualified versions of these types are collectively called _trivial types_. Scalar types, standard-layout class types ([class.prop]), arrays of such types and cv-qualified versions of these types are collectively called _standard-layout types_. [Standard-layout types, static-layout class types ([class.prop]), arrays of such types and cv-qualified versions of these types are collectively called _static-layout types_.]{.add} Scalar types, implicit-lifetime class types ([class.prop]), array types, and cv-qualified versions of these types are collectively called implicit-lifetime types.

Add new subsection to __§11.2 [class.prop]__

:::add
A _static-layout class_ is a class with a single unspecified layout shared by all objects of the class. A _standard-layout class_ is a _static-layout class_.
:::

Modify __§17.2.4 [support.types.layout]__

The macro `offsetof(type, member-designator)` has the same semantics as the corresponding macro in the C standard library header `<stddef.h>`, but accepts a restricted set of _type_ arguments in this document. Use of the `offsetof` macro with a _type_ other than a [standard-layout class]{.rm} [static-layout class]{.add} ([class.prop]) is [conditionally-supported]{.rm} [ill formed]{.add}. The expression `offsetof(type, member-designator)` is never type-dependent and it is value-dependent if and only if _type_ is dependent. The result of applying the `offsetof` macro to a static data member or a function member is undefined. No operation invoked by the `offsetof` macro shall throw an exception and `noexcept(offsetof(type, member-designator))` shall be true.

Add to __§21.3.3 [meta.type.synop]__

:::add
```
namespace std {

  template<class T> struct is_static_layout;

  template<class T>
  inline constexpr bool is_static_layout_v = is_static_layout<T>::value;

}
```
:::