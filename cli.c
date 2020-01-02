//
// Copyright (c) 2019, Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#include "home.h"
#include "post.h"
#include "prototype.h"

int main() {
  home_t *home = alloc(home_t);
  post_t *post = alloc(post_t);

  home_compile(home, "../weblog.pages");
  list_for(home->posts, index, home_post_t, item,
           { post_compile(post, home, item); });

  dealloc(post);
  dealloc(home);
  // command line interface (CLI)
}