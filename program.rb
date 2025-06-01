require 'json'
require 'yaml'

actual = eval(File.read('result.txt'))
expected = YAML.load_file('experiments/testing/clay_example.yml')

File.open('test_actual.json', 'wb') do |f|
  f.write(JSON.pretty_generate actual)
end

File.open('test_expected.json', 'wb') do |f|
  f.write(JSON.pretty_generate expected)
end
