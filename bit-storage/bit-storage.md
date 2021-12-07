---
title: "Narrowing and widening bit_cast"
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

It is sometimes desirable to temporarily store an object within the storage of an object of different type. A particularly good example is passing trivially copyable types by value in a `void*` commonly used in passing context to callbacks, be it directly or encapsulated within a `function_view` class. This can be achieved in some cases using `std::bit_cast` and `std::memcpy` in others. Both approaches have their limitations however: `std::memcpy` is not `constexpr` and applying it to non trivially constructible types requires some gymnastics, while `std::bit_cast` requires that both input and output be of the same size.

# Proposed wording

## Library additions

> ```diff
> + template<typename To, typename From>
> + requires
> +   sizeof(To) >= sizeof(From) &&
> +   is_trivially_copyable_v<To> &&
> +   is_trivially_copyable_v<From>
> + constexpr To bit_cast_widening(const From& from) noexcept;
> ```
> ::: add
>> _Requires_: `sizeof(To) >= sizeof(From)`, `is_trivially_copyable_v<To>` is `true`, `is_trivially_copyable_v<From>` is `true`.
>> _Returns_: an object of type `To` whose value is unspecified.

> ```diff
> + template<typename To, typename From>
> + requires
> +   sizeof(To) <= sizeof(From) &&
> +   is_trivially_copyable_v<To> &&
> +   is_trivially_copyable_v<From>
> + constexpr To bit_cast_narrowing(const From& from) noexcept;
> ```
> ::: add
>> _Requires_: `sizeof(To) >= sizeof(From)`, `is_trivially_copyable_v<To>` is `true`, `is_trivially_copyable_v<From>` is `true`.
>> _Returns_: an object of type `To` whose value is unspecified, except if the value of `from` is the result of an invocation of `bit_cast_widening<From, To>` in which case the returned value is equal to the value passed to `bit_cast_widening<From, To>`.
