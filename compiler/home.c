//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#include "compiler/home.h"
#include "language.h"
#include "toolbelt.h"

static void _alloc_card_(home_card_t *self, args_t arguments) {
  self->type = alloc(text_t, "");
  self->size = alloc(text_t, "");
  self->date = alloc(text_t, "");
  self->show = alloc(text_t, "");
  self->group = alloc(text_t, "");
  self->link = alloc(text_t, "");
  self->path = alloc(text_t, "");
  self->title = alloc(text_t, "");
  self->text = alloc(text_t, "");
}

static void _free_card_(home_card_t *self) {
  dealloc(self->type);
  dealloc(self->size);
  dealloc(self->date);
  dealloc(self->show);
  dealloc(self->group);
  dealloc(self->link);
  dealloc(self->path);
  dealloc(self->title);
  dealloc(self->text);
}

static void _copy_card_(home_card_t *self, home_card_t *object) {}

static bool _equal_card_(home_card_t *self, home_card_t *object) {
  return false;
}

static void _inspect_card_(home_card_t *self, inspect_t *inspect) {}

def_prototype_source(home_card_t, _alloc_card_, _free_card_, _copy_card_,
                     _equal_card_, _inspect_card_);

static void group_enter(ast_item_t *rule, object_t context) {
  home_t *home = cast(home_t *, context);
  token_t *tag = ast_get_token(rule, 0);
  text_trim(tag->value);

  text_set(home->group, tag->value->value);
  text_set(home->card->type, tag->value->value);
}

static void group_exit(ast_item_t *rule, object_t context) {
  home_t *home = cast(home_t *, context);
  token_t *tag = ast_get_token(rule, 0);

  if (text_compare(tag->value, "post") || text_compare(tag->value, "note") ||
      text_compare(tag->value, "offsite")) {
    list_add(home->cards, LIST_TAIL, home->card);
    home->card = alloc(home_card_t);
  }
}

static void item_enter(ast_item_t *rule, object_t context) {
  home_t *home = cast(home_t *, context);

  text_set(home->value, "");
}

static void linebreak_enter(ast_item_t *rule, object_t context) {
  home_t *home = cast(home_t *, context);

  text_append(home->value, "<br>");
}

static void text_enter(ast_item_t *rule, object_t context) {
  home_t *home = cast(home_t *, context);
  token_t *text = ast_get_token(rule, 0);

  text_append(home->value, text->value->value);
}

static void replace_text_special_char(text_t *text) {
  text_replace(text, "\\\\", "\\");
  text_replace(text, "\\+", "+");
  text_replace(text, "\\*", "*");
  text_replace(text, "\\^", "^");
  text_replace(text, "\\[", "[");
  text_replace(text, "\\]", "]");
  text_replace(text, "\\#", "#");
  text_replace(text, "\\{", "{");
  text_replace(text, "\\}", "}");
}

static void link_enter(ast_item_t *rule, object_t context) {
  home_t *home = cast(home_t *, context);
  token_t *name = ast_get_token(rule, 1);
  token_t *type = ast_get_token(rule, 2);
  token_t *link = ast_get_token(rule, 3);

  text_t *temp = copy(name->value);
  replace_text_special_char(temp);

  text_append(home->value, "<strong><a href=\"");
  text_append(home->value, link->value->value);
  if (text_compare(type->value, "+")) {
    text_append(home->value, "\" target=\"_blank\">");
  } else {
    text_append(home->value, "\">");
  }
  text_append(home->value, temp->value);
  text_append(home->value, "</a></strong>");

  dealloc(temp);
}

static void item_exit(ast_item_t *rule, object_t context) {
  home_t *home = cast(home_t *, context);
  token_t *tag = ast_get_token(rule, 0);
  text_trim(tag->value);

  if (text_compare(home->group, "weblog")) {
    if (text_compare(tag->value, "title")) {
      text_set(home->weblog_title, home->value->value);
    } else if (text_compare(tag->value, "brief")) {
      text_set(home->weblog_brief, home->value->value);
    } else if (text_compare(tag->value, "tags")) {
      text_set(home->weblog_tags, home->value->value);
    }
  } else if (text_compare(home->group, "copyright")) {
    if (text_compare(tag->value, "owner")) {
      text_set(home->copyright_owner, home->value->value);
    } else if (text_compare(tag->value, "year")) {
      text_set(home->copyright_year, home->value->value);
    }
  } else if (text_compare(home->group, "license")) {
    if (text_compare(tag->value, "link")) {
      text_set(home->license_link, home->value->value);
    } else if (text_compare(tag->value, "type")) {
      text_set(home->license_type, home->value->value);
    } else if (text_compare(tag->value, "file")) {
      text_set(home->license_file, home->value->value);
    }
  } else if (text_compare(home->group, "content")) {
    if (text_compare(tag->value, "link")) {
      text_set(home->content_link, home->value->value);
    } else if (text_compare(tag->value, "site")) {
      text_set(home->content_site, home->value->value);
    } else if (text_compare(tag->value, "type")) {
      text_set(home->content_type, home->value->value);
    } else if (text_compare(tag->value, "name")) {
      text_set(home->content_name, home->value->value);
    } else if (text_compare(tag->value, "file")) {
      text_set(home->content_file, home->value->value);
    }
  } else if (text_compare(home->group, "post") ||
             text_compare(home->group, "note") ||
             text_compare(home->group, "offsite")) {
    if (text_compare(tag->value, "date")) {
      text_set(home->card->date, home->value->value);
    } else if (text_compare(tag->value, "show")) {
      text_set(home->card->show, home->value->value);
    } else if (text_compare(tag->value, "group")) {
      text_set(home->card->group, home->value->value);
    } else if (text_compare(tag->value, "link")) {
      text_set(home->card->link, home->value->value);
    } else if (text_compare(tag->value, "path")) {
      text_set(home->card->path, home->value->value);
    } else if (text_compare(tag->value, "title")) {
      text_set(home->card->title, home->value->value);
    } else if (text_compare(tag->value, "size")) {
      text_set(home->card->size, home->value->value);
    } else if (text_compare(tag->value, "text")) {
      text_set(home->card->text, home->value->value);
    }
  }
}

static void _alloc_(home_t *self, args_t arguments) {
  self->recognizer = alloc(recognizer_t);

  scanner_t *scanner = self->recognizer->scanner;
  scanner_add_model(scanner, ":Comment",
                    "^##(#N|#A|,|:|#.|/| |#(|#)|-|'|\")*\r?\n");
  scanner_add_model(scanner, ":Ignore", "^( |\r?\n)+");
  scanner_add_model(
      scanner, "Text",
      "^( |!|\"|#$|%|~|&|'|#(|#)|,|-|#.|/"
      "|#N|:|;|<|=|>|#?|@|#A|_|`|\\(\\|#+|#*|#^|[|]|##|{|})|#|)+");
  scanner_add_model(scanner, "Star", "^#*");
  scanner_add_model(scanner, "Plus", "^#+");
  scanner_add_model(scanner, "ValueOpen", "^[ ?");
  scanner_add_model(scanner, "ValueClose", "^ ?]");
  scanner_add_model(scanner, "LinkOpen", "^{ ?");
  scanner_add_model(scanner, "LinkClose", "^ ?}");
  scanner_add_model(scanner, "LineBreak", "^#^");

  grammar_t *grammar = self->recognizer->parser->grammar;
  grammar_rule(grammar, "init", "group :init | group Eot");
  grammar_rule(grammar, "group", "Text list");
  grammar_rule(grammar, "list", "item :list | item");
  grammar_rule(grammar, "item", "Text valuelist");
  grammar_rule(grammar, "valuelist", "value :valuelist | value");
  grammar_rule(grammar, "value", "ValueOpen part ValueClose");
  grammar_rule(grammar, "part", "block :part | block");
  grammar_rule(grammar, "block", "text | link | linebreak");
  grammar_rule(grammar, "link",
               "LinkOpen Text Star Text LinkClose | LinkOpen Text Plus Text "
               "LinkClose");
  grammar_rule(grammar, "linebreak", "LineBreak");
  grammar_rule(grammar, "text", "Text");

  grammar_begin(grammar, "init");

  self->generator = alloc(walker_t);
  self->generator->context = self;
  walker_listener(self->generator, "group", group_enter, group_exit);
  walker_listener(self->generator, "item", item_enter, item_exit);
  walker_listener(self->generator, "link", link_enter, NULL);
  walker_listener(self->generator, "linebreak", linebreak_enter, NULL);
  walker_listener(self->generator, "text", text_enter, NULL);

  self->path = alloc(text_t, "");

  self->group = alloc(text_t, "");
  self->card = alloc(home_card_t);
  self->value = alloc(text_t, "");

  self->weblog_title = alloc(text_t, "");
  self->weblog_brief = alloc(text_t, "");
  self->weblog_tags = alloc(text_t, "");

  self->copyright_owner = alloc(text_t, "");
  self->copyright_year = alloc(text_t, "");

  self->license_link = alloc(text_t, "");
  self->license_type = alloc(text_t, "");
  self->license_file = alloc(text_t, "");

  self->content_file = alloc(text_t, "");
  self->content_link = alloc(text_t, "");
  self->content_name = alloc(text_t, "");
  self->content_site = alloc(text_t, "");
  self->content_type = alloc(text_t, "");

  self->cards = alloc(list_t);

  self->page = alloc(text_t, "");
}

static void _free_(home_t *self) {
  dealloc(self->recognizer);
  dealloc(self->generator);

  dealloc(self->path);

  dealloc(self->group);
  dealloc(self->card);
  dealloc(self->value);

  dealloc(self->weblog_title);
  dealloc(self->weblog_brief);
  dealloc(self->weblog_tags);

  dealloc(self->copyright_owner);
  dealloc(self->copyright_year);

  dealloc(self->license_link);
  dealloc(self->license_type);
  dealloc(self->license_file);

  dealloc(self->content_file);
  dealloc(self->content_link);
  dealloc(self->content_name);
  dealloc(self->content_site);
  dealloc(self->content_type);

  dealloc(self->cards);

  dealloc(self->page);
}

static void _copy_(home_t *self, home_t *object) {}

static bool _equal_(home_t *self, home_t *object) { return false; }

static void _inspect_(home_t *self, inspect_t *inspect) {}

def_prototype_source(home_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

static void home_page_generate(home_t *self) {
  text_from_file(self->page, "template/home.html");
  text_replace(self->page, "$year", self->copyright_year->value);
  text_replace(self->page, "$owner", self->copyright_owner->value);
  text_replace(self->page, "$type", self->license_type->value);
  text_replace(self->page, "$file", self->license_file->value);
  text_replace(self->page, "$link", self->license_link->value);
  text_replace(self->page, "$title", self->weblog_title->value);
  text_replace(self->page, "$brief", self->weblog_brief->value);
  text_replace(self->page, "$tags", self->weblog_tags->value);
  text_replace(self->page, "$content_name", self->content_name->value);
  text_replace(self->page, "$content_site", self->content_site->value);
  text_replace(self->page, "$content_file", self->content_file->value);
  text_replace(self->page, "$content_link", self->content_link->value);
  text_replace(self->page, "$content_type", self->content_type->value);

  text_t *cards = alloc(text_t, "");
  text_t *card_template = alloc(text_t, "");
  list_for(self->cards, index, home_card_t, card, {
    text_set(card_template, "  <div class=\"$type-card size-$size\">\n"
                            "    <div class=\"content $info $textonly\">\n"
                            "$tag"
                            "$title"
                            "$text"
                            "$endtext"
                            "    </div>\n"
                            "  </div>\n\n");
    text_replace(card_template, "$type", card->type->value);
    text_replace(card_template, "$size", card->size->value);

    if (text_compare(card->type, "post")) {
      text_replace(card_template, "$info", "info");
      text_replace(card_template, "$textonly", "");
      text_replace(card_template, "$tag",
                   "      <div class=\"time\"><time "
                   "datetime=\"$dateshort\">$datelong</time></div>\n      <div "
                   "class=\"tag\">$tag</div>\n");
      text_replace(card_template, "$dateshort", card->date->value);
      text_replace(card_template, "$datelong", card->show->value);
      text_replace(card_template, "$tag", card->group->value);
      text_replace(card_template, "$title",
                   "      <div class=\"text\">\n$title");

      if (text_compare(card->path, "")) {
        text_replace(card_template, "$title", "        <h1>$title</h1>\n");
        text_replace(card_template, "$title", card->title->value);
      } else {
        text_replace(card_template, "$title",
                     "        <a href=\"$path\">$title</a>\n");
        text_replace(card_template, "$title", card->title->value);
        text_replace(card_template, "$path", card->path->value);
      }

      if (text_compare(card->text, "")) {
        text_replace(card_template, "$text", "");
      } else {
        text_replace(card_template, "$text", "        <p>$text</p>\n");
        text_replace(card_template, "$text", card->text->value);
      }
      text_replace(card_template, "$endtext", "      </div>\n");
    } else if (text_compare(card->type, "note")) {
      text_replace(card_template, "$info", "");
      text_replace(card_template, "$tag", "");
      if (text_compare(card->title, "")) {
        text_replace(card_template, "$textonly", "text-only");
        text_replace(card_template, "$title", "");
      } else {
        text_replace(card_template, "$textonly", "");
        text_replace(card_template, "$title", "      <h1>$title</h1>\n");
        text_replace(card_template, "$title", card->title->value);
      }
      text_replace(card_template, "$text", "      <p>$text</p>\n");
      text_replace(card_template, "$text", card->text->value);
      text_replace(card_template, "$endtext", "");
    } else if (text_compare(card->type, "offsite")) {
      text_replace(card_template, "$info", "info");
      text_replace(card_template, "$textonly", "");
      text_replace(card_template, "$tag",
                   "      <div class=\"time\"><time "
                   "datetime=\"$dateshort\">$datelong</time></div>\n      "
                   "<div class=\"tag\">$tag</div>\n");
      text_replace(card_template, "$dateshort", card->date->value);
      text_replace(card_template, "$datelong", card->show->value);
      text_replace(card_template, "$tag", card->group->value);

      text_replace(card_template, "$title",
                   "      <div class=\"text\">\n$title");
      if (text_compare(card->link, "")) {
        text_replace(card_template, "$title", "        <h1>$title</h1>\n");
        text_replace(card_template, "$title", card->title->value);
      } else {
        text_replace(
            card_template, "$title",
            "        <a href=\"$link\"  target=\"_blank\">$title</a>\n");
        text_replace(card_template, "$title", card->title->value);
        text_replace(card_template, "$link", card->link->value);
      }

      if (text_compare(card->text, "")) {
        text_replace(card_template, "$text", "");
      } else {
        text_replace(card_template, "$text", "        <p>$text</p>\n");
        text_replace(card_template, "$text", card->text->value);
      }
      text_replace(card_template, "$endtext", "      </div>\n");
    }
    text_append(cards, card_template->value);
  });
  dealloc(card_template);
  text_replace(self->page, "$cards", cards->value);
  dealloc(cards);
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
