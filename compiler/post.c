//
// Copyright (c) 2019, Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#include "post.h"

static void _alloc_(post_t *self, args_t arguments) {}

static void _free_(post_t *self) {}

static void _copy_(post_t *self, post_t *object) {}

static bool _equal_(post_t *self, post_t *object) { return true; }

def_prototype_source(post_t, _alloc_, _free_, _copy_, _equal_);

void post_test() {
  post_t *post = alloc(post_t);
  assert(type_equal(post, "post_t") == true);
  dealloc(post);
}