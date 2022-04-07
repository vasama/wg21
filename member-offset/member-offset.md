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



# Motivation



[Boost.Intrusive](https://github.com/boostorg/intrusive/blob/boost-1.74.0/include/boost/intrusive/detail/parent_from_member.hpp)


# Proposed changes

## Synopsis

```cpp
namespace std {

  template<typename C, typename M>
    requires is_standard_layout_v<C>
  constexpr C& object_from_member(M& member, M(C::* ptr)) noexcept;

  template<typename C, typename M>
    requires is_standard_layout_v<C>
  constexpr const C& object_from_member(const M& member, M(C::* ptr)) noexcept;

  template<typename C, typename M>
    requires is_standard_layout_v<C>
  constexpr size_t member_offset(M(C::* ptr)) noexcept;

}
```

## Changes

> ```diff
> + template<typename C, typename M>
> +   requires is_standard_layout_v<C>
> + constexpr C& object_from_member(M& member, M(C::* ptr)) noexcept;
> +
> + template<typename C, typename M>
> +   requires is_standard_layout_v<C>
> + constexpr const C& object_from_member(const M& member, M(C::* ptr)) noexcept;
> ```
> ::: add
>> _Requires_: `ptr` shall not be `nullptr`. `member` shall refer to the member pointed to by `ptr` of an instance of `C`.
>> _Returns_: reference to the instance of `C` of which `member` is a member.
> :::

> ```diff
> + template<typename C, typename M>
> +   requires is_standard_layout_v<C>
> + constexpr size_t member_offset(M(C::* ptr)) noexcept;
> ```
> ::: add
>> _Requires_: `ptr` shall not be `nullptr`.
>> _Returns_: the offset of the data member pointed to by `ptr`.
> :::
