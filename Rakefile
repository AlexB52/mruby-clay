require 'rake'
require 'tempfile'

desc 'Run mruby-mtest'
task :mtest do
  mruby_binary = File.expand_path("./mruby/bin/mruby", __dir__)
  mruby_files = FileList["mrblib/**/*.rb"]
  test_files = FileList["test/**/*.rb"]

  Tempfile.open("test_file") do |test_file|
    content = ""

    mruby_files.each do |file|
      content += File.read(file) + "\n"
    end

    test_files.each do |file|
      content += File.read(file).gsub("MTest::Unit.new.run", "") + "\n"
    end

    content += <<~RUBY
      class TestRunFailed < StandardError;end
      result = MTest::Unit.new.run
      raise TestRunFailed if result > 0
    RUBY

    test_file.write(content)
    test_file.rewind

    exit system("#{mruby_binary} #{test_file.path}")
  end
end

task default: [:mtest]