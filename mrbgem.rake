MRuby::Gem::Specification.new('mruby-clay') do |spec|
  spec.license  = 'MIT'
  spec.author   = 'Alexandre Barret'
  spec.summary  = 'mruby bindings for clay'

  spec.cc.include_paths << File.join(__dir__, 'clay')
end
