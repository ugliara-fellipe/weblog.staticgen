//
// Copyright (c) 2019, Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#include "site.h"

static void _alloc_(site_t *self, args_t arguments) {}

static void _free_(site_t *self) {}

static void _copy_(site_t *self, site_t *object) {}

static bool _equal_(site_t *self, site_t *object) { return true; }

def_prototype_source(site_t, _alloc_, _free_, _copy_, _equal_);

void site_test() {
  site_t *site = alloc(site_t);
  assert(type_equal(site, "site_t") == true);
  dealloc(site);
}