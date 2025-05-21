MRuby::Build.new do |conf|
  toolchain :gcc

  conf.gembox 'default'
  # conf.gembox 'full-core'

  conf.gem github: 'iij/mruby-mtest'
  conf.gem "#{ MRUBY_ROOT }/.."

  # conf.gem "#{ MRUBY_ROOT }/../../mruby-termbox2"

  conf.cc.flags << '-g -O0 -fsanitize=address'
  conf.linker.flags << '-fsanitize=address'

  conf.enable_debug
  conf.enable_bintest
  conf.enable_test
end
