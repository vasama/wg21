---
title: "Required attribute syntax"
document: D0xxxR0
date: today
audience: Language Evolution Group
author:
  - name: Lauri Vasama
    email: <wg21@vasama.org>
toc: true
---

# Introduction

Attributes as introduced in C++11 are permitted to be ignored if not recognised by the implementation. This makes their use difficult for any new feature that seeks to change the behaviour of the program in observable ways. This problem can be seen with the `no_unique_address` attribute introduced in C++20. Because it affects the layout of types and as such their ABI, Microsoft has been especially hesitant to implement it and has instead chosen to provide the `msvc::no_unique_address` attribute. It may be argued that this functionality should not have been provided through an ignorable attribute. The alternative solution employed since the inception of attributes, for `consteval` and `constinit` in C++20, is the introduction of new keywords. This is well known to be contentious due to potential conflicts with existing code.

# Proposal

To remedy these issues going forward, this paper proposes an extension to the C++11 attribute syntax: required attributes. A required attribute is denoted by an exclamation mark (`!`) (syntax subject to change based on feedback) preceding the name of the attribute. If a required attribute is not recognised by the implementation, the program is ill formed. A required attribute does not affect the behaviour of the attribute, only ensuring that the attribute is recognised by the implementation. It is however recommended that implementations not recognise attributes unless they also implement them in a way that matches user expectations. The required attribute syntax may be applied to any attribute including any existing standard or implementation defined attributes. For any future standard attributes seeking to affect the behaviour of the program, the use of required attribute syntax should be mandated. The non-required forms of any existing standard attributes with effects on program behaviour, such as `no_unique_address`, should also be deprecated (no wording yet).

http://eel.is/c++draft/dcl.attr#grammar-6

# Proposed wording

Modify §9.12.1.1 as follows:

> | _attribute:_
> :::rm
> |     _attribute-token attribute-argument-clause~opt~_
> :::
> :::add
> |     !_~opt~ attribute-token attribute-argument-clause~opt~_
> :::

Modify §9.12.1.6 as follows:

For an _attribute-token_ (including an _attribute-scoped-token_) not specified in this document, the behavior is implementation-defined. Any _attribute-token_ that is not recognized by the implementation is ignored[, unless it is a _required attribute_, in which case the program is ill formed]{.add}.
