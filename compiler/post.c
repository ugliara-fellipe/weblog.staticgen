//
// Copyright (c) 2019, Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#include "post.h"

static void _alloc_(post_t *self, args_t arguments) {
  self->recognizer = alloc(recognizer_t);
  /*
  scanner_t *scanner = self->recognizer->scanner;
  scanner_add_model(scanner, ":Comment", "^##(#N|#A|,|:|#.|/| |#(|#)|-)*\r?\n");
  scanner_add_model(scanner, "Tag", "^#A*");
  scanner_add_model(scanner, "Value", "^\"(#N|#A|,|:|#.|/| |-)*\"");
  scanner_add_model(scanner, ":Ignore", "^( |\r?\n)");

  grammar_t *grammar = self->recognizer->parser->grammar;
  grammar_rule(grammar, "init", "group :init | group Eot");
  grammar_rule(grammar, "group", "Tag list");
  grammar_rule(grammar, "list", "item :list | item");
  grammar_rule(grammar, "item", "Tag Value");

  grammar_begin(grammar, "init");
  */

  self->generator = alloc(walker_t);
  /*
  self->generator->context = self;
  walker_listener(self->generator, "group", group_enter, group_exit);
  walker_listener(self->generator, "item", item_enter, NULL);
  */

  self->page = alloc(text_t, "");
}

static void _free_(post_t *self) {
  dealloc(self->recognizer);
  dealloc(self->generator);

  dealloc(self->page);
}

static void _copy_(post_t *self, post_t *object) {}

static bool _equal_(post_t *self, post_t *object) { return true; }

def_prototype_source(post_t, _alloc_, _free_, _copy_, _equal_);

static void post_page_generate(post_t *self) {}

void post_compile(post_t *self, home_t *home, home_post_t *home_post) {
  text_t *out = copy(home->path);
  text_append(out, "/");
  text_append(out, home_post->link->value);
  text_t *in = copy(out);
  text_replace(in, ".html", ".post");
  text_t *file = alloc(text_t, "");
  text_from_file(file, in->value);
  dealloc(in);
  // recognizer_perform(self->recognizer, file->value);
  // walker_perform(self->generator, self->recognizer->parser->ast);
  post_page_generate(self);
  text_to_file(self->page, out->value);
  dealloc(out);
  dealloc(file);
}

void post_test() {
  post_t *post = alloc(post_t);
  assert(type_equal(post, "post_t") == true);
  dealloc(post);
}