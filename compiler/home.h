//
// Copyright (c) 2020, Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#ifndef HOME_H
#define HOME_H

#include "list.h"
#include "prototype.h"
#include "recognizer.h"
#include "walker.h"

typedef struct {
  text_t *date;
  text_t *show;
  text_t *group;
  text_t *link;
  text_t *path;
  text_t *title;
} home_post_t;

def_prototype_header(home_post_t);

typedef struct {
  recognizer_t *recognizer;
  walker_t *generator;

  text_t *path;

  text_t *group;
  home_post_t *post;

  text_t *weblog_title;
  text_t *weblog_description;
  text_t *weblog_keywords;

  text_t *license_holder;
  text_t *license_link;
  text_t *license_type;
  text_t *license_file;
  text_t *license_date;

  list_t *posts;

  text_t *page;
} home_t;

def_prototype_header(home_t);

void home_compile(home_t *self, const char *home_path);

void home_test();

#endif
