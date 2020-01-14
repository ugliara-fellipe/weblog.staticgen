# Staticgen

Static Weblog Generator makes the Html files of a weblog site from files written 
with a markup language. The generated files contain only Html and CSS code, they 
are Javascript free and not require any server side dependencies. This project 
is designed with the C11 standard library only.

## Build and Format

*Important*: This project requires the **extend** library 
(<https://github.com/ugliara-fellipe/library.extend>), clone and compile the 
library before build **staticgen**.

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

## Contributing

Pull requests are welcome. Please open an issue first to discuss what you 
would like to change. Read [CONTRIBUTING.md](https://github.com/ugliara-fellipe/weblog.staticgen/blob/master/.github/CONTRIBUTING.md) for details on our code of conduct, and the 
process for submitting pull requests.

## License
Copyright (c) 2019, Fellipe Augusto Ugliara

Use of this source code is governed by an ISC license that can be found 
in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen