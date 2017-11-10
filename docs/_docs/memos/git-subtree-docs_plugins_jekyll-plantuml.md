---
title: "How the 'PlantUML' plugin has been integrated to Jekyll"
layout: default
---

# Generalities

## Introduction

The "jekyll-plantuml" plugin provides to Jekyll the ability to integrate
graph drawings described in a specific text format and generated through
"GraphViz"/"Dot" tools in the static website.

This page is about how the "PlantUML" Jekyll plugin has been integrated to this
documentation. It might be useful for future reference.


## Resources

[A "GraphViz cheat-sheet"](http://www.graphviz.org/pdf/dotguide.pdf)


# Dependencies installation

## The plantuml Java archive

It takes the form of a Java archive.
~~~~~~~~~~{bash}
cd docs/
mkdir _bin/
wget http://sourceforge.net/projects/plantuml/files/plantuml.jar/download
mv download plantuml.jar
~~~~~~~~~~

## The GraphViz/Dot binary

Directly from Linux Mint's official repo :
~~~~~~~~~~{bash}
sudo apt-get install -y graphviz
~~~~~~~~~~


# Initialization of the subtree

~~~~~~~~~~{bash}
git subtree add --prefix=docs/_plugins/jekyll-plantuml/ https://github.com/yjpark/jekyll-plantuml.git master --squash
~~~~~~~~~~


# Configuration file edition

These lines have been added to `_config.yml` :

<pre class="nolines">
<code class="language-{sh}">plantuml:
  plantuml_jar: _bin/plantuml.jar     # path to plantuml jar
  tmp_folder: _plantuml               # tmp folder to put generated image files
  dot_exe: dot                        # [optional] path to Graphviz dot execution
  background_color: white             # [optional] UML image background color
</code></pre>


# Example :

![Example 1](http://uml.mvnsearch.org/github/Aloike/openserial-base-testDoc/master/docs/_docs/memos/example1.puml)


git-subtree-docs_plugins_jekyll-plantuml.md
