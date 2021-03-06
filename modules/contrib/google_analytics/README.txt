
Module: Google Analytics
Author: Alexander Hass <http://drupal.org/user/85918>


Description
===========
Adds the Google Analytics tracking system to your website.

Requirements
============

* Google Analytics user account


Installation
============
* Copy the 'google_analytics' module directory in to your Drupal 'modules'
directory as usual.


Usage
=====
In the settings page enter your Google Analytics account number.

All pages will now have the required JavaScript added to the
HTML footer can confirm this by viewing the page source from
your browser.

Page specific tracking
====================================================
The default is set to "Add to every page except the listed pages". By
default the following pages are listed for exclusion:

admin
admin/*
batch
node/add*
node/*/*
user/*/*

These defaults are changeable by the website administrator or any other
user with 'administer google analytics' permission.

Like the blocks visibility settings in Drupal core, there is now a
choice for "Add if the following PHP code returns TRUE." Sample PHP snippets
that can be used in this textarea can be found on the handbook page
"Overview-approach to block visibility" at http://drupal.org/node/64135.

Advanced Settings
=================
You can include additional JavaScript snippets in the custom javascript
code textarea. These can be found on the official Google Analytics pages
and a few examples at http://drupal.org/node/248699. Support is not
provided for any customisations you include.

To speed up page loading you may also cache the Google Analytics "analytics.js"
file locally.
