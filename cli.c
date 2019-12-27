//
// Copyright (c) 2019, Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#include "home.h"
#include "prototype.h"

int main() {
  home_t *home = alloc(home_t);

  home_compile(home, "../weblog.pages/home.blog", "out/index.html");

  dealloc(home);
  // command line interface (CLI)
}