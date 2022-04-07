---
title: "Required attribute syntax"
document: D0xxxR0
date: today
audience: Language Evolution Group
author:
  - name: Lauri Vasama
    email: <lauri@vasama.org>
toc: true
---

# Introduction

Attributes as introduced in C++11 are specified to be ignored if not recognised by the implementation. This makes their use difficult for any new feature that seeks to change the behaviour of the program in observable ways. This problem can be seen with the `no_unique_address` attribute introduced in C++20. Because it affects the layout of types and as such their ABI, Microsoft has been especially hesitant to implement it, and has instead chosen to provide the `msvc::no_unique_address` attribute. It may be argued that this functionality should not have been provided through an ignorable attribute. The alternative solution employed since the inception of attributes, for `consteval` and `constinit` in C++20, is the introduction of new keywords. This is well known to be contentious due to potential conflicts with existing code.

To remedy these issues going forward, this paper proposes an extension to the C++11 attribute syntax: required attributes. A required attribute is denoted by an exclamation mark (`!`) preceding the name of the attribute. If a required attribute is not recognised by the implementation, the program is ill formed. It does not change or mandate any behaviour of the attribute, only ensuring that the attribute is recognised by the implementation. The required attribute syntax may be applied to any attribute including any existing standard or implementation defined attributes. Future attributes may be required to be used as required attributes if they seek to change the behaviour of the program. The use of certain existing attributes such as `no_unique_address` as non-required attributes may also be deprecated.

http://eel.is/c++draft/dcl.attr#grammar-6

# Proposed wording

For an _attribute-token_ (including an _attribute-scoped-token_) not specified in this document, the behavior is implementation-defined. Any _attribute-token_ that is not recognized by the implementation is ignored, unless it is a _required attribute_, in which case the behaviour of the program is ill formed.

> | _attribute:_
:::rm
> |     attribute-token attribute-argument-clause~opt~_
:::
:::add
> |     !_~opt~ attribute-token attribute-argument-clause~opt~_
:::
