project('hello-world', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=gnu11'])

gtk_dep = dependency('gtk4', version : '>=4.0')

executable('hello-world', 'main.c',
  dependencies : [gtk_dep],
  install : true)
