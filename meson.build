project('gtk4-examples', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=gnu17'])

gtk_dep = dependency('gtk4', version : '>=4.0')

examples_dir = 'examples'
example_dirs = meson.source_root() / examples_dir
dirs = run_command('ls', example_dirs).stdout().strip().split('\n')

foreach d : dirs
  subdir = examples_dir / d
  if run_command('test', '-f', subdir / 'main.c').returncode() == 0
    exe_name = 'example-' + d
    executable(exe_name, subdir / 'main.c',
      dependencies : [gtk_dep],
      install : true)
  endif
endforeach
