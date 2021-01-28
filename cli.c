//
// Copyright (c) 2020, Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#include "home.h"
#include "post.h"
#include "prototype.h"
#include "text.h"
#include "term.h"

int main(int argc, char **argv) {
  if(argc < 2) {
    term_error("no imput folder\n");
    return EXIT_FAILURE;
  }

  if(argc > 2) {
    term_error("only one argument is expected\n");
    return EXIT_FAILURE;
  }

  if(strcmp(argv[1], "--help") == 0) {
    printf("Usage: staticgen [FOLDER|--help|--license]\n");
    printf("Static Weblog Generator makes the Html files of a weblog \n");
    printf("site from files written with a markup language.\n");
    printf("\n");
    printf("Compile weblog in the FOLDER path.\n");
    printf("\n");
    printf("  --help     display this help and exit\n");
    printf("  --license  output license and exit\n");
    return EXIT_SUCCESS;
  }

  if(strcmp(argv[1], "--license") == 0) {
    printf("ISC License\n");
    printf("\n");
    printf("Copyright (c) 2020, Fellipe Augusto Ugliara\n");
    printf("\n");
    printf("Permission to use, copy, modify, and/or distribute this software for any\n");
    printf("purpose with or without fee is hereby granted, provided that the above\n");
    printf("copyright notice and this permission notice appear in all copies.\n");
    printf("\n");
    printf("THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL WARRANTIES\n");
    printf("WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF\n");
    printf("MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR\n");
    printf("ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES\n");
    printf("WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN\n");
    printf("ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF\n");
    printf("OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n");  
    return EXIT_SUCCESS;
  }

  home_t *home = alloc(home_t);
  printf("Weblog Staticgen\n\n");
  post_t *post = alloc(post_t);

  home_compile(home, argv[1]);
  list_for(home->posts, index, home_post_t, item, {
    if (!text_compare(item->link, "")) {
      post_compile(post, home, item);
    }
  });

  printf("Done\n");

  dealloc(post);
  dealloc(home);
}
