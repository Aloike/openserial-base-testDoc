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
<!--{% plantuml %}
digraph tree {
    nodesep=.1;
    rankdir=LR;
    node [shape=box, style="rounded,filled", width=3, height=0];


    /*
     *  Declare nodes
     */
    node_coreApp [label="Core Application", style="squared", width=0];
    node_ifaceSerialPort [label="Serial Port interface"];
    node_gui [label="Basic GUI (terminal-like)"];
    node_configManagement [label="Configuration File management"];
    node_pluginsManagement [label="Plugins management"];


    /*
     *  Draw horizontal arrows
     */
    pnt_ifaceSerialPort[shape=point];
    pnt_ifaceSerialPort->node_ifaceSerialPort;

    pnt_gui[shape=point];
    pnt_gui->node_gui;

    pnt_configManagement[shape=point];
    pnt_configManagement->node_configManagement;

    pnt_pluginsManagement[shape=point];
    pnt_pluginsManagement->node_pluginsManagement;


    /*
     *  Draw vertical lines
     */
    {
        rank=same;
        node_coreApp->pnt_ifaceSerialPort->pnt_gui->pnt_configManagement->pnt_pluginsManagement[arrowhead=none];
    }
}
{% endplantuml %} -->
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

