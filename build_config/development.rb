MRuby::Build.new do |conf|
  toolchain :gcc

  conf.gem "#{ MRUBY_ROOT }/.."
  conf.gembox 'default'
  # conf.gembox 'full-core'

  conf.cc.flags << '-g -O0 -fsanitize=address'
  conf.linker.flags << '-fsanitize=address'

  conf.enable_debug
  conf.enable_bintest
  conf.enable_test
end
