//
// Copyright (c) 2019, Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#include "home.h"
#include "ast.h"
#include "text.h"
#include "token.h"

static void _alloc_post_(home_post_t *self, args_t arguments) {
  self->date = alloc(text_t, "");
  self->show = alloc(text_t, "");
  self->group = alloc(text_t, "");
  self->link = alloc(text_t, "");
  self->path = alloc(text_t, "");
  self->title = alloc(text_t, "");
}

static void _free_post_(home_post_t *self) {
  dealloc(self->date);
  dealloc(self->show);
  dealloc(self->group);
  dealloc(self->link);
  dealloc(self->path);
  dealloc(self->title);
}

static void _copy_post_(home_post_t *self, home_post_t *object) {}

static bool _equal_post_(home_post_t *self, home_post_t *object) {
  return false;
}

static void _inspect_post_(home_post_t *self, inspect_t *inspect) {}

def_prototype_source(home_post_t, _alloc_post_, _free_post_, _copy_post_,
                     _equal_post_, _inspect_post_);

static void value_remove_quotes(text_t *value) {
  text_sub(value, 1, text_size(value) - 2);
}

static void group_enter(ast_item_t *rule, object_t context) {
  home_t *home = cast(home_t *, context);
  token_t *tag = ast_get_token(rule, 0);

  text_set(home->group, tag->value->value);
}

static void group_exit(ast_item_t *rule, object_t context) {
  home_t *home = cast(home_t *, context);
  token_t *tag = ast_get_token(rule, 0);

  if (text_compare(tag->value, "post")) {
    list_add(home->posts, LIST_TAIL, home->post);
    home->post = alloc(home_post_t);
  }
}

static void item_enter(ast_item_t *rule, object_t context) {
  home_t *home = cast(home_t *, context);
  token_t *tag = ast_get_token(rule, 0);
  token_t *value = ast_get_token(rule, 1);

  if (text_compare(home->group, "weblog")) {
    if (text_compare(tag->value, "title")) {
      text_set(home->weblog_title, value->value->value);
      value_remove_quotes(home->weblog_title);
    } else if (text_compare(tag->value, "description")) {
      text_set(home->weblog_description, value->value->value);
      value_remove_quotes(home->weblog_description);
    } else if (text_compare(tag->value, "keywords")) {
      text_set(home->weblog_keywords, value->value->value);
      value_remove_quotes(home->weblog_keywords);
    }
  } else if (text_compare(home->group, "license")) {
    if (text_compare(tag->value, "holder")) {
      text_set(home->license_holder, value->value->value);
      value_remove_quotes(home->license_holder);
    } else if (text_compare(tag->value, "link")) {
      text_set(home->license_link, value->value->value);
      value_remove_quotes(home->license_link);
    } else if (text_compare(tag->value, "type")) {
      text_set(home->license_type, value->value->value);
      value_remove_quotes(home->license_type);
    } else if (text_compare(tag->value, "file")) {
      text_set(home->license_file, value->value->value);
      value_remove_quotes(home->license_file);
    } else if (text_compare(tag->value, "date")) {
      text_set(home->license_date, value->value->value);
      value_remove_quotes(home->license_date);
    }
  } else if (text_compare(home->group, "post")) {
    if (text_compare(tag->value, "date")) {
      text_set(home->post->date, value->value->value);
      value_remove_quotes(home->post->date);
    } else if (text_compare(tag->value, "show")) {
      text_set(home->post->show, value->value->value);
      value_remove_quotes(home->post->show);
    } else if (text_compare(tag->value, "group")) {
      text_set(home->post->group, value->value->value);
      value_remove_quotes(home->post->group);
    } else if (text_compare(tag->value, "link")) {
      text_set(home->post->link, value->value->value);
      value_remove_quotes(home->post->link);
    } else if (text_compare(tag->value, "path")) {
      text_set(home->post->path, value->value->value);
      value_remove_quotes(home->post->path);
    } else if (text_compare(tag->value, "title")) {
      text_set(home->post->title, value->value->value);
      value_remove_quotes(home->post->title);
    }
  }
}

static void _alloc_(home_t *self, args_t arguments) {
  self->recognizer = alloc(recognizer_t);

  scanner_t *scanner = self->recognizer->scanner;
  scanner_add_model(scanner, ":Comment",
                    "^##(#N|#A|,|:|#.|/| |#(|#)|-|'|\")*\r?\n");
  scanner_add_model(scanner, "Tag", "^#A*");
  scanner_add_model(scanner, "Value", "^\"(#N|#A|,|:|#.|/| |-|')*\"");
  scanner_add_model(scanner, ":Ignore", "^( |\r?\n)");

  grammar_t *grammar = self->recognizer->parser->grammar;
  grammar_rule(grammar, "init", "group :init | group Eot");
  grammar_rule(grammar, "group", "Tag list");
  grammar_rule(grammar, "list", "item :list | item");
  grammar_rule(grammar, "item", "Tag Value");

  grammar_begin(grammar, "init");

  self->generator = alloc(walker_t);
  self->generator->context = self;
  walker_listener(self->generator, "group", group_enter, group_exit);
  walker_listener(self->generator, "item", item_enter, NULL);

  self->path = alloc(text_t, "");

  self->group = alloc(text_t, "");
  self->post = alloc(home_post_t);

  self->weblog_title = alloc(text_t, "");
  self->weblog_description = alloc(text_t, "");
  self->weblog_keywords = alloc(text_t, "");

  self->license_holder = alloc(text_t, "");
  self->license_link = alloc(text_t, "");
  self->license_type = alloc(text_t, "");
  self->license_file = alloc(text_t, "");
  self->license_date = alloc(text_t, "");

  self->posts = alloc(list_t);

  self->page = alloc(text_t, "");
}

static void _free_(home_t *self) {
  dealloc(self->recognizer);
  dealloc(self->generator);

  dealloc(self->path);

  dealloc(self->group);
  dealloc(self->post);

  dealloc(self->weblog_title);
  dealloc(self->weblog_description);
  dealloc(self->weblog_keywords);

  dealloc(self->license_holder);
  dealloc(self->license_link);
  dealloc(self->license_type);
  dealloc(self->license_file);
  dealloc(self->license_date);

  dealloc(self->posts);

  dealloc(self->page);
}

static void _copy_(home_t *self, home_t *object) {}

static bool _equal_(home_t *self, home_t *object) { return false; }

static void _inspect_(home_t *self, inspect_t *inspect) {}

def_prototype_source(home_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

static void home_page_generate(home_t *self) {
  text_from_file(self->page, "template/home.html");
  text_replace(self->page, "$date", self->license_date->value);
  text_replace(self->page, "$holder", self->license_holder->value);
  text_replace(self->page, "$type", self->license_type->value);
  text_replace(self->page, "$file", self->license_file->value);
  text_replace(self->page, "$link", self->license_link->value);
  text_replace(self->page, "$title", self->weblog_title->value);
  text_replace(self->page, "$description", self->weblog_description->value);
  text_replace(self->page, "$keywords", self->weblog_keywords->value);

  text_t *posts = alloc(text_t, "");
  text_t *post_template = alloc(text_t, "");
  list_for(self->posts, index, home_post_t, post, {
    text_set(post_template,
             "  <article class=\"postcard\">\n"
             "    <div class=\"info\">\n"
             "      <time datetime=\"$date\">$show</time> # $group\n"
             "    </div>\n"
             "    <a href=\"$link\"$tab>$title</a>\n"
             "  </article>\n\n");
    text_replace(post_template, "$date", post->date->value);
    text_replace(post_template, "$show", post->show->value);
    text_replace(post_template, "$group", post->group->value);
    if (!text_compare(post->link, "")) {
      text_replace(post_template, "$link", post->link->value);
      text_replace(post_template, "$tab", "");
    } else {
      text_replace(post_template, "$link", post->path->value);
      text_replace(post_template, "$tab", " target=\"_blank\"");
    }
    text_replace(post_template, "$title", post->title->value);
    text_append(posts, post_template->value);
  });
  dealloc(post_template);
  if (self->posts->size > 0) {
    text_sub(posts, 2, text_size(posts) - 4);
  }
  text_replace(self->page, "$posts", posts->value);
  dealloc(posts);
}

void home_compile(home_t *self, const char *home_path) {
  text_set(self->path, home_path);
  text_t *in = alloc(text_t, home_path);
  text_append(in, "/home.blog");
  text_t *file = alloc(text_t, "");
  text_from_file(file, in->value);
  printf("Home Page %s\n", in->value);
  dealloc(in);
  if (recognizer_perform(self->recognizer, file->value)) {
    walker_perform(self->generator, self->recognizer->parser->ast);
    home_page_generate(self);
    text_t *out = alloc(text_t, home_path);
    text_append(out, "/index.html");
    text_to_file(self->page, out->value);
    dealloc(out);
    printf("Success\n\n");
  } else {
    printf("Failure\n\n");
  }
  dealloc(file);
}

void home_test() {
  home_t *home = alloc(home_t);
  assert(type_equal(home, "home_t") == true);
  dealloc(home);
}
