# php-bootstrap
Version 0.1.0 Beta

[![Build Status](https://travis-ci.org/darkknight13/php-bootstrap.svg?branch=master)](https://travis-ci.org/darkknight13/php-bootstrap)
[![Coverage Status](https://coveralls.io/repos/github/darkknight13/php-bootstrap/badge.svg?branch=master)](https://coveralls.io/github/darkknight13/php-bootstrap?branch=master)

This is a PHP Library to generate Bootstrap HTML

## Progress Bar
```PHP
Bootstrap_ProgressBar::initiate('main_progress_bar') //need to initialize using id of the progressbar
      ->add_bar('60') // adding a progress bar with percentage 60
      ->type('default') // progress bar style types, supports all bootstrap styles
      ->showtext() //showing the text in bar
      ->striped() // striped bar
      ->state('active') // animate the striped bar
      ->generate(); // generate the html
```
Above code will generate a Progress like -
![Alt Text](https://raw.githubusercontent.com/darkknight13/php-bootstrap/master/images/progressbar_example_1.PNG)
