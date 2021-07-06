# Staticgen

Static Weblog Generator makes the Html files of a weblog site from files written 
with a markup language. The generated files contain only Html and CSS code, they 
are JavaScript free and not require any server side dependencies. This project 
depends on the C11 standard library, toolbelt library, and language library.

## Build and Format

*Important*: This project requires the **toolbelt** 
(<https://github.com/ugliara-fellipe/library.toolbelt>) and **language** 
(<https://github.com/ugliara-fellipe/library.language>) libraries, clone and 
compile the libraries before build **staticgen**.

Use the Advanced Package Tool [apt](https://en.wikipedia.org/wiki/APT_\(software\)) 
to install the dependencies necessary to build and format the project. The compiler 
[clang](https://en.wikipedia.org/wiki/Clang) is used to compile the project, and the 
source codes are formated using [clang-format](http://clang.llvm.org/docs/ClangFormat.html).
Run the next command in Linux (Debian like distros) to install the dependencies.

```bash
sudo apt install clang clang-format
```

Use the script *build.sh* to compile the project and to generate the deploy folder 
with the executable file. Run the next command to build the project.

```bash
sh build.sh
```

The *format.sh* script applies the code style to the header (.h) and source (.c) 
files in the project. Run the next command to format the project.

```bash
sh format.sh
```

## Usage

The best way to begin with **staticgen** is by accessing the 
[weblog.pages](https://github.com/ugliara-fellipe/weblog.pages) repository. You 
will find a weblog example, developed with staticgen's markup language. After you 
build **staticgen**, you can generate a weblog from weblog.pages repository. 
The compiled weblog is hosted [here](https://ugliara-fellipe.github.io/). 
For further assistance, contact me by email (<ugliara.fellipe@gmail.com>).

### Writing a Home Page

The home page is the first weblog page. It has a list of cards, and each one 
shows the title, the date, and the group of a post. The title of each post 
is also the link to open it. The code of a home page contains the info about the 
page, the copyright notice, and the cards to each post. A code example is 
written below.

```
#
# Copyright 2020 Fellipe Augusto Ugliara
#
# Content on this file is licensed under the Creative Commons Attribution 
# 4.0 International License. To view a copy of this license: visit 
# http://creativecommons.org/licenses/by/4.0/, or search for the CONTENT 
# file at https://github.com/ugliara-fellipe/weblog.pages
#

weblog
  title [Writing Notebook]
  brief [Weblog - Writing Notebook]
  tags  [Mathematics,Philosophy,Profile,Storytelling]

copyright
  year  [2020]
  owner [Fellipe Augusto Ugliara]

license
  link  [https://github.com/ugliara-fellipe/ugliara-fellipe.github.io]
  type  [ISC]
  file  [LICENSE]

content
  link  [https://github.com/ugliara-fellipe/ugliara-fellipe.github.io]
  site  [http://creativecommons.org/licenses/by/4.0/]
  type  [CC BY 4.0]
  name  [Creative Commons Attribution 4.0 International License]
  file  [CONTENT]

post
  size  [large]
  date  [2021-08-07]
  show  [August 07, 2021]
  group [Mathematics]
  path  [mathbooks/mathbooks.html]
  title [Mathematics Library]
  text  [Knowledge is an asset that must be accessible to everyone. This post ]
        [list a set of free books, that is an option for who want to learn ]
        [math and does not support the high costs of books available on the ]
        [market. The books are organized into: elementary math, foundations ]
        [and philosophy, pure math, history and recreation.]

offsite
  size  [small]
  date  [2021-07-23]
  show  [July 23, 2021]
  group [Storytelling]
  link  [uncovered/uncovered.pdf]
  title [Uncovered]
  text  [An open tabletop storytelling game, that not use probabilistic ]
        [rules. It contains the "Uncovered" game scenery and "Tabloid Ruleset".]

note
  size  [normal]
  title [Talk with Author]
  text  [Here are posted my open works. All the contents are under permissive ]
        [licenses. Feel free to email me about the published topics.^^]
        [Author email:^ugliara.fellipe@gmail.com]
```

### Post and its Elements

The posts have a dialect that allows representing easily the elements of the 
text. The possible elements in a post are paragraphs, bold texts, italic texts, 
ordered lists, unordered lists, session titles, alerts, quotes, links, 
and special symbols. A post code example is written in the next code box and 
each element is detailed below.

```
#
# It is a Comment Block
#

It is a +italic+ break ^
It is a *bold* {Text + url} or {Text * url}

++First Item in Ordered List
++Second Item in Ordered List

**First Item in Unordered List
**Second Item in Unordered List

[Title]

[[SubTitle]]

+++
Quote Text
+++

***
Alert Text
***

Commom ^
! "$%~&'(),-./0123456789:;<=>?@ABCDEFGHIJKL
MNOPQRSTUVWXYZ_`abcdefghijklmnopqrstuvwxyz|

Special ^
\\ \+ \* \^ \[ \] \# \{ \}
```

#### Paragraph and Special Symbols

Inside the post tag to define a paragraph, only write the text, no specific 
symbol is required. The paragraphs are separated by empty lines. Use the 
symbol ^ to add a line break in the paragraph. The symbols used to define 
the post elements are considered special symbols, the list of them 
is \\ \+ \* [ ] # } and {. If a special symbol needs to be 
written add a \\ before it.

#### Session and List

There are two types of sessions and two types of lists. The session is defined 
with symbol [ session ], and a subsession with symbol [[ subssesion ]]. The 
unordered list is defined with symbol \*\* before each item in the list, and 
ordered list with symbol \+\+ before each item in the list.

#### Alert and Quote

These elements are similar, the text inside a symbol block will be 
considered a alert or quote. The alert block is defined inside symbols 
\*\*\*, and the quote block is defined inside the symbols \+\+\+. Each block 
opened with a symbol must be closed with the same symbol.

#### Link, Bold, and Italic

The bold and italic texts are easy, put them inside symbol \* to bold and 
\+ to italic. The link is defined with the symbols } { \+ or \* like shown in the 
last code box. 

### Style and Icon Files

The generated pages are linked with style files *global.css*, *home.css* and 
*post.css*. These files define the appearance of pages, style files can be gotten 
[here](https://github.com/ugliara-fellipe/weblog.pages/tree/master/style). 
An icon file also is necessary, it usually appears in the browser tab and the 
favorite bar, and this icon file can be gotten 
[here](https://github.com/ugliara-fellipe/weblog.pages/tree/master/images). 
New files can be created to change icon and style, the names and paths of 
files must be kept.

## Contributing

Pull requests are welcome. Please open an issue first to discuss what you 
would like to change. Read 
[CONTRIBUTING.md](https://github.com/ugliara-fellipe/weblog.staticgen/blob/master/.github/CONTRIBUTING.md) 
for details on our code of conduct, and the process for submitting pull requests.

## Copyright and License

Copyright 2020 Fellipe Augusto Ugliara

Use of source codes are governed by an ISC license that can be found 
in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
