//
// Copyright (c) 2019, Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#include "post.h"

static void replace_text_special_char(text_t *text) {
  text_replace(text, "'#", "#");
  text_replace(text, "'^", "^");
  text_replace(text, "'~", "~");
  text_replace(text, "'*", "*");
  text_replace(text, "'`", "`");
  text_replace(text, "'!", "!");
  text_replace(text, "''", "'");
}

static void session_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  token_t *text = ast_get_token(rule, 1);

  text_t *temp = copy(text->value);
  replace_text_special_char(temp);
  text_trim(temp);

  text_append(post->post, "    <h2>");
  text_append(post->post, temp->value);
  text_append(post->post, "</h2>\n\n");

  dealloc(temp);
}

static void subsession_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  token_t *text = ast_get_token(rule, 1);

  text_t *temp = copy(text->value);
  replace_text_special_char(temp);
  text_trim(temp);

  text_append(post->post, "    <h3>");
  text_append(post->post, temp->value);
  text_append(post->post, "</h3>\n\n");

  dealloc(temp);
}

static void linebreak_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);

  text_append(post->post, "<br>");
}

static void parttext_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  token_t *text = ast_get_token(rule, 0);

  text_t *temp = copy(text->value);
  replace_text_special_char(temp);

  text_append(post->post, temp->value);

  dealloc(temp);
}

static void italic_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  token_t *text = ast_get_token(rule, 1);

  text_t *temp = copy(text->value);
  replace_text_special_char(temp);

  text_append(post->post, "<em>");
  text_append(post->post, temp->value);
  text_append(post->post, "</em>");

  dealloc(temp);
}

static void bold_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  token_t *text = ast_get_token(rule, 1);

  text_t *temp = copy(text->value);
  replace_text_special_char(temp);

  text_append(post->post, "<strong>");
  text_append(post->post, temp->value);
  text_append(post->post, "</strong>");

  dealloc(temp);
}

static void link_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  token_t *name = ast_get_token(rule, 1);
  token_t *link = ast_get_token(rule, 3);

  text_t *temp = copy(name->value);
  replace_text_special_char(temp);

  text_append(post->post, "<strong><a href=\"");
  text_append(post->post, link->value->value);
  text_append(post->post, "\">");
  text_append(post->post, temp->value);
  text_append(post->post, "</a></strong>");

  dealloc(temp);
}

static void image_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  token_t *name = ast_get_token(rule, 1);
  token_t *link = ast_get_token(rule, 3);

  text_t *temp = copy(name->value);
  replace_text_special_char(temp);

  text_append(post->post, "    <center>\n"
                          "      <div class=\"horizontal-scroll\">\n"
                          "        <img class=\"illustration\" src=\"");
  text_append(post->post, link->value->value);
  text_append(post->post, "\" />\n"
                          "      </div>\n"
                          "      <figcaption>");
  text_append(post->post, temp->value);
  text_append(post->post, "</figcaption>\n"
                          "    </center>\n\n");

  dealloc(temp);
}

static void replace_code_special_char(text_t *text) {
  text_replace(text, "'!", "!");
  text_replace(text, "''", "'");
  text_replace(text, "\r\n", "&#10;");
  text_replace(text, "\n", "&#10;");
  text_replace(text, " ", "&#32;");
}

static void code_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  token_t *text = ast_get_token(rule, 0);

  text_t *temp = copy(text->value);
  text_sub(temp, 3, text_size(temp) - 6);
  text_trim(temp);
  replace_code_special_char(temp);

  text_append(post->post, "    <pre><code>");
  text_append(post->post, temp->value);
  text_append(post->post, "</code></pre>\n\n");
  dealloc(temp);
}

static void text_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  text_append(post->post, "    <p>");
}

static void text_exit(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  text_append(post->post, "</p>\n\n");
}

static void quote_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  text_append(post->post, "    <blockquote>\n      <p>");
}

static void quote_exit(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  text_append(post->post, "</p>\n    </blockquote>\n\n");
}

static void ordered_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  text_append(post->post, "    <ul>\n");
}

static void ordered_exit(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  text_append(post->post, "    </ul>\n\n");
}

static void unordered_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  text_append(post->post, "    <ol>\n");
}

static void unordered_exit(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  text_append(post->post, "    </ol>\n\n");
}

static void item_enter(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  text_append(post->post, "      <li>");
}

static void item_exit(ast_item_t *rule, object_t context) {
  post_t *post = cast(post_t *, context);
  text_append(post->post, "</li>\n");
}

static void _alloc_(post_t *self, args_t arguments) {
  self->recognizer = alloc(recognizer_t);

  scanner_t *scanner = self->recognizer->scanner;
  scanner_add_model(scanner, ":Comment", "^##(#N|#A|,|:|#.|/| |#(|#)|-)*\r?\n");
  scanner_add_model(scanner, "Quote", "^#* ?");
  scanner_add_model(scanner, "Session", "^#*#* ?");
  scanner_add_model(scanner, "SubSession", "^#*#*#* ?");
  scanner_add_model(scanner, "Text",
                    "^('(##|#^|~|#*|#`|!|')|#N|#A|,|:|#.|/"
                    "|#(|#)|[|]|{|}|-|#+|@| |;|$|=|_|\\|%|\"|#?)+");
  scanner_add_model(scanner, "Bold", "^`");
  scanner_add_model(scanner, "Italic", "^``");
  scanner_add_model(scanner, "Ordered", "^~");
  scanner_add_model(scanner, "Unordered", "^~~");
  scanner_add_model(scanner, "Link", "^!");
  scanner_add_model(scanner, "Image", "^!!");
  scanner_add_model(scanner, "Code",
                    "^!!!('(!|')|##|#^|~|#*|#`|#N|#A|,|:|#.|/"
                    "|#(|#)|[|]|{|}|-|#+|@| |;|$|=|_|\\|%|\"|#?|\r?\n)+!!!");
  scanner_add_model(scanner, "LineBreak", "^#^");
  scanner_add_model(scanner, ":TextBreak", "^\r?\n");
  scanner_add_model(scanner, "CloseBlock", "^\r?\n\r?\n");

  grammar_t *grammar = self->recognizer->parser->grammar;
  grammar_rule(grammar, "init", "block :init | block Eot");
  grammar_rule(grammar, "block",
               "session | subsession | text | quote | ordered | unordered | "
               "code | image");
  grammar_rule(grammar, "session", "Session Text CloseBlock");
  grammar_rule(grammar, "subsession", "SubSession Text CloseBlock");
  grammar_rule(grammar, "part", "subpart :part | subpart");
  grammar_rule(grammar, "subpart",
               "parttext | bold | linebreak | italic | link");
  grammar_rule(grammar, "linebreak", "LineBreak");
  grammar_rule(grammar, "parttext", "Text");
  grammar_rule(grammar, "image", "Image Text Image Text Image CloseBlock");
  grammar_rule(grammar, "link", "Link Text Link Text Link");
  grammar_rule(grammar, "bold", "Bold Text Bold");
  grammar_rule(grammar, "italic", "Italic Text Italic");
  grammar_rule(grammar, "quote", "Quote part Quote CloseBlock");
  grammar_rule(grammar, "ordered",
               "ordereditem :ordered | ordereditem CloseBlock");
  grammar_rule(grammar, "ordereditem", "Ordered part");
  grammar_rule(grammar, "unordered",
               "unordereditem :unordered | unordereditem CloseBlock");
  grammar_rule(grammar, "unordereditem", "Unordered part");
  grammar_rule(grammar, "text", "part CloseBlock");
  grammar_rule(grammar, "code", "Code CloseBlock");

  grammar_begin(grammar, "init");

  self->generator = alloc(walker_t);

  self->generator->context = self;
  walker_listener(self->generator, "session", session_enter, NULL);
  walker_listener(self->generator, "subsession", subsession_enter, NULL);
  walker_listener(self->generator, "linebreak", linebreak_enter, NULL);
  walker_listener(self->generator, "parttext", parttext_enter, NULL);
  walker_listener(self->generator, "italic", italic_enter, NULL);
  walker_listener(self->generator, "bold", bold_enter, NULL);
  walker_listener(self->generator, "link", link_enter, NULL);
  walker_listener(self->generator, "image", image_enter, NULL);
  walker_listener(self->generator, "code", code_enter, NULL);
  walker_listener(self->generator, "text", text_enter, text_exit);
  walker_listener(self->generator, "quote", quote_enter, quote_exit);
  walker_listener(self->generator, "ordered", ordered_enter, ordered_exit);
  walker_listener(self->generator, "unordered", unordered_enter,
                  unordered_exit);
  walker_listener(self->generator, "ordereditem", item_enter, item_exit);
  walker_listener(self->generator, "unordereditem", item_enter, item_exit);

  self->page = alloc(text_t, "");
  self->post = alloc(text_t, "");
}

static void _free_(post_t *self) {
  dealloc(self->recognizer);
  dealloc(self->generator);

  dealloc(self->page);
  dealloc(self->post);
}

static void _copy_(post_t *self, post_t *object) {}

static bool _equal_(post_t *self, post_t *object) { return true; }

def_prototype_source(post_t, _alloc_, _free_, _copy_, _equal_);

static void post_page_generate(post_t *self, home_t *home,
                               home_post_t *home_post) {
  text_from_file(self->page, "template/post.html");
  text_replace(self->page, "$date", home->license_date->value);
  text_replace(self->page, "$holder", home->license_holder->value);
  text_replace(self->page, "$type", home->license_type->value);
  text_replace(self->page, "$file", home->license_file->value);
  text_replace(self->page, "$link", home->license_link->value);
  text_replace(self->page, "$title", home->weblog_title->value);
  text_replace(self->page, "$description", home->weblog_description->value);
  text_replace(self->page, "$keywords", home->weblog_keywords->value);

  text_replace(self->page, "$post_date", home_post->date->value);
  text_replace(self->page, "$post_show", home_post->show->value);
  text_replace(self->page, "$post_group", home_post->group->value);
  text_replace(self->page, "$post_title", home_post->title->value);

  text_trim(self->post);
  text_replace(self->page, "$post", self->post->value);
}

void post_compile(post_t *self, home_t *home, home_post_t *home_post) {
  text_set(self->page, "");
  text_set(self->post, "");

  text_t *out = copy(home->path);
  text_append(out, "/");
  text_append(out, home_post->link->value);
  text_t *in = copy(out);
  text_replace(in, ".html", ".post");
  text_t *file = alloc(text_t, "");
  text_from_file(file, in->value);
  printf("Post Page %s\n", in->value);
  dealloc(in);
  if (recognizer_perform(self->recognizer, file->value)) {
    walker_perform(self->generator, self->recognizer->parser->ast);
    post_page_generate(self, home, home_post);
    text_to_file(self->page, out->value);
    printf("Success\n\n");
  } else {
    printf("Failure\n\n");
  }
  dealloc(out);
  dealloc(file);
}

void post_test() {
  post_t *post = alloc(post_t);
  assert(type_equal(post, "post_t") == true);
  dealloc(post);
}