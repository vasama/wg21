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
