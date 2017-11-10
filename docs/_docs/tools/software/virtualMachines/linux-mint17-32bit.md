---
author: aloike
category: tools_sw_vm
date: 2017-04-17 13:58:00 +0100
layout: default
permalink: tools/software/virtualMachines/linux-mint17-32bits/
title: 'Linux Mint 17 32Bits Virtual Machine'
---

# Introduction

The OpenSerial Project aims to provide a cross-platform software to interact
with serial interfaces.

A good practice is to maintain several virtual machines with different
controlled environnements to be used as reference to build and test the
software for non-regressions.

This page describes the initial configuration of the Linux Mint 17 (32Bit)
Virtual Machine.



# Initial installation

* VirtualBox -> Machine -> New
  * In the creation Wizard :
    * Name : OpenSerial_LinuxMint17_32bits
    * Type : Linux
    * Version : Ubuntu (32-bit)
    * Memory : 2048 Mo
    * Disk :
	  * Name : OpenSerial_LinuxMint17_32bits_disk.vmdk
      * Type : VMDK, dynamically allocated, divided in several 2Go files
      * Size : 20Gb
  * Right click on the new VM -> Configuration
    * General -> Advanced :
      * Bidirectionnal clipboard and drag&drop
    * System -> Processor
      * 1 CPU @100%
      * PAE/NX activated
    * Display -> Screen
      * Video memory : 32Mo
      * 1 screen
    * Storage :
      * Selection of the Linux Mint disk image `linuxmint-17.3-cinnamon-32bit.iso`
    * Network : 
      * Board 1 : Bridge.
* Start The VM
  * Linux Mint shall automatically boot.
  * On the desktop, double-click "Install Linux Mint"
* In the installation Wizard :
  * Language : English
  * Erase disk and install Linux Mint.
  * "Who are you" screen :
    * Name : The Github one.
	* Computer name : linux-mint17-32bit.openserialproject.github.io
* Once the installation has ended, restart the machine.
* Snapshot of the machine state.


# System update

~~~~~~~~~~{sh}
sudo apt-get upgrade
mintupdate
# Refresh, then install all available updates.
~~~~~~~~~~


# Installed softwares

~~~~~~~~~~{.sh}
sudo apt-get install -y htop tree
sudo apt-get install -y git git-gui gitk meld
sudo apt-get install -y qt5-default
sudo apt-get install -y qtcreator vim vim-gnome

# For the Jekyll static website generator
sudo apt-get install -y ruby-full ruby2.0 ruby2.0-dev bundler rbenv
cd /usr/bin/
sudo mv ruby ruby.orig
sudo ln -s ruby2.0 ruby
sudo gem install jekyll --pre
sudo apt-get install -y graphviz
~~~~~~~~~~

<pre class="nolines">
<code class="language-{sh}">cd ~/Downloads
git clone git://github.com/jekyll/jekyll.git
cd jekyll/
git checkout v3.4.3 # To this day, the most recent.
</code></pre>

