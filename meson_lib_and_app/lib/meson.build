sources = files(
  'src/lib.cpp'
)

test_lib = library('test-lib', sources, include_directories: include_directories('./src'))

test_dep = declare_dependency(
  link_with: test_lib,
  include_directories: include_directories('./src')
)
