---
layout: default
permalink: /
title: "Home"
---

# Introduction

## System Overview : The OpenSerial Project

The OpenSerial Project aims to provide an open-source, cross-platform, modular tool to use serial interfaces.

It is constituted of a main application that can be extended through a plugins mechanism.

Find more on [the project's website](https://openserialproject.github.io) !



## Repository overview : The Main App : `openserial-base`

The project is contained in several repositories, each corresponding to a
Software Configuration Item.

This repository is dedicated to the development of the "base" application,
which is the central software of the project.<br>
The base software contains all the essential bits, like the serial interface
management, the configuration file management, a terminal-like interface, and
the plugins management mechanism.

<p align="center">
<!-- TODO : Ajouter schema home-repository_overview.puml -->
</p>


## Website overview : The `openserial-base` development documentation

This website, which is part of the `openserial-base` Software Configuration
Item, holds development documentation about this SCI.



# Documentation content

## List of this site's pages :

{% for lPage in site.pages %}|{{ lPage.title }}|<a href="{{ lPage.url }}">{{lPage.url}}</a>|
{% endfor %}


## List of this site's posts :

{% for lPost in site.posts %}|{{ lPost.title }}|<a href="{{ lPost.url }}">{{lPost.url}}</a>|
{% endfor %}

